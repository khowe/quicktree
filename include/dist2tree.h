/**********************************************************************
 * File: dist2tree.h
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

#ifndef _DIST2TREE
#define _DIST2TREE

#include "align.h"
#include "options.h"
#include "util.h"
#include "cluster.h"
#include "buildtree.h"


/********************** function prototypes ***************************/

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
void maketree_neighbourjoin( FILE * );


#endif
