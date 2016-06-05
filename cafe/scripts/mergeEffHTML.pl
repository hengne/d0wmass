#!/usr/bin/perl -w

#################################################################################
#
# Original Date: 15 Aug 2006
# Original Author: Joseph Haley (Princeton Universiry)
# LaTeX extension by Remi Mommsen, July 15, 2007
#
# --- mergeEffHTML.perl Version 2.0 ---
# Modified Date: 20 Sept 2006
# Version 2.0 will merge eff.html files with an extra column for "Global efficiency
# corrected by the event weight."
# I.e. the columns are: 
# 1) Cut Name 
# 2) Number of events 
# 3) Selection efficiency
# 4) Global efficiency
# 5) Global efficiency corrected by the event weight
#
# What I want this program to do...
# - Take a list of eff.html files.
# - Look through the first file and find all the cuts
# - Store the cut names in an array (@cutName)
# - And have parallel arrays with: 
#    + number of events passing each cut (@cutCount)
#    + if it is a wright, weight * number of events (@weightxCount)
#    + if it is a weight, weight error * number of events (@weightErrxCount)
# - Loop through the remaining files one at a time doing the following:
#    + Find the first cut made in this file
#    + Check that this is the same as the first cut in the first file ($cutName[0])
#    + Update the parallel arrays
#    + Then find the next cut in this file and do the same, etc.
# **** Exit the program if any file has extra cuts or does not have cuts in exactly
#      the same order as @cutNames.  Note: it is okay if a file does not have
#      all the cuts because it one of the cut returned zero events; however, 
#      this should print a warning.
# - After looping through all the files, the arrays will be used to make the 
#      output eff.html (and optional text) file(s).
#
# Subroutines:
# &printusage print usage message to STDOUT.
# &helpmessage print instructions for gettins usage info.
# &get_weight_ave($i) returns (average weight, average weight error) for weight with index $i
# &update_gweight($weight, $weightErr) used the input to update $gweight and $gweightErr
# &get_cut_efficiencied($i) returns the three types of efficiencies for cut with index $i
#


# Print help message and exit program if there are not enough arguments
if ($#ARGV<0) {
    &helpmessage;
    exit 1;
}

### Parse the command line input
foreach $arg (@ARGV){
    #print "\$arg = $arg\n";
    # There are two types of command input 
    # (1) Control flags that begin with a '-' (e.g. -t -list=foo.list -v).
    # (2) Input html file names (do not begin with a '-').
    if($arg=~/^-/){
	#This is a control flag
	if($arg eq "-h" || $arg eq "-help"){
	    &printusage;
	    exit 0;
	}elsif($arg eq "-f" || $arg eq "-force"){
	    $force=1;
	}elsif($arg eq "-t" || $arg eq "-text"){
	    $text=1;
	}elsif($arg eq "-l" || $arg eq "-latex"){
	    $latex=1;
	}elsif($arg eq "-v" || $arg eq "-verbose"){
	    $verbose=1;
	}elsif($arg=~/^-list=(.*)/){
	    $listfile=$1;
	}elsif($arg=~/^-out=(.*)/){
	    $outfile=$1;
	}else{
	    print "Error: \'$arg\' is not a valid option.\n";
	    &helpmessage;
	    exit 1;
	}
    }else{
	#This is an input file name
	push @mergelist, $arg;
    }
}

### Fill @mergelist if a file list was given
if( $listfile ){
    if( @mergelist ){
	print "Error: You have specified input files on the command line and given\n";
	print "a list if input files.  You must do one or the other but not both.\n";
	&helpmessage;
	exit 1;
    }
    if( open LISTFILE, "$listfile" ){
	local $/ = "\n";
	while(my $line=<LISTFILE>){
	    if( $line=~/^\s*#/ ){
		# skip lines that start with #
	    }elsif( $line=~/^\s*([^\s]+)\s*$/ ){
		push @mergelist, $1;
	    }elsif( $line=~/^\s*$/ ){
		# skip empty lines
	    }else{
		print "Error in list file $listfile.\n";
		print "Line $.: $line";
		print "There must only one filename per line.\n";
		exit 1;
	    }
	}
	close LISTFILE;
    }else{
	print "Error: Could not open $listfile!\n";
	exit 1;
    }
}
if(!@mergelist){
    print "No input files!\n";
    &helpmessage;
    exit 1;
}
### @mergelist is full of files to be merged

### If $outfile has not been set use defualt
if( !$outfile ){ $outfile="merged.html"; }

