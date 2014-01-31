#!/pkg/bin/perl 
###############################################################################
# This software is being provided to you, the LICENSEE, by the Linguistic     #
# Data Consortium (LDC) and the University of Pennsylvania (UPENN) under the  #
# following license.  By obtaining, using and/or copying this software, you   #
# agree that you have read, understood, and will comply with these terms and  #
# conditions:                                                                 #
#                                                                             #
# Permission to use, copy, modify and distribute, including the right to      #
# grant others the right to distribute at any tier, this software and its     #
# documentation for any purpose and without fee or royalty is hereby granted, #
# provided that you agree to comply with the following copyright notice and   #
# statements, including the disclaimer, and that the same appear on ALL       #
# copies of the software and documentation, including modifications that you  #
# make for internal use or for distribution:                                  #
#                                                                             #
# Copyright 1999 by the University of Pennsylvania.  All rights reserved.     #
#                                                                             #
# THIS SOFTWARE IS PROVIDED "AS IS"; LDC AND UPENN MAKE NO REPRESENTATIONS OR #
# WARRANTIES, EXPRESS OR IMPLIED.  By way of example, but not limitation,     #
# LDC AND UPENN MAKE NO REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR   #
# FITNESS FOR ANY PARTICULAR PURPOSE.                                         #
###############################################################################
# mansegment.perl Version 1.0
# Run as: mansegment.perl [dictfile] < infile > outfile
# Mandarin segmentation for both GB and BIG5 as long as the conresponding 
# word frequency dictionary is used.
#
# Written by Zhibiao Wu at LDC on April 12 1999
#
# Algorithm: Dynamic programming to find the path which has the highest 
# multiple of word probability, the next word is selected from the longest
# phrase.
#
# dictfile is a two column text file, first column is the frequency, 
# second column is the word. The program will change the file into a dbm 
# file in the first run. So be sure to remove the dbm file if you have a
# newer version of the text file.
##############################################################################

$DICTPATH = $1 if ( $0 =~ /(.+)\/[^\/]+/ );

if (@ARGV[0] ne "") {
    $dictfile = @ARGV[0];
} else {
    $dictfile = "./Mandarin.fre";
}

@ARGV=();
$#ARGV = -1;

# read in frequency dictionary in associate array.

&read_dict();

