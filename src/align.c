/*  Last edited: Feb  1 15:35 2002 (klh) */
/**********************************************************************
 ** FILE: align.c
 ** NOTES:
 **   Functions for the manipulation of multiple sequence
 **   alignments
**********************************************************************/

#include "align.h"


static char *comment = "#";
static char *whitespace = " \t\r\n";


/**********************************************************************
 FUNCTION: free_Alignment
 DESCRIPTION: 
   Frees the memory used by the given alignment
 ARGS:
   An Alignment
 RETURNS: A null pointer
 NOTES:
**********************************************************************/
void *free_Alignment( struct Alignment *al ) {
  unsigned int i;
  
  if (al != NULL) {
    if (al->seqs != NULL) {
      for( i=0; i < al->numseqs; i++) {
	al->seqs[i] = free_Sequence( al->seqs[i] );
      }
      al->seqs = free_util( al->seqs );
    }
    al = free_util( al );
  }
  return al;
}



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

struct Alignment *read_MUL_Alignment( FILE *stream ) {
  struct Alignment *aln;
  unsigned int index = 0;
  char tempname[MAX_NAME_LENGTH];
  int c;

  aln = (struct Alignment *) malloc_util( sizeof( struct Alignment ));
  aln->numseqs = 0;
  aln->seqs = NULL;
  aln->length = 0;
    

  while (( c = fgetc(stream)) != EOF) {
    if (aln->numseqs % SEQ_BLOCKSIZE == 0) {
      /* we need to allocate some more memory. But is it a malloc or realloc ? */

      if (aln->numseqs == 0) {
      	aln->seqs = (struct Sequence **) malloc_util( SEQ_BLOCKSIZE * sizeof( struct Sequence *));
      }
      else {
	aln->seqs = (struct Sequence **) 
	  realloc_util( aln->seqs, (aln->numseqs + SEQ_BLOCKSIZE) * sizeof( struct Sequence *));
      }
    }

    index = 0;
    while (! isspace(c) ) {
      tempname[index++] = c;
      c = fgetc(stream);
    }
    tempname[index] = '\0';
    while ( isspace(c = fgetc(stream)) );


    aln->seqs[aln->numseqs] = empty_Sequence();
    aln->seqs[aln->numseqs]->name = (char *) malloc_util( MAX_NAME_LENGTH * sizeof(char));
    strcpy(aln->seqs[aln->numseqs]->name, tempname);

    index = 0;
    do {
      if (index % RES_BLOCKSIZE == 0) {
      /* we need to allocate some more memory. But is it a malloc or realloc ? */
	if (index == 0) {
	  aln->seqs[aln->numseqs]->seq = (char *) malloc_util( RES_BLOCKSIZE * sizeof(char));
	}
	else {
	  aln->seqs[aln->numseqs]->seq = (char *) 
	    realloc_util( aln->seqs[aln->numseqs]->seq, (index + RES_BLOCKSIZE) * sizeof(char));
	}	
      }
      if (! isspace(c) )
	aln->seqs[aln->numseqs]->seq[index++] = c;
      c = fgetc(stream);

    } while ( c != '\n' && c != EOF);

    /* Since we now know the length of the sequence, we can do a bit of resizing */

    if (aln->numseqs == 0 || index < aln->length) {
      /* The first sequence is the trend setter */
      aln->length = index;
    }
    /* First, resize the current sequence */
    aln->seqs[aln->numseqs]->seq = (char *)
	   realloc_util( aln->seqs[aln->numseqs]->seq, aln->length * sizeof(char));

    /* if we reduced the aligment length, The earlier sequences are too big;
       Since we will only read up to the length of the smallest sequence, this
       will only prove a problem if we run out of memory; however, if the user 
       given non-flused alignments, then they are asking for everything they get...
    */

    aln->numseqs++;

  }

  /* now we can resize the seq array, and all the actual sequences themselves; this resizing
     will only save significant memory if a non-flush alignment has been given. Is it worth
     it? Well, we have to set the length of each sequence, so may as well do it while we are
     here*/

