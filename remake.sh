#! /bin/bash

#
#
#       remake
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

red="\033[0;31m"
green="\033[0;32m"
yellow="\033[0;33m"
blue="\033[0;34m"
magenta="\033[0;35m"
cyan="\033[0;36m"
white="\033[0;37m"

boldyellow="\033[1;33m"
boldblue="\033[1;34m"

reset="\033[0;0;0m"
separator=" -- -- -- -- -- -- -- -- -- -- -- -- -- .. -- -- -- -- -- -- -- -- -- -- -- -- --"
shortseparator=" -- -- -- -- -- -- -- -- -- -- -- -- -- "

# current project
projectdir=`pwd`
projectname="gsierpinski"


awk_binary_path="/bin/gawk"
PATH_AWK="awk"
awkmakefile="$PATH_AWK""/make-colorized.awk"
awkprojectfile="$PATH_AWK""/""$projectname""-colorized.awk"

SLEEP_FLAG="yes"
sleep_time_after_compilation="90"

colorize="yes"

# trap ctrl-z so it sleeps until enter is pressed



trap pause SIGINT

function pause() {
  echo -ne "$magenta"" pressed...  ""$yellow""pause\n\n"
  echo -ne "$boldblue""press ""$white""enter""$boldblue"" to exit ""$reset"
  read
  exit
}



if [ -f $awkmakefile -a -f $awkprojectfile -a -f $awk_binary_path ]
then
  colorize="yes"
  echo awk files found... colorizing turned on by default.
  echo                    colorized run provides also some of so called features...
else
  colorize="nocolor"
  echo no gawk and/or awk scripts present. standard output.
fi


function make_tar {
  today=`date +%Y%m%d`
  current_tar_name=`echo "$projectname""-""$today"".tar"`
  current_filename="$current_tar_name"".gz"
  if [ -f tar/$current_filename ]; then
    echo
  else
    # program sources
    cfiles=`ls src/*.c`
    headers=`ls src/*.h`
    awkfiles=`ls awk/*.awk`
    # additional files to archive
    miscfiles="Makefile remake.sh remake.sh-in-new-terminal.sh grep-files.sh ""$projectname"
    tar -cf tar/$current_tar_name $cfiles $headers $awkfiles $miscfiles
    gzip tar/$current_tar_name
    echo created new $current_filename
  fi
}


function sleep_then {
  sleep_time=$1
  echo -ne "$boldblue""press ""$white""ctrl-c ""$boldblue""to stop timer and pause\n"
  tclr=`echo -ne "$boldyellow"`
  timer_prefix=`echo -ne "$blue""    ~   ""$tclr"`

  # iterate each second
  for ((timer=$sleep_time; timer>0; timer--))
  do
    min=$((timer/60))
    sec=$((timer-(min*60)))
    if [ "$sec" -lt "10" ]
    then
        sec=`echo "0""$sec"`
    fi

    # printing with second blinking :)
    if [ $((timer%2)) == 0 ]
    then
      echo -ne "$timer_prefix""$min""$boldblue"":""$tclr""$sec""            \r"
    else
      echo -ne "$timer_prefix""$min""$boldblue"".""$tclr""$sec""            \r"
    fi
    sleep 1
  done
}

# -----------------------------------------------------------------------------

#
# lets run

#cd $projectdir/$projectname
echo -ne "\n""hint: type \"remake nocolor\" "
echo -ne "or simply \"make\" to turn off colorized output.\n\n"

OBJ_DIR=`cat Makefile | grep "OBJ_PATH=" | cut -f2 -d=`
BIN_DIR=`cat Makefile | grep "BIN_PATH=" | cut -f2 -d=`


if [ -d "$OBJ_DIR" ]; then
  echo obj directory found...
else 
  mkdir $OBJ_DIR
fi

if [ -d "$BIN_DIR" ]; then
  echo bin directory found...
else 
  mkdir $BIN_DIR
fi


#
# this does not need to shine so much

if [ "$colorize" = "nocolor" ]
then
  echo current directory: $projectdir/$projectname
  echo
  make clean
  make all
  #./bin/$projectname
  # when symbolic link is present
  ./$projectname
# exit
  exit
fi

#
# in case of only running (after build 

if [ "$1" = "run" ]
then 
  ./$projectname 2>&1 | gawk -f $awkprojectfile
# exit  
  exit
fi

#
# building by default

echo -ne "$blue""\ncurrent directory: $yellow $projectdir/$projectname $reset\n\n"

#
# making

echo -ne "$blue""$separator\n"
echo -ne "$white""make clean 2>&1 | gawk -f $awkmakefile""\n"
echo -ne "$blue""$shortseparator"
make clean 2>&1 | gawk -f $awkmakefile

echo -ne "$blue""$separator\n"
echo -ne "$white""make all 2>&1 | gawk -f $awkmakefile""\n"
echo -ne "$blue""$shortseparator"
make all   2>&1 | gawk -f $awkmakefile



#
# if successful compilation

if [ -f bin/$projectname ]; then
  echo -ne "$blue""$separator""\n"

  # binary is placed in: ./bin/$projectname
  if [ -f ./$projectname ]; then
    echo link to binary is present...
  else
    ln -s ./bin/$projectname ./$projectname
  fi

  ./$projectname 2>&1 | gawk -f $awkprojectfile
  # after execution
  if [ "$SLEEP_FLAG" = "yes" ]
  then
    if [ -d tar ]; then
      make_tar
    else
      mkdir tar
      make_tar
    fi
    sleep_then $sleep_time_after_compilation
  fi

#
# when compilation fails

else
  echo -ne "$red""\nthere was an error during building "
  echo -ne "$yellow"" $projectname  ""$red""source.\n"
  if [ "$SLEEP_FLAG" = "yes" ]
  then
    sleep_then $sleep_time_after_compilation
  else
    echo -ne "$white""\nhit enter...\n""$reset"
    read
  fi
fi

