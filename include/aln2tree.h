/***********************************************************************
 * File: aln2tree.h
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
 * This program constructs a phylogenetic tree from a given align-
 * ment file. The process comprises of two phases: 
 * 1. Construction of a distance matrix. Here, the optional -k
 * is used to determine whether Kimura's tranlation is used to
 * hopefully obtain more accurate distance
 * 2. The construction of the tree. It is printed in New-Hampshire
 * format to standard output
 ***********************************************************************/
#ifndef _ALN2TREE
#define _ALN2TREE

#include "options.h"
#include "util.h"
#include "align.h"
#include "cluster.h"
#include "buildtree.h"

/********************** function prototypes ***************************/


/*********************************************************************
 FUNCTION: maketree_treemaker
 DESCRIPTION: 
   Given a fule handle to an alignment, creates and prints a neighbour
   joining phlogenetic tree for the sequences in the alignment
 RETURNS: void
 ARGS: 
   A file handle to an alignment (should be in MUL format);
 NOTES: 
 *********************************************************************/
void maketree_treemaker( FILE * );


#endif
