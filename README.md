About QuickTree
===============

QuickTree is an efficient implementation of the Neighbor-Joining
algorithm (PMID: 3447015), capable of reconstructing phylogenies 
from huge alignments in time less than the age of the universe.


Installing QuickTree
====================

QuickTree is written in ANSI C and should compile and run on a number
of different platforms. "make quicktree" from this directory should
compile the program and place the executable in the current directory.


Using QuickTree
===============

quicktree -h gives a list of options.

QuickTree accepts both distance matrix and multiple-sequence-aligment
inputs. The former should be in PHYLIP format. The latter should be in
Stockholm format, which is the native alignment format for the Pfam
database. Alignments in various formats can be converted to Stockholm
format with the sreformat program, which is part of the HMMer package 
(hmmer.org).

The tress are written to stdout, in the Newick/New-Hampshire format
use by PHYLIP and many other programs.


Contact
=======

Any problems, please contact klh@ebi.ac.uk

Kevin Howe, 2002

