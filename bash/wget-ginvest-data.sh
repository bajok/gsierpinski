#! /bin/bash

#
#       wget-ginvest-data
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


#
# initially this script will not download zip files.
# just fill with lacking daily files from last month


#
# will check local data integrity


#
# data sources definitions

DATA_NEWCONNECT_URI="http://bossa.pl/pub/newconnect/mstock/sesjancn/"

DATA_GPW_URI="http://bossa.pl/pub/metastock/mstock/sesjaall/"


#
# some colors

red="\033[0;31m"
green="\033[0;32m"
yellow="\033[0;33m"
blue="\033[0;34m"
magenta="\033[0;35m"
cyan="\033[0;36m"
white="\033[0;37m"
boldmagenta="\033[1;35m"
reset="\033[0;0;0m"


#
# usage

if [ "$1" == "" -o "$1" == "--help" ];
then
  echo -ne "$boldmagenta""usage: ""$reset\n"
  echo -ne "variables: \n"
  echo -ne "<DATA> : NEWCONNECT|GPW \n"
  echo -ne "$0 - update from last daily file to   \n"
  echo -ne "\n"
# echo -ne "TODO: \n"
# exit
  exit
fi

#
# go:

# display pattern

echo -ne "$PRINT_GREP_PATTERN"
for ((iter=$pattern_length; iter<$((1*pattern_separator_length/4)); iter++)); 
  do echo -ne " "; 
done
echo -ne "$reset""\n"

# for each file
# display (or not) results

for file in $FILELIST
# TODO: if file other than backup file...
# if [ "$file" 
do
  #echo "$DIRECTORY"/"$file"
  SEARCH_RESULT=`cat "$DIRECTORY""$file" | egrep -n $GREP_SWITCHES $GREP_PATTERN`
  if [ -z "$SEARCH_RESULT" ]
  then
    echo -ne "                                                            \r"
  else
    if [ "$1" != "--onefile" ]; then # if called from make-colorized.awk script this line is suppresed
    echo -ne "$hl_green""  filename:   ""$hl_green2""$file""  $reset""\n"  # | gawk -f $awkgrepfile
    fi
    echo -ne "$SEARCH_RESULT" | gawk -f $awkgrepfile
  fi
done

# display pattern

echo -ne "$PRINT_GREP_PATTERN_DARK"
for ((iter=$pattern_length; iter<$((1*pattern_separator_length/4)); iter++)); 
do 
  echo -ne " ";
done
echo -ne "$reset""\n"