  aln->seqs = (struct Sequence **) realloc_util(  aln->seqs, aln->numseqs * sizeof( struct Sequence *));
  for (index=0; index < aln->numseqs; index++) {
    aln->seqs[index]->length = aln->length;
    aln->seqs[index]->seq = (char *) 
      realloc_util(  aln->seqs[index]->seq, aln->length * sizeof(char));
  }

  return aln;
}



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

void write_MUL_Alignment( FILE *handle, struct Alignment *al ) {
  unsigned int i,j;

  for( i=0; i < al->numseqs; i++ ) {
    fprintf( handle, "%-24s ", al->seqs[i]->name);
    for( j=0; j < al->length; j++) {
      fprintf( handle, "%c",  al->seqs[i]->seq[j]);
    }
    fprintf( handle, "\n");
  }
  fflush( handle );

}



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

struct Alignment *read_Stockholm_Alignment( FILE *handle ) {
  struct Alignment *aln;
  struct Aln_block {
    int col_st;
    int col_en;
  } *blocks = NULL;

  char line[MAX_LINE_LEN];
  char tokenstring[MAX_LINE_LEN];
  char *name_ptr = NULL;
  char *seq_ptr = NULL;
  char **aln_names = NULL;

  unsigned int i, j, k;
  unsigned int aln_pos = 0;
  unsigned int numseqs = 0;
  unsigned int numblocks  = 0;
  unsigned int thisseq = 0;
  unsigned int aln_len = 0;


  aln = (struct Alignment *) malloc_util( sizeof( struct Alignment ));
  aln->numseqs = 0;
  aln->seqs = NULL;
  aln->length = 0;


  /* This is a two-pass parse. First parse to get the block structure,
     second parse to actually read in the alignment */

  /*******************/
  /** First pass ... */
  /*******************/

  /* skip to first non-comment, non-blank line */

  do {
    if (fgets(line, MAX_LINE_LEN, handle) == NULL) {
      fatal_util("Cannot read alignment; file is empty");
    }
    strcpy(tokenstring, line);
  }
  while ((name_ptr = strtok(tokenstring, whitespace)) == NULL || 
	 (strchr(comment, *name_ptr) != NULL));

  numblocks   = 0;
  while (!feof(handle)) {
    if (numblocks == 0) {
      blocks = (struct Aln_block *) malloc_util (sizeof(struct Aln_block));
    }
    else { 
      blocks = (struct Aln_block *) realloc_util (blocks, (numblocks+1) * sizeof(struct Aln_block));
    }
    blocks[numblocks].col_st = MAX_LINE_LEN + 1;
    blocks[numblocks].col_en = -1;
    
    thisseq = 0;
    while (name_ptr != NULL) {
      if (numblocks == 0) {
	if (thisseq == 0) {
	  aln_names = (char **) malloc_util (sizeof(char *));
	}
	else { 
	  aln_names = (char **) realloc_util (aln_names, (thisseq + 1) * sizeof(char *));
	}
	
	aln_names[thisseq] = (char *) malloc_util( (strlen( name_ptr ) + 1) * sizeof(char));
	strcpy( aln_names[thisseq], name_ptr );
      }
      else {
	if (strcmp(aln_names[thisseq], name_ptr) != 0) {
	  warning_util("Your seq names are inconsistent across blocks. Using the names in the first block");
	}
	  
      }
      thisseq++;
      
      if ((seq_ptr = strtok(NULL, whitespace)) != NULL) {
	if (seq_ptr - tokenstring < blocks[numblocks].col_st) {
	  blocks[numblocks].col_st = seq_ptr - tokenstring;
	}
	/* The following accounts for the fact that there may be whitepasce at the end of the line */
	for (seq_ptr = line + strlen(line) - 1;  strchr(whitespace, *seq_ptr) != NULL; seq_ptr --);
	
	if (seq_ptr - line > blocks[numblocks].col_en) {
	  blocks[numblocks].col_en = seq_ptr - line;
	}
      }
      
      
      /* If the next line is blank, then we have reached the end of the block.
	 This assumes that blocksa are separated by one onr more blank line.
	 I hope this is correct */
      
      do {
	if (fgets(line, MAX_LINE_LEN, handle) == NULL) { 
	  name_ptr = NULL; 
	  break; 
	}
	strcpy(tokenstring, line);
	
	if ((name_ptr = strtok(tokenstring, whitespace)) == NULL) {
	  break;
	}
      } while (strchr(comment, *name_ptr) != NULL);
      
    }
    
    if (numblocks == 0) {
      numseqs = thisseq;
    }
    else if (thisseq != numseqs) {
      fatal_util("The blocks in your alignment are inconsistent in their number of sequences");
    }
    
    numblocks++;
    
    /* skip to ther next block */
    
    do {
      if (fgets(line, MAX_LINE_LEN, handle) == NULL) { 
	name_ptr = NULL; 
	break; 
      }
      strcpy(tokenstring, line);
    }
    while ((name_ptr = strtok(tokenstring, whitespace)) == NULL || 
	   (strchr(comment, *name_ptr) != NULL));
    
  }
  
