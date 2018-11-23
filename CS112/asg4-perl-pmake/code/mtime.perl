#!/usr/bin/perl
# $Id: mtime.perl,v 1.1 2018-11-06 18:50:44-08 - - $
#
# NAME
#    older.perl - check whether a pair of files are older or newer
#
# SYNOPSIS
#    older.perl filename...
#
# DESCRIPTION
#    The two files' modification times are compared and a
#    relationship is printed.
#

use strict;
use warnings;
use POSIX qw(strftime);
$0 =~ s|.*/||;

sub mtime ($) {
   my ($filename) = @_;
   my @stat = stat $filename;
   return @stat ? $stat[9] : undef;
}

sub fileinfo ($) {
   my ($filename) = @_;
   my $mtime = mtime $filename;
   print "$filename: ";
   if (defined $mtime) {print strftime "%c\n", localtime $mtime}
                  else {print "$!\n"}
   return $mtime;
}

for my $filename (@ARGV) {
   unless (-e $filename) {
      printf STDERR "$0: $filename: $!\n";
   }else {
      my $mtime = mtime $filename;
      my $ctime = strftime "%c", localtime $mtime;
      printf "%-20s %12d %s\n", $filename, $mtime, $ctime;
   }
}

