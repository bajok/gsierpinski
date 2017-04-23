#! /bin/bash

#
#       grep-files
#       
#       Copyright 2009 Przemysław Dużyk <przemyslaw.duzyk@gmail.com>
#       
#       This program is free software; you can redistribute it and/or modify
#       it under the terms of the GNU General Public License as published by
#       the Free Software Foundation; either version 2 of the License, or
#       (at your option) any later version.
#       
#       This program is distributed in the hope that it will be useful,
#       but WITHOUT ANY WARRANTY; without even the implied warranty of
#       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#       GNU General Public License for more details.
#       
#       You should have received a copy of the GNU General Public License
#       along with this program; if not, write to the Free Software
#       Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#       MA 02110-1301, USA.
#


DIRECTORY="$1"
FILELIST=`ls $DIRECTORY`
GREP_PATTERN="$2"
GREP_SWITCHES=" $3"" $4"" $5"

PATH_AWK="awk"
awkgrepfile="$PATH_AWK""/grep-colorized.awk"

red="\033[0;31m"
green="\033[0;32m"
yellow="\033[0;33m"
blue="\033[0;34m"
magenta="\033[0;35m"
cyan="\033[0;36m"
white="\033[0;37m"
boldmagenta="\033[1;35m"
hl_blue="\033[1;34;40m"
hl_green="\033[1;32;40m"
hl_magenta="\033[1;37;45m"
reset="\033[0;0;0m"

PRINT_GREP_PATTERN="$hl_magenta""  $GREP_PATTERN  "$reset"\n"

#
# usage

if [ "$1" = "" -o "$2" = "" ]
then
  echo -ne "usage is:   $0 [directory] [pattern]  <grep switches>\n"
  echo -ne "example:    $0 src         glViewPort -B1\n"
  echo -ne "\n"
  echo -ne "TODO: directory may be ommited if pattern is provided in single quotation mark\n"
  echo -ne "TODO: pattern may passed to gawk for keyword colorizing\n"
# exit
  exit
fi

#
# go:

echo -ne "\n""$PRINT_GREP_PATTERN""\n\n"

for file in $FILELIST
# TODO: if file other than backup file...
# if [ "$file" 
do
  SEARCH_RESULT=`cat "$DIRECTORY"/"$file" | grep -n $GREP_SWITCHES -e $GREP_PATTERN`
  if [ -z "$SEARCH_RESULT" ]
  then
    echo -ne "                                                            \r"
  else
    echo -ne "$hl_green""  filename:   ""$hl_blue""$file""  $reset""\n"  # | gawk -f $awkgrepfile
    echo -ne "$SEARCH_RESULT""\n" | gawk -f $awkgrepfile
  fi
done

echo -ne "$reset""\n"

