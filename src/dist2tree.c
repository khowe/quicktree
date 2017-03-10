/**********************************************************************
 * File: dist2tree.c
 * Author: Kevin Howe
 * Copyright (C) Genome Research Limited, 2002-
 *-------------------------------------------------------------------
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------
 * NOTES:
 * This program can be used to generate neighbour-joining
 * trees given a distance matrix file.
 * The matrix file should be in phylip format; the application was
 * originally coded to compare the efficiency of the writer's 
 * implementation of neighbourjoining with that of phylip's 
 * 'neighbor' program. The tree is writtento stdout in New Hants 
 * format.
 **********************************************************************/
#include "dist2tree.h"


/*********************************************************************
 FUNCTION: maketree_neighbourjoin
 DESCRIPTION: 
   Given a file handle to a distance matrix, creates and prints a neighbour
   joining phlogenetic tree for the sequences in the alignment
 RETURNS: void
 ARGS: 
   A file handle to a distance matrix (in 'phylip' format)
 NOTES: 
 *********************************************************************/

void maketree_neighbourjoin( FILE *input ) {
  struct DistanceMatrix *mat;
  struct Alignment *aln;
  struct Tree *myTree;
  struct ClusterGroup *group; 

  /******* METHOD ***************************************
    1. Read the Cluster (reads in the matrix as a side effect).
    4. Shatter the Cluster into several CLusters, thus
         forming a ClusterGroup
    5. Build a tree from the ClusterGroup, and print it
  *******************************************************/

  mat = read_phylip_DistanceMatrix( input, &aln  );
  fclose( input );

  /* Note that the alignment here contains no sequences, just names,
     so there is no point in trying to merge identical sequences, hence 
     the FALSE argument 
  */
  group = alignment_to_ClusterGroup( aln, FALSE );
  group->matrix = mat;
  myTree = neighbour_joining_buildtree( group, FALSE );
  write_newhampshire_Tree( stdout, myTree, FALSE );

  aln = free_Alignment( aln );
  group = free_ClusterGroup( group );
  myTree = free_Tree( myTree );

}



/*********************************************************************
		        MAIN
 *********************************************************************/

void main (int argc, char *argv[]) {

  FILE *matrixfile;

  if (argc != 2)
    fatal_util( "Usage: neighbourjoin matrixfile (in PHYLIP format)");
  else {
    if ((matrixfile = fopen( argv[1], "r" )) == NULL)
      fatal_util( "Could not open file %s for reading", argv[1] );
  
    maketree_neighbourjoin( matrixfile );
  }
}