  /* First pass over. At this point, we now know everything we need 
     to allocate the memory for the alignement */


  aln_len = 0;
  for (i = 0; i < numblocks; i++) {
    aln_len += blocks[i].col_en - blocks[i].col_st + 1;
  }

  aln->seqs = (struct Sequence **) malloc_util (numseqs * sizeof(struct Sequence *));
  aln->length = aln_len;
  aln->numseqs = numseqs;
  for (i=0; i < numseqs; i++) {
    aln->seqs[i] = empty_Sequence();
    aln->seqs[i]->length = aln_len;
    aln->seqs[i]->seq = (char *) malloc_util( aln_len * sizeof( char ));
    aln->seqs[i]->name = aln_names[i];
  }

  /********************/
  /** Second pass ... */
  /********************/

  rewind(handle);

  for (;;) {
    if (fgets(line, MAX_LINE_LEN, handle) == NULL) {
      fatal_util("Could not read in alignment; empty sequence file");
    }
    strcpy(tokenstring, line);

    if ((name_ptr = strtok(tokenstring, whitespace)) == NULL) continue;
    else if (strchr(comment, *name_ptr) == NULL) break;
  }
  
  aln_pos = 0;
  for (i = 0 ; i < numblocks; i++) {
    thisseq = 0;
    while (name_ptr != NULL) {
      /* we have a valid line. Copy the sequence characters into the correct sequence */
      for (k=blocks[i].col_st, j=aln_pos; k <= blocks[i].col_en; j++, k++) {
	aln->seqs[thisseq]->seq[j] = line[k];
      }

      for (;;) {
	/* loop until we hit the sequence line */
	name_ptr = NULL;
	if (fgets(line, MAX_LINE_LEN, handle) == NULL)  {
	  /* we have reached the end of the file */
	  break;
	}
	strcpy(tokenstring, line);
	if ((name_ptr = strtok(tokenstring, whitespace)) == NULL) {
	  /* A blank line, therfore the end of the block */
	  break;
	}
	if (strchr(comment, *name_ptr) == NULL) {
	  /* A non-null line. Check it's not a comment */
	  if (strchr(comment, *name_ptr) == NULL) {
	    thisseq++;
	    break;
	  }
	}
      }
    }
      
    aln_pos += blocks[i].col_en - blocks[i].col_st + 1;

    /* now parse up to the beginning of the next block */

    for (;;) {
      if (fgets(line, MAX_LINE_LEN, handle) == NULL) {
	/* end of file */
	break;
      }
      strcpy(tokenstring, line);
      if ((name_ptr = strtok(tokenstring, whitespace)) == NULL) {
	/* a blank line, so loop on around .. */
	continue;
      }
      if (strchr(comment, *name_ptr) == NULL) {
	/* not a comment line */
	break;
      }
    }
  }


  /***************************************************
   * Garbage collection and return
   ***************************************************/

  blocks = free_util(blocks);
  aln_names = free_util(aln_names);

  return aln;
}
