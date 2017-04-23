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
hl_green="\033[0;32;40m"
hl_green2="\033[1;32;40m"
hl_grep_string="\033[1;37;44m"
hl_grep_string_dark="\033[1;30;44m"
reset="\033[0;0;0m"


# if one file search
if [ "$1" == "--onefile" ]; then # TODO: check list length, currently used for 1 entry
  GREP_PATTERN="$3"
  GREP_SWITCHES="" # not used
  #GREP_SWITCHES=" $4"" $5"" $6"
  if [ -f "$2" ]; then # then second param shall be filepath
  FILELIST="$2"
  fi
else # below
  # if $1 == all
  #GREP_PATTERN="'$1 $2 $3 $4 $5 $6 $7'"
  GREP_PATTERN="$1 $2 $3 $4 $5 $6 $7"

  # use grep switches when --switch option is used?
  # GREP_SWITCHES=" $2"" $3"" $4"
  GREP_SWITCHES=""
  
  DIRECTORY="src"
  # if directory is a file - list this file
  if [ -d "$DIRECTORY" ]; 
  then 
    FILELIST=`ls $DIRECTORY`
    DIRECTORY="$DIRECTORY""/"
  else # probably it is a source file
    if [ -f "$DIRECTORY" ];
    then
      FILELIST=`ls $DIRECTORY`
      DIRECTORY=""
    else
      echo -ne "$red""file not found or something else""$reset\n"
      exit
    fi
  fi
fi # fi one file

# get number of spaces to fill
pattern_separator_length="80"
pattern_length=`echo $GREP_PATTERN | wc -c`
pattern_fill_spaces=$((pattern_separator_length-pattern_length))
PRINT_GREP_PATTERN="$hl_grep_string""  $GREP_PATTERN  "
PRINT_GREP_PATTERN_DARK="$hl_grep_string_dark""  $GREP_PATTERN  "


#
# usage

if [ "$1" == "" -o "$1" == "--help" ]
then
  echo -ne "$boldmagenta""usage: ""$reset"" old info!  \n"
  echo -ne "$0 src '\\-.data'       to look for '->data' \n"
  echo -ne "usage is:   $0 [directory] [pattern]  <grep switches>\n"
  echo -ne "example:    $0 src         glViewPort -B1\n"
  echo -ne "example:    $0 src/main.c  glViewPort -B1\n"
  echo -ne "example:    $0 src         glFrust*\n"
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
  if [ "$1" == "--whatever-currently-not-used" ]; then
    SEARCH_RESULT=`cat "$DIRECTORY""$file" | egrep -n \'$GREP_PATTERN\'`
  else # use no switches take all words
    SEARCH_RESULT=`cat "$DIRECTORY""$file" | egrep -n "$*"`
  fi
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


