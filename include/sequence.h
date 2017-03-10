/**********************************************************************
 * File: sequence.h
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
 * Functions and structures for the manipulation of protein 
 * sequences. Only minimal functionality is needed
 **********************************************************************/
#ifndef _SEQUENCE
#define _SEQUENCE

#include <string.h>
#include "util.h"


#define MAX_NAME_LENGTH 25

/******************* structure definitions ****************************/

struct Sequence {
  unsigned int length;
  char *name;
  char *seq;
  char *sec_struct;
  char *surf_acc;
  char *trans_mem;
  char *post_prob;
  char *lig_bind;
};

/********************** function prototypes ***************************/


/**********************************************************************
 FUNCTION: clone_Sequence
 DESCRIPTION: 
   Performs a deep copy of the given Sequence and returns it
 ARGS:
   A Sequenced pointer (sequence.h)
 RETURNS:
   A pointer to a Sequence structure
 NOTES:
 **********************************************************************/
struct Sequence *clone_Sequence( struct Sequence *);

/**********************************************************************
 FUNCTION: empty_Sequence
 DESCRIPTION: 
   Creates and returns an new, empty Sequence object
 ARGS: 
 RETURNS:
   A pointer to a Sequence structure
 NOTES:
 **********************************************************************/
struct Sequence *empty_Sequence( void );

/**********************************************************************
 FUNCTION: free_Sequence
 DESCRIPTION: 
   frees the memory occupied by the given Sequence reference
 ARGS: 
   A pointer to a struct Sequence
 RETURNS: 
   The NULL pointer
 NOTES:
 **********************************************************************/
void *free_Sequence( struct Sequence *);


#endif
