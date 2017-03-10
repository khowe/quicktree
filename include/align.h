/**********************************************************************
 * File: align.h
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
 * Functions and types for the manipulation of multiple sequence
 * alignments
 **********************************************************************/
#ifndef _ALIGN
#define _ALIGN

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "sequence.h"
#include "util.h"

#define RES_BLOCKSIZE 20
#define SEQ_BLOCKSIZE 10
#define MAX_LINE_LEN  4096

/******************* structure definitions ****************************/

struct Alignment {
  unsigned int numseqs;
  unsigned int length;
  struct Sequence **seqs;
};

/********************** function prototypes ***************************/

/**********************************************************************
 FUNCTION: free_Alignment
 DESCRIPTION: 
   Frees the memory used by the given alignment
 ARGS:
   An Alignment
 RETURNS: A null pointer
 NOTES:
 **********************************************************************/
void *free_Alignment( struct Alignment *);


/**********************************************************************
 FUNCTION: read_MUL_Alignment
 DESCRIPTION: 
   Reads in a muliple alignment from the given file handle and returns
   it
 ARGS: 
   A file handle
 RETURNS: A number denoting the status:
   A pointer to the struct Alignment object created, or NULL of there
   was an error parsing the file
 NOTES: It is assumed that the aligment file is in Pfam (MUL) format.
   Garbage results should be expected if the input file is not in this 
   format

   The function allocates all the memory necessary for the 
   alignment. The caller should call free_Alignment (align.h) to 
   free this memory when the alignment is no longer needed
 **********************************************************************/
struct Alignment *read_MUL_Alignment( FILE * );


/**********************************************************************
 FUNCTION: read_Stockholm_Alignment
 DESCRIPTION: 
   This function fills a simple alignment structure from an
   file assumed to be in Stockholm format. At this stage, I am ignoring
   all mark-up information (all lines beginning with '#' are ignored).
   The function also allows for wrapped alignments. Note that Pfam
   alignments in MUL format will be handled correctly by this function
 ARGS:
   FILE *
 RETURNS: struct Alignment (align.h)
 NOTES:
 **********************************************************************/
struct Alignment *read_Stockholm_Alignment( FILE *);



/**********************************************************************
 FUNCTION: write_MUL_Alignment
 DESCRIPTION: 
   Prints a rep. of the alignment to the given handle (in MUL format)
 ARGS:
   FILE *
   struct Alignment (align.h)
 RETURNS: struct Alignment (align.h)
 NOTES:
 **********************************************************************/
void write_MUL_Alignment( FILE *, struct Alignment *);

#endif

