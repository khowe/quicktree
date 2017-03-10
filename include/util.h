/**********************************************************************
 * File: util.h
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
 * This file contains general utiliy functions used throughout the 
 * application, such as those for memory management and error
 * messaging. I have used it as a place to put other general stuff
 * until I have somewhere better to put it.
 **********************************************************************/
#ifndef _UTIL
#define _UTIL

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


/********************** function prototypes ***************************/

/********************************************************************* 
 FUNCTION: calloc_util
 DESCRIPTION: 
   A wrapper for the stdlib.h function calloc; exits if memory cannot
   be allocated
 RETURNS: A generic pointer to the reallocated memory
 ARGS: 
   The number of bytes to be allocated
 NOTES:
 *********************************************************************/
void *calloc_util( size_t, size_t );


/********************************************************************* 
 FUNCTION: malloc_util
 DESCRIPTION: 
   A wrapper for the stdlib.h function malloc; exits if memory cannot
   be allocated
 RETURNS: A generic pointer to the reallocated memory
 ARGS: 
   The number of bytes to be allocated
 NOTES:
 *********************************************************************/
void *malloc_util( size_t );


/********************************************************************* 
 FUNCTION: realloc_util
 DESCRIPTION: 
   A wrapper for the stdlib.h function realloc; exits if memory cannot
   be allocated
 RETURNS: A generic pointer to the reallocated memory
 ARGS:
   A pointer to the memory to be reallocated
   The number of bytes to be allocated
 NOTES:
 *********************************************************************/
void *realloc_util( void *, size_t );


/********************************************************************* 
 FUNCTION: free_util
 DESCRIPTION: 
   A wrapper for the stdlib.h function free; warns if the free could 
   not be performed
 RETURNS: A (hopefully null) pointer
 ARGS:
   A pointer to the memory to be deallocated
 NOTES:
 *********************************************************************/
void *free_util( void * );


/********************************************************************* 
 FUNCTION: fatal_util
 DESCRIPTION: 
   Prints the given formatted error message and exits
 RETURNS:
 ARGS:
   A format string + args, c.f. printf
 NOTES:
 *********************************************************************/
void fatal_util( char *, ... );


/********************************************************************* 
 FUNCTION: warning_util
 DESCRIPTION: 
   Prints the given formatted warning to stderr
 RETURNS:
 ARGS:
   A format string + args, c.f. printf
 NOTES:
 *********************************************************************/
void warning_util( char *, ... );


#endif