#if($verbose){
#    print "input files : ";
#    my $temp=0;
#    foreach (@mergelist){
#	if( $temp++>3 ){
#	    print "$_ ...";
#	    last;
#	}
#	print "$_, ";
#    }
#    print "\n";
#    print "output file : $outfile\n";
#}

### Output file checks
if ( -e $outfile ) { # Check if the output file exists
    if ( ! -w $outfile ){ # Check that it is writable
	print "$outfile is not writable!  Aborting...\n";
	exit 1;
    }
    while (!$force){            # Prompt user to overwrite or abort
	print "The output file $outfile already exists, are you sure you want to continue?(y/n)";
	chomp(my $answer = <STDIN>);
	if( $answer eq 'y' ){
	    if( rename($outfile,$outfile."~") ){
		print "Moved old $outfile to $outfile~\n" ;
	    }
	    print "Proceeding...\n";
	    last;
	}
	elsif ( $answer eq 'n' ){
	    print "Aborting...\n";
	    exit 1;
	}
	print "Invalid answer...";
    }
}else{
    if($verbose){ print "File '$outfile' will be created...\n";}
}
### Now everything should be in order to start merging...


### Moving on to @mergelist...
foreach $file (@mergelist){
    if( ! -e $file ) {       # Check that this file exists
	print "***Skipping input file '$file' -> does not exist!\n";
	next;
    }elsif( ! -r $file ) {   # Check that this file is readable
	print "***Skipping input file '$file' -> not readable (check permissions)!\n";
	next;
    }elsif( ! -T $file ) {   # Check that this is a text file
	print "***Skipping input file '$file' -> not a text file!\n";
	next;
    }
    if($verbose){ print "processing $file...\n";}
    open FILE, $file or die "ERROR: Cannot open file $file!\n";
    # This file open and ready to merge
    
    # quantities to reset at beginning of each new file
    my $cutIndex = 0;
    my $totalWeight = 1.0;
    my $totalWeightErr = 0.0;

    local $/ = "</TR>\n"; # Change local copy of $/ (the input record separator) to "</TR>\n"

    while (my $line = <FILE>) {  # Iterate through the file (each chunk seperated by $/)
	
	    # Match this line to given format and find all the quantities of intrest

		#The "Initial" table row has this format:
		#<TR>
		#<TD align=left>
		#Initial
		#</TD>
		#<TD TITLE="Number of events">
		#10000
	        #<TD>&#160;</TD> <TD>&#160;</TD><TD>&#160;</TD> 
		#</TR>

		#Each cut row has this format:
		#<TR>                                         (or <TR BGCOLOR=#bfefff>)
		#<TD align=left>
		#PROCESSOR "dq" (input)                       <----- Cut Name
		#</TD>
		#<TD TITLE="Number of events">
		#100000                                       <----- Cut Count
		#</TD><TD TITLE="Selection efficiency">
		#100.000&#177;0.000%
		#</TD><TD TITLE="Global efficiency">
		#100.000&#177;0.000%
		#</TD>
	        #</TD><TD TITLE="Global efficiency corrected by the event weight">
	        #95.556&#177;0.079%
	        #</TD>
		#</TR>

	        #Each weight has this format:
		#<TR>
		#<TD align=left>
		#EMCorr: emCorr
		#</TD>
		#<TD TITLE="Number of events">
		#1496
		#</TD> <TD TITLE="Average weight">         OR: </TD> <TD TITLE="Global event weight">
		#0.826&#177;0.007
	        #</TD> <TD> &#160;</TD><TD>&#160;</TD> 
		#</TR>

	# Skip chunks that don't match one of the above formats.
	# Break matching chunks into smaller peices...
	if( $line=~m@^<TR.*?>\s*<TD align=left>\s*(\w+.*?)\s*</TD>\s*<TD TITLE="Number of events">\s*(\d+)\s*(?:</TD>)?\s*<TD>(&\#160;)</TD>\s*@i ){

	    ###Matches Initial Cut Format###
	    $this_is_weight = 0;

	}elsif( $line=~m@^<TR.*?>\s*<TD align=left>\s*(\w+.*?)\s*</TD>\s*<TD TITLE="Number of events">\s*(\d+)\s*</TD>\s*<TD TITLE="Selection efficiency">\s*(.*)@i ){

	    ###Matches Cut Format###
	    $this_is_weight = 0;

	}elsif( $line=~m@^<TR.*?>\s*<TD align=left>\s*(\w+.*?)\s*</TD>\s*<TD TITLE="Number of events">\s*(\d+)\s*</TD>\s*<TD TITLE=".*weight">\s*(.*?)\s*</TD>\s*@i  ){

	    ###Matches Weight Fromat###
	    $this_is_weight = 1;

	}else{
	    #does not match a format
	    next;
	}
	
	my $m1 = $1; # rename matches so I don't loose them if I do another search
	my $m2 = $2;
	my $m3 = $3;
	
	if( $m1=~m@(.*)</TD>@i ){ $m1 = $1; } #if there is a trailing "</TD>" in the name get rid of it.

	if( $#filesMerged < 0 ) { 
	    # This is the first file to be merged so we need to set the initial
	    # values for @cutName, @cutCount, @weightxCount, and @weightErrxCount) 
	    
	    #print $line;
	    #print "\$m1 = $m1\n";
	    #print "\$m2 = $m2\n";
	    #print "\$m3 = $m3\n";
	    
	    push @cutName, $m1;                          # Add this cut name to @cutName
	    push @cutCount, $m2;                         # Add event count for this cut to @cutCount
	    
	    # Check if this "cut" is actually a weight
	    if ( $this_is_weight ) {
		# Update total weight numbers
		$m3=~/^\s*(\d+\.\d+)\&\#177\;(\d+\.\d+)\s*$/;
		$totalWeight *= $1;
		$totalWeightErr = sqrt($totalWeightErr**2 + $2**2);
		push @is_a_weight,         1;
		push @thisweightxCount,    $1*$m2;
		push @thisweightErrxCount, $2*$m2;
	    }else{
		push @is_a_weight,         0; # not a weight
		push @thisweightxCount,    0; # don't care about these
		push @thisweightErrxCount, 0;
	    }
	    
	    if($#cutName != $cutIndex || $#cutCount != $cutIndex || $#is_a_weight != $cutIndex || $#thisweightxCount != $cutIndex || $#thisweightErrxCount != $cutIndex ){
		print "ERROR: Arrays do not match up!\n";
	    }
	    $cutIndex++;            # Increment cutIndex

	}else{
	    # We have already made @cutName from the first file so now we need 
	    # to make sure that the rest of the files have the same cut names and 
	    # merge the corresponding values into @cutCounts
	    
	    if( "$m1" ne $cutName[$cutIndex] ){  # Stop if this cut name does not match the one in @cutName
		print "The cut \'$1\' in file $file does not match the expected cut \'$cutName[$cutIndex]\'.\n";
		print "Aborting merge...\n";
		exit 1;
	    }
	    # Add event count for this cut to running total $cutCount[$cutIndex]
	    $cutCount[$cutIndex] += $m2;  
	    

	    # Is this a weight
	    if( $this_is_weight ){
		$is_a_weight[$cutIndex] or die "'$m1' looks like a _weight_, but I was expecting the _cut_ '$cutName[$cutIndex]'.  $!";
		# Update total weight numbers
		$m3=~/^\s*(\d+\.\d+)\&\#177\;(\d+\.\d+)\s*$/;
		$totalWeight *= $1;
		$totalWeightErr = sqrt($totalWeightErr**2 + $2**2);
		$thisweightxCount[$cutIndex]    += $1*$m2; # Update singlular weight arrays
		$thisweightErrxCount[$cutIndex] += $2*$m2;
		#print "\$thisweightxCount[$cutIndex] = $thisweightxCount[$cutIndex]\n";
		#print "\$thisweightErrxCount[$cutIndex] = $thisweightErrxCount[$cutIndex]\n";
	    }
	    
	    # Increment cutIndex
	    $cutIndex++;                 
	}
	# Next line please
    }
    # Done merging this file!
    if($#filesMerged < 0 && $verbose){
	print "\nFound the following cuts to be merged:\n";
	print "-------------------------------------------------------------\n";
	foreach (@cutName){
	    print "$_\n";
	}
	print "-------------------------------------------------------------\n";
    }
    if( $cutIndex <= $#cutName ){ print "Warning: $file only had $cutIndex of ".($#cutName+1)." cuts.\n";}
    push @filesMerged, $file; # Put file name in list of successfully merged files
    close FILE;
    # Thank you sir, may I have another?
}
### Now we have all the info from the input files


### Create the output file(s)...

### First a simple text file

# Defaults for global weight
$gweight = 1.0;
$gweightErr = 0.0;

if( $text ){

    # Set the name for the text file
    my $textfile = "$outfile\.text";
    if( $outfile=~/^(.+)\.html?/ ) { $textfile="$1\.text"; }

    if ( -e $textfile ) { # Check if the file exists
	rename($textfile, $textfile."~");
	if($verbose){ print "Moved old $textfile to $textfile~.\n";}
    }
    open TEXTFILE, ">$textfile" or die "Could not open $textfile for write! $!";    

    # The first "cut" is special because it is the Initial count
    printf TEXTFILE "%-35s  %-8s\n", $cutName[0], $cutCount[0];
    
    # Print the text for the rest of the cuts
    for (my $i = 1; $i <= $#cutName; $i++){
	
	if($is_a_weight[$i]){
	    # This "cut" is actually a weight
	    my ($weight_ave, $weightErr_ave) = &get_weight_ave($i);
	    # Update the global weight variables
	    &update_gweight($weight_ave, $weightErr_ave);
	    
	    printf TEXTFILE "%-35s  %-8s : %7.3f+-%-5.3f\n", $cutName[$i], $cutCount[$i], $weight_ave, $weightErr_ave;
	    
	}else{
	    # This is a cut
	    # Get cut, global, and weighted global efficiencies
	    my ($ceff, $cerr, $geff, $gerr, $weff, $werr) = &get_cut_efficiencies($i);
	    
	    printf TEXTFILE "%-35s  %-8s : %7.3f+-%-5.3f%% : %7.3f+-%-5.3f%% : %7.3f+-%-5.3f%%\n", $cutName[$i], $cutCount[$i], 100*$ceff, 100*$cerr, 100*$geff, 100*$gerr, 100*$weff, 100*$werr ;
	}
    }
    print TEXTFILE "NOTE: weight errors are not merged correctly, they are just averaged.\n";
    close TEXTFILE;  # Done making the text file
    
}

if( $latex ){

    # Set the name for the text file
    my $latexfile = "$outfile\.tex";
    if( $outfile=~/^(.+)\.html?/ ) { $latexfile="$1\.tex"; }

    if ( -e $latexfile ) { # Check if the file exists
	rename($latexfile, $latexfile."~");
	if($verbose){ print "Moved old $latexfile to $latexfile~.\n";}
    }
    open LATEXFILE, ">$latexfile" or die "Could not open $latexfile for write! $!";    

    # Print table header
    print LATEXFILE "\\documentclass[11pt,oneside]{article}\n";
    print LATEXFILE "\\begin{document}\n";
    print LATEXFILE "\\begin{table}\n";
    print LATEXFILE "\\begin{center}\n";
    print LATEXFILE "\\begin{tabular}{l|r|r\@{\$\\pm\$}l|r\@{\$\\pm\$}l|r\@{\$\\pm\$}l}\n";
    print LATEXFILE "Selection &\\# events &\\multicolumn{2}{|c}{Rel. eff.} &\\multicolumn{2}{|c}{Global eff.} &\\multicolumn{2}{|c}{Weighted eff.}\\\\\n";
    print LATEXFILE "\\hline\n";
    # The first "cut" is special because it is the Initial count
    printf LATEXFILE "%-35s &%-8s &\\multicolumn{2}{|c}{} &\\multicolumn{2}{|c}{} &\\multicolumn{2}{|c}{}\\\\\n", &clean_latex($cutName[0]), $cutCount[0];
    
    # Print the text for the rest of the cuts
    for (my $i = 1; $i <= $#cutName; $i++){

	if($is_a_weight[$i]){
	    # This "cut" is actually a weight
	    my ($weight_ave, $weightErr_ave) = &get_weight_ave($i);
	    # Update the global weight variables
	    &update_gweight($weight_ave, $weightErr_ave);
	    
	    printf LATEXFILE "%-35s &%-8s &%7.3f &%-5.3f &\\multicolumn{2}{|c}{} &\\multicolumn{2}{|c}{}\\\\\n", &clean_latex($cutName[$i]), $cutCount[$i], $weight_ave, $weightErr_ave;
	    
	}else{
	    # This is a cut
	    # Get cut, global, and weighted global efficiencies
	    my ($ceff, $cerr, $geff, $gerr, $weff, $werr) = &get_cut_efficiencies($i);
	    
	    printf LATEXFILE "%-35s &%-8s &%7.3f &%-5.3f\\%% &%7.3f &%-5.3f\\%% &%7.3f &%-5.3f\\%%\\\\\n", &clean_latex($cutName[$i]), $cutCount[$i], 100*$ceff, 100*$cerr, 100*$geff, 100*$gerr, 100*$weff, 100*$werr ;
	}
    }
    print LATEXFILE "\\end{tabular}\n";
    print LATEXFILE "\\end{center}\n";
    print LATEXFILE "\\caption{NOTE: weight errors are not merged correctly, they are just averaged.}\n";
    print LATEXFILE "\\end{table}\n";
    print LATEXFILE "\\end{document}\n";
    close LATEXFILE;  # Done making the text file
    
}

### Create the output HTML file
# To create the outfile I will copy lines from the first merged file and simply change
# the cut efficiencies to the new merged values.

open OUTFILE, ">$outfile" or die "Could not open $outfile for write! $!";
open INFILE, "$mergelist[0]" or die "Could not open $mergelist[0]!  $!";
local $/ = "</TR>\n"; # Change local copy of $/ (the input record separator) to "</TR>\n"
$cutIndex=0;
# Defaults for global weight
$gweight = 1.0;
$gweightErr = 0.0;
# Initial values for eff and geff strings
$ceffString = "&#160;";
$geffString = "&#160;";
$weffString = "&#160;";

while ($line = <INFILE>) {  # Iterate through the file (each chunk seperated by $/)
    
    if( $line=~m@^(<TR.*?>)\s*<TD align=left>\s*(\w+.*?)\s*</TD>\s*<TD TITLE="Number of events">\s*\d+\s*(?:</TD>)?\s*<TD>&\#160;</TD>\s*@i ){
	###Matches Initial Cut Format###
	
	if($cutIndex > 0){
	    print "The cut '$cutName[$cutIndex]' has the format of the initial cut, but is not the first cut!\n";
	    print "Aborting...\n";
	    exit 1;
	}
	if($2 ne $cutName[0]){
	    print "Found the initial cut '$2', but was expecting the cut '$cutName[0]'!\n";
	    print "Aborting...\n";
	    exit 1;
	}
	$outline = "$1\n<TD align=left>\n$cutName[0]\n</TD>\n<TD TITLE=\"Number of events\">\n$cutCount[0]\n<TD>&#160;</TD> <TD>&#160;</TD><TD>&#160;</TD> \n</TR>\n";
	
	$cutIndex++;
	
    }elsif( $line=~m@^(<TR.*?>)\s*<TD align=left>\s*(\w+.*?)\s*</TD>\s*<TD TITLE="Number of events">\s*\d+\s*</TD>\s*<TD TITLE="Selection efficiency">\s*.*@i ){
	###Matches Cut Format###
	
	if( $is_a_weight[$cutIndex] == 1 ){
	    print "The cut '$2' has the format of a cut, but it was set as a weight!\n";
	    print "Aborting...\n";
	    exit 1;
	}
	if($2 ne $cutName[$cutIndex]){
	    print "Found the cut '$2', but was expecting the cut '$cutName[$cutIndex]'!\n";
	    print "Aborting...\n";
	    exit 1;
	}
	my ($ceff, $cerr, $geff, $gerr, $weff, $werr) = &get_cut_efficiencies($cutIndex);
	
	$ceffString = sprintf("%0.3f&#177;%0.3f%%", 100*$ceff, 100*$cerr);
	$geffString = sprintf("%0.3f&#177;%0.3f%%", 100*$geff, 100*$gerr);
	$weffString = sprintf("%0.3f&#177;%0.3f%%", 100*$weff, 100*$werr);
	
	$outline = "$1\n<TD align=left>\n$cutName[$cutIndex]\n</TD>\n<TD TITLE=\"Number of events\">\n$cutCount[$cutIndex]\n</TD><TD TITLE=\"Selection efficiency\">\n$ceffString\n</TD><TD TITLE=\"Global efficiency\">\n$geffString\n</TD>\n</TD><TD TITLE=\"Global efficiency corrected by the event weight\">\n$weffString\n</TD>\n</TR>\n";
	$cutIndex++;
	
	
    }elsif( $line=~m@^(<TR.*?>)\s*<TD align=left>\s*(\w+.*?)\s*</TD>\s*<TD TITLE="Number of events">\s*\d+\s*</TD>\s*<TD TITLE=".*weight">\s*.*?\s*</TD>\s*@i  ){
	###Matches Weight Fromat###
	
	if( $is_a_weight[$cutIndex] == 0 ){
	    print "The cut '$2' has the format of a weight, but was not set as a weight!\n";
	    print "Aborting...\n";
	    exit 1;
	}
	if($2 ne $cutName[$cutIndex]){
	    print "Found the weight '$2', but was expecting the weight '$cutName[$cutIndex]'!\n";
	    print "Aborting...\n";
	    exit 1;
	}
	
	my ($weight_ave, $weightErr_ave) = &get_weight_ave($cutIndex);
	$ceffString = sprintf("%0.3f&#177;%0.3f", $weight_ave, $weightErr_ave);
	
	# Update the global weight variables
	&update_gweight($weight_ave, $weightErr_ave);
	
	$outline = "$1\n<TD align=left>\n$cutName[$cutIndex]\n</TD>\n<TD TITLE=\"Number of events\">\n$cutCount[$cutIndex]\n</TD> <TD TITLE=\"Average weight\">\n$ceffString\n</TD> <TD> &#160;</TD><TD>&#160;</TD> \n</TR>\n";
	$cutIndex++;
	
    }else{
	#does not match a format
	$outline = $line; #copy this chunk
	if($cutIndex > $#cutName && !$note_printed){
	    $note_printed = 1;
	    print OUTFILE "NOTE: weight errors are not merged correctly, they are just averaged.<BR>\n";     
	}
    }
    
    print OUTFILE $outline;
}
close INFILE;
close OUTFILE;  # Done making HTML file

if($verbose){ print "Files successfully merged: @filesMerged \n";}
exit 0;


### Below are all the subroutines

# Print a message saying how to get more help
sub helpmessage{
    print "For help and usage try: $0 -h\n";
}

# This subroutine prints the usage info for this script
sub printusage{
    print <<DONE;
This script merges efficiency html files created by the Stat processor.  It was
designed for the simple case where the efficiency files contain a single set of 
selections (ie. a single stat sample).  It does not merge systematics or files 
with multiple stat samples (I\'m not sure what it would do).

Usage:

You can specify each input file on the command line:
 $0 input1.html input2.html input3.html ...

Or you can pass a list of files to merge:
 $0 -list=merge_these.list

Additional options:

 -out=output.html : Specify the name of the resulting output file (default is merged.html).

 -f  or  -force   : Do not prompt to overwrite existing output file(s).

 -h  or  -help    : Print this usage summary.

 -t  or  -text    : Also create a plain text file (with the same base name as the output html).

 -l  or  -latex   : Also create a latex file (with the same base name as the output html).

 -v  or  -verbose : Verbose printout during execution.

Author: Joe Haley, cooljoe\@fnal.gov
Date: Sept. 2006
Version: 1.0
DONE
}

sub get_weight_ave {
    my ($i) = @_;
    my $weight_ave    =  $thisweightxCount[$i]/$cutCount[$i];    # Average weight
    my $weightErr_ave =  $thisweightErrxCount[$i]/$cutCount[$i]; # Average weight err
    return ($weight_ave, $weightErr_ave);
}
sub update_gweight {
    my ($newWeight, $newWeightErr) = @_;
    $gweightErr =  sqrt(($newWeight*$gweightErr)**2 + ($gweight*$newWeightErr)**2) ;
    $gweight    =  $gweight*$newWeight;
    #print "Global weight set to: $gweight+-$gweightErr\n";
}

sub get_cut_efficiencies {
    my ($i) = @_;
    # cut efficiency
    my $Ceff =  $cutCount[$i]/$cutCount[$i-1];
    my $Cerr =  sqrt($Ceff*(1.0-$Ceff)/$cutCount[$i-1]);
    
    # global efficiency
    my $Geff = $cutCount[$i]/$cutCount[0];
    my $Gerr = sqrt($Geff*(1.0-$Geff)/$cutCount[0]);
    
    # weighted efficiency = gweight*geff
    # weighted eff error = sqrt( (gweight*gerr)^2 + (geff*gweightErr)^2 )
    my $Weff = $gweight*$Geff;
    my $Werr = sqrt( ($gweight*$Gerr)**2 + ($Geff*$gweightErr)**2 );

    return ($Ceff, $Cerr, $Geff, $Gerr, $Weff, $Werr);
}

sub clean_latex {
    my ($string) = @_;

    $string =~ s/_/\\_/g;
    $string =~ s/>/\$>\$/g;
    $string =~ s/</\$<\$/g;
    return $string;
}
