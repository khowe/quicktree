/***********************************************************************
 * File: aln2dist.h
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
 * This program produces a distance matrix in phylip format for the 
 * given alignment file. The optional -k flag is used to determine 
 * whether Kimura's tranlation is used to hopefully obtain more 
 * accurate distances. The matrix is written to stdout
 ***********************************************************************/
#ifndef _ALN2DIST
#define _ALN2DIST

#include "options.h"
#include "util.h"
#include "align.h"
#include "cluster.h"


/********************** function prototypes ***************************/


/*********************************************************************
 FUNCTION: generate_matrix_matrixmaker
 DESCRIPTION: 
   Given a fule handle to an alignment, creates and prints a 
   distance matrix for the sequences in the alignment in phylip format
   to stdout
 RETURNS: void
 ARGS: 
   An open alignment FILE
 NOTES: 
 *********************************************************************/
void generate_DistanceMatrix_matrixmaker( FILE * );

#endif