# read in Mandarin files.
$last = "";
while (<>) {
    chop;
    split(//,$_);
    $newline = "";
    $ch = 0;
    while (@_) {
	$c = shift(@_);
	if ($c eq " ") {
	    $newline .= $c;
	} elsif ($c =~ /[\x80-\xff]/) {
	    $cc = $c . shift(@_);
	    if ($ch == -1){
		$newline = $newline . " " . $cc;
	    } else {
		$newline = $newline . $cc;
	    }
	    $ch = 1;
	} else {
	    if ($ch == 1) {
		$newline = $newline . " " . $c;
	    } else {
		$newline .= $c;
	    }
	    $ch = -1;
	}
    }

    $_ = $newline;
    s/^ *//g;
    @line = split;
    if (@line[0] =~ /[\x80-\xff]/) {
	@line[0] = $last . @line[0];
    } else {
	if ($last ne "") {
	    &process($last);
	    print "\n";
	}
    }
    $last = "";

    while (@line + 1 -1 > 1) {
	$first = shift(@line);
	&process($first);
	print " ";
    } 
    if (@line[0] =~ /[\x0-\x7f]/) { 
	print "@line[0]\n";
    } else {
	$last = @line[0];
    }

}
if ($last ne "") {
    &process($last);
    print "\n";
}



sub process {
    local($sentence) = @_;

    return if ($sentence eq "");
    
    if (!($sentence =~ /[\x80-\xff]/)) {
	print $sentence;
	return;
    }

    $top = 1;
    $value{1} = 1;
    $position{1} = 0;
    $next{1} = -1;
    $result{1} = "";
    $nextid = 2;
    $len = length($sentence);

    while (($top != -1) && 
	   (!(($position{$top} == $len) && ($next{$top} == -1)))) {

#	print STDERR  "$. $result{$top}\n";

	# find the first open path
	$current = $top;
	$father = $top;
	while (($current != -1 ) && ($position{$current} == $len)) {
	    $father = $current;
	    $current = $next{$current};
	}

	# remove this path
	if ($current == $top) {
	    $top = $next{$top};
	} else {
	    $next{$father} = $next{$current};
	}

	if ($current == -1) {
	    # no open path, finished, take the first path
	    $next{$top} = -1;
	} else {
	    $firstword = substr($sentence, $position{$current}, 2);

	    # if the first character doesn't have word phrase in the dict.
	    if ($freq{"m,$firstword"} eq "") {
		$freq{"m,$firstword"} = 2;
	    }
	    
	    $i = $freq{"m,$firstword"};
	    if ($i > $len - $position{$current}) {
		$i = $len - $position{$current};
	    }
	    $i = $i +2;
	    
	    do {
		$i = $i-2;
		$word = substr($sentence, $position{$current}, $i);
	    } while (($i >=2) && ($freq{$word} eq ""));
	    
	    if ($i < 2) {
		$word = substr($sentence, $position{$current}, 2);
		$freq{$word} = 1;
	    }
	    
	    if ($freq{$word}) {
		&pronode();
	    }
	}
    }
   

    if ($top == -1) {
	print STDERR "Error: $. $sentence.\n";
    } else {
	$result{$top} =~ s/^ *//g;
	print $result{$top};
    }

    return;
}


sub pronode {

    $value{$nextid} = $value{$current} * $freq{$word} / $freq{total};
    $result{$nextid} = $result{$current} . " " . $word;
    $position{$nextid} = $position{$current} + $i;
    
    # check to see whether there is duplicated path
    # if there is a duplicate path, remove the small value path
    $index = $top;
    $father = $index;
    $needInsert = 1;
    while ($index != -1) {
	if ($position{$index} == $position{$nextid}) {
	    if ($value{$index} >= $value{$nextid}) {
		$needInsert = 0;
	    } else {
		if ($top == $index) {
		    $next{$nextid} = $next{$index};
		    $top = $nextid;
		    $needInsert = 0;
		} else {
		    $next{$father} = $next{$nextid};
		}
	    }
	    $index = -1;
	} else {
	    $father = $index;
	    $index = $next{$index};
	}
	
    }
    
    
    # insert the new path into the list
    if ($needInsert == 1) {
	while (($index != -1) && ($value{$index} > $value{$nextid})) {
	    $father = $index;
	    $index = $next{$index};
	}
	if ($top == $index) {
	    $next{$nextid} = $top;
	    $top = $nextid;
	} else {
	    $next{$father} = $nextid;
	    $next{$nextid} = $index;
	}
    }				# 
    
    $nextid++;

}

sub read_dict {
    print STDERR "Reading frequency dictionary $dictfile ...\n";
    if (-e "$dictfile.pag") {
	$textfiletime = -M $dictfile;
	$dbmfiletime = -M "$dictfile.pag";
	if ($textfiletime > $dbmfiletime) {
	    dbmopen(%freq,$dictfile,0644) || die "Cannot open dbmfile $dictfile";
	    print STDERR "DBM file exists, use it ...\n";
	    return;
	} else {
	    print STDERR "dbm file older than text file ...\n";
	}
	    
    }
    $freq{total} = 0;
    print STDERR "Making DBM file ...\n";
    dbmopen(%freq,$dictfile,0644) || die "Cannot open dbmfile $dictfile";
    open(F,"$dictfile") || die "Dictonary file $dictfile not found";
    while (<F>) {
	chop;
	s/^ *//;
	split;
	$freq{@_[1]}  = @_[0];
	$header = substr(@_[1],0,2);
	if ($freq{"m,$header"}) {
	    if ($freq{"m,$header"} < length(@_[1])) {
		$freq{"m,$header"} = length(@_[1]);
	    }
	} else {
	    $freq{"m,$header"} = length(@_[1]);
	}
	$freq{total} += @_[0];
    }
    close(F);
    print STDERR "Making DBM file finished\n";
}

