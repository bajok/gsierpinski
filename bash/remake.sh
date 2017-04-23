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

SCRIPT_VER="0.9.52"

# 
# a one shall have at least 120 columns wide terminal. or something.

##################################################################################################
#
# remake

today=`date +%Y%m%d`

##################################################################################################
#
# current project variables

projectname=`cat Makefile | grep 'PROGRAM_NAME = ' | cut -f2 -d= | tr -d " "`
projectdir=`pwd`
projectver=`cat src/main.c | grep define | grep PROGRAM_VER | cut -f5 -d" "`
OBJ_DIR=`cat Makefile | grep "OBJ_PATH=" | cut -f2 -d=`
BIN_DIR=`cat Makefile | grep "BIN_PATH=" | cut -f2 -d=`

#
# archiving

TAR_DIR="tar" 
# each day new archive file: filename is date based
# these variables may be changed in make_tar function and output file may contain exit code
TAR_FILE_TEMP=`echo "$projectname""-""$today"".tar"`
GZIP_FILE_OUT="$TAR_FILE_TEMP"".gz"

# there is no SRC_DIR variable
# in case of use another sources directory src may be just a symbolic link to it

#
# select files to build

makediff_file="make.diff"
makediff_file_old="make.diff.old"
build_file="build.files"

#
# gawk support 

awk_binary_path="/bin/gawk"
gawkcmd="gawk --posix "
# if no gawk installed there is no colorize support (and its features)
PATH_AWK="awk"
awkmakefile="$PATH_AWK""/make-colorized.awk"
awkprojectfile="$PATH_AWK""/""$projectname""-colorized.awk"

##########

#
# defaults

sleep_time_after_compilation="3"
colorize="yes"
SLEEP_FLAG="yes"

##################################################################################################
#
# colors

red="\033[0;31m"
green="\033[0;32m"
yellow="\033[0;33m"
blue="\033[0;34m"
magenta="\033[0;35m"
cyan="\033[0;36m"
white="\033[0;37m"
boldgreen="\033[1;32m"
boldyellow="\033[1;33m"
boldblue="\033[1;34m"
boldmagenta="\033[1;35m"
boldwhite="\033[1;37m"
rederror="\007\033[0;37;41m"
hlgreenwhite="\033[1;37;42m"
hlblueyellowb="\033[1;33;44m"
hlblueyellow="\033[0;33;44m"
hlbluewhite="\033[0;37;44m"
hlbluewhiteb="\033[1;37;44m"
hl_separator="\033[0;37;40m"
hl_scriptn1="\033[1;37;45m"
hl_scriptn2="\033[0;37;45m"
reset="\033[0;0;0m"
SAVE_CURSOR_POS="\033[s"
LOAD_CURSOR_POS="\033[u"


##################################################################################################
#
# check obj/bin dirs

#
# getting obj and bin dirs

OBJ_DIR=`cat Makefile | grep "OBJ_PATH=" | cut -f2 -d=`
BIN_DIR=`cat Makefile | grep "BIN_PATH=" | cut -f2 -d=`

if [ -d "$OBJ_DIR" ]; then
  echo -ne "$hl_scriptn1"" \n" # obj directory found...
else 
  mkdir $OBJ_DIR
fi

if [ -d "$BIN_DIR" ]; then
  echo -ne "$hl_scriptn1"" \n" # bin directory found...
else
  mkdir $BIN_DIR
fi


##################################################################################################
#
# print header or help also

echo -ne "$hl_scriptn1""remake.sh""$hl_scriptn2"" ver. $SCRIPT_VER""$reset\n\n"
echo -ne "$boldblue""current project:   ""$boldyellow""$projectname""$reset\n"
echo -ne "$boldblue""project version:   ""$boldwhite""$projectver""$reset\n"
echo -ne "$boldblue""current directory: ""$white""$projectdir""$reset\n"
echo -ne "$boldblue""sources directory: ""$white""src""$reset\n"
echo -ne "$boldblue""objects directory: ""$white""$OBJ_DIR""$reset\n"
echo -ne "$boldblue""binary  directory: ""$white""$BIN_DIR""$reset\n"


if [ "$1" == "--help" -o "$1" == "-h" -o "$1" == "help" ]; then

  #
  # descriptions

  DESC_REMAKE="$yellow""recompile only modified sources, link and execute""$reset\n"
  DESC_REMAKE_ALL="$yellow""recompile all sources: remove ""$blue""$makediff_file""$yellow"" (force fresh build)""$reset\n"
  DESC_REMAKE_BUILDFILES="$yellow""recompile only given sources: ""$blue""buildfiles=file1:file2... ""$yellow""and exit""$reset\n"
  DESC_REMAKE_BF="$yellow""same, but also link and execute; ""$blue""bf=*:pattern""$yellow"" build files with name containing pattern""$reset\n"
  DESC_REMAKE_SLEEP="$yellow""sleep after program termination""$reset\n"
  DESC_REMAKE_NOCOLOR="$yellow""turn off colorizing (but not for help)""$reset\n"
  DESC_REMAKE_RUN="$yellow""just execute program""$reset\n"
  DESC_REMAKE_REMOVETAR="$yellow""removes today's archive (compile, make new archive, execute)""$reset\n"
  DESC_REMAKE_VERIFY="$yellow""check if all compiled objects exist""$reset\n"
  DESC_REMAKE_NEXT="$yellow""recompile only first failed file (""$white""\$ remake.sh next warning""$yellow""  deletes file with warnings)""$reset\n"
  DESC_REMAKE_CLEAN="$yellow""clean objects (and exit)""$reset\n"

  echo -ne "$boldmagenta""\n  usage:\n""$reset\n"
  echo -ne "$boldblue""  compile, link and run options:\n"
  echo -ne "$white""  $ remake             "$DESC_REMAKE
  echo -ne "$white""  $ remake next        "$DESC_REMAKE_NEXT
  echo -ne "$white""  $ remake all, -a     "$DESC_REMAKE_ALL
  echo
  echo -ne "$boldgreen""  only execute:\n"
  echo -ne "$white""  $ remake run         "$DESC_REMAKE_RUN
  echo
  echo -ne "$boldblue""  build tools:\n"
  echo -ne "$white""  $ remake clean       "$DESC_REMAKE_CLEAN
  echo -ne "$white""  $ remake buildfiles= "$DESC_REMAKE_BUILDFILES
  echo -ne "$white""  $ remake bf=         "$DESC_REMAKE_BF
  echo -ne "$white""  $ remake removetar   "$DESC_REMAKE_REMOVETAR
  echo -ne "$white""  $ remake verify, -v  "$DESC_REMAKE_VERIFY
  echo
  echo -ne "$boldblue""  miscellaneous:\n"
  echo -ne "$white""  $ remake sleep       "$DESC_REMAKE_SLEEP
  echo -ne "$white""  $ remake nocolor     "$DESC_REMAKE_NOCOLOR
  echo -ne "$white""  $ remake help, -h, --help"
  echo
  echo -ne "$green""  examples:\n"
  echo -ne "$white""  $ remake next warning\n"
  echo -ne "$white""  $ remake buildfiles=main:callbacks:widgets\n"
  echo -ne "$white""  $ remake bf=*:widgets\n"
  echo -ne "$white""  $ remake sleep nocolor\n"
  echo -ne "$white""  $ remake all sleep nocolor\n"
  echo -ne "$reset\n"

  if [ "$1" == "--help" ]; then
    echo -ne "$magenta""note: only sleep and nocolor flags may be used as 2nd parameter\n""$reset"
    echo -ne "$magenta""note: whenever waiting for enter ctrl-c may be pressed to terminate script (e.g. tar removal)\n\n""$reset"
  fi

  if [ "$1" == "--help" ]; then 
    echo "todo: remove make.diff file if number of objects != number of *.c files"
    echo "todo: add diff option that compares current source files with extracted archive (by date)"
    echo "todo: remove step of recompiling [main.c] source file when calling    $ ./remake.sh"  
    echo "todo: add packdata option with param: latest listings"   
    echo "todo: use \"\$today\" variable to update main.c file with current version, e.g. 20100425"
  fi

  echo -ne "$reset\n"
  exit

fi

##################################################################################################
#
# flags

# set "sleep after compilation" flag
if [ "$1" == "sleep" -o "$2" == "sleep" ]; then
  SLEEP_FLAG="yes"
else
  SLEEP_FLAG="no"
fi

# colorize flag
if [ "$1" == "nocolor" -o "$2" == "nocolor" -o "$3" == "nocolor" ]; then
  colorize="nocolor"
fi


##################################################################################################
#
# functions

#
# verify - link if all objects present (ls c files and find object for them)

#   ~~~~~~~~~~~~~~~~~~~~~
#        verify
#   ~~~~~~~~~~~~~~~~~~~~~
function verify() {

  MAD_OBJECTS="4"

  OBJECTS=`ls src/*.c | cut -f2 -d/ | cut -f1 -d.`
  OBJ_ERR="0"
  OBJ_BAD_LIST=""
  #SAVE_CURSOR_POS="\033[s"
  #LOAD_CURSOR_POS="\033[u"
  #NO_FILE_STRING=`echo -ne "\033[sno \033[u\033[40C 123\n"`
  ERR_COLUMN="\033[60C"
  FIRST_BAAAD_FILE="hope_nobody_would_ever_call_a_file_like_that"

  echo
  echo -ne "$hlblueyellowb"" :: verifying objects...$reset\n"

  for file in $OBJECTS; do
    objfile="$OBJ_DIR/""$file"".o"
    if [ -f $objfile ]; then
      O_LINEUP="\033[1A"
      echo -ne "$green""$objfile""$reset$O_LINEUP\n"
    else
      if [ "$FIRST_BAAAD_FILE" == "hope_nobody_would_ever_call_a_file_like_that" ]; then
        FIRST_BAAAD_FILE="$file"
      fi
      if [ "$OBJ_ERR" -eq "0" ]; then
        OBJ_BAD_LIST=$file
      else
        OBJ_BAD_LIST=`echo "$OBJ_BAD_LIST"" ""$file"`
      fi
      OBJ_ERR=$((OBJ_ERR+1))
      if [ "$OBJ_ERR" -lt "$((MAD_OBJECTS+1))" ]; then # printing only several if many..
        echo -ne "$rederror""\033[s""$objfile""$red""\033[u""$ERR_COLUMN""no such file""$reset\n"
      fi
      # else continue counting
    fi
  done

  if [ "$OBJ_ERR" -gt "$MAD_OBJECTS" ]; then
    echo -ne "$rederror""too many failed objects for this screen to handle\n"
  fi

  if [ "$OBJ_ERR" -gt "0" ]; then
    echo -ne "\n""$rederror""build incomplete!""\n$reset\n"
    echo -ne "$red""may pick another try with a one:\n$reset"
    echo -ne "$yellow""$0 buildfiles=""$blue""$FIRST_BAAAD_FILE""\n$reset"

#    if [ "$OBJ_ERR" -lt "$((MAD_OBJECTS+1))" ]; then # printing only if few errors
#    for file in $OBJ_BAD_LIST; do
#      echo -ne "$yellow""$0 buildfiles=""$blue""$file""\n$reset"
#    done
#    fi

    echo -ne "$red""\nor may want all:\n"
    echo -ne "$yellow""$0 buildfiles="
    for file in $OBJ_BAD_LIST; do
      echo -ne "$blue""$file:"
    done
    echo -ne "\b $reset\n\n"
    # and to execute afterall
    #echo -ne "\b && $0\n"

    interrupt
    exit
  else
    if [ "$1" == "and_print_remakes" ]; then
    echo -ne "$boldmagenta""recompile:\n$reset"
    for file in $OBJECTS; do
      echo -ne "$yellow""$0 buildfiles=""$blue""$file""\n$reset"
    done
    fi
  fi
}


#
# trap ctrl-c so it sleeps until enter is pressed

#   ~~~~~~~~~~~~~~~~~~~~~
#    pause
#   ~~~~~~~~~~~~~~~~~~~~~
trap pause SIGINT
function pause() {
  echo -ne "$magenta"" pressed...  ""$boldyellow""aborting...\n\n"
  # this lines allows to stay terminal alive
  echo -ne "$boldblue""press ""$white""enter""$boldblue"" to exit ""$reset"
  read
  exit
}

function interrupt() {
  echo -ne "$boldblue""press ""$white""enter""$boldblue"" to continue or "
  echo -ne "$white""Ctrl+C""$boldblue"" to abort\n""$reset"
  read
}

#
# turn off colorizing if awk files not present

#   ~~~~~~~~~~~~~~~~~~~~~
#     colorize    check
#   ~~~~~~~~~~~~~~~~~~~~~
if [ "$colorize" == "yes" ]; then
  if [ -f $awkmakefile -a -f $awkprojectfile -a -f $awk_binary_path ]; then
    colorize="yes"
#    echo awk files found... colorizing turned on by default.
#    echo                    colorized run provides also some sort of so called features...
  else
    colorize="nocolor"
    echo no $gawkcmd and/or awk scripts present. standard output.
  fi
else
  echo turning off this fancy color support
fi


# make archive once a day 
# this function is called after successful build

###############################################################################
#
# make_tar

#   ~~~~~~~~~~~~~~~~~~~~~
#        make_tar
#   ~~~~~~~~~~~~~~~~~~~~~
function make_tar() {
#  today=`date +%Y%m%d`
#  TAR_FILE_TEMP=`echo "$projectname""-""$today"".tar"`
#  GZIP_FILE_OUT="$TAR_FILE_TEMP"".gz"

  # binary executed with segfault
  if [ "$1" == "segfault" ]; then
    TAR_FILE_TEMP=`echo "$projectname""-""$today""-segfault.tar"`
    if [ -f "$TAR_DIR/$TAR_FILE_TEMP"".gz" ]; then
      echo -ne "$red""removing segfaulted source archive...""$reset\n"
      echo rm $TAR_DIR/$TAR_FILE_TEMP".gz"
      rm $TAR_DIR/$TAR_FILE_TEMP.gz
    fi
  fi

  GZIP_FILE_OUT="$TAR_FILE_TEMP"".gz"

  if [ -f $TAR_DIR/$GZIP_FILE_OUT ]; then
    echo -ne "$green""daily archive present. \n"
  else #                                                                         ### create new archive ###
       # usually if segfault was noticed, this is called because $GZIP_FILE_OUT == $projectname-$today.gz
       # so archive for segfaulted source is repeated and .gz file deleted
    # program sources
    cfiles=`ls src/*.c`
    cifiles=`ls src/*.cincl`
    headers=`ls src/*.h`
    macros=`ls src/*.def`
    # script files
    awkfiles=`ls awk/*.awk`
    bashfiles=`ls bash/*.sh`
    scriptfiles=" $awkfiles "" $bashfiles "
    # additional files to archive
    miscfiles="Makefile remake remake.sh-in-new-terminal.sh grepfiles wget-ginvest-data ""$projectname"

  # tar
    tar -cf $TAR_DIR/$TAR_FILE_TEMP $cfiles $cifiles $headers $macros $scriptfiles $miscfiles

  # gzip
    gzip $TAR_DIR/$TAR_FILE_TEMP

  fi

  if [ -f $TAR_DIR/$GZIP_FILE_OUT ]; then 
    echo -ne "$blue""build archive:""$reset\n"
    _archive_namestr=`ls -hsQ $TAR_DIR/$GZIP_FILE_OUT | cut -f2 -d\"`
    _archive_propstr=`ls -lah $TAR_DIR/$GZIP_FILE_OUT | cut -f5-8 -d" "`
    echo -ne "$boldwhite""$_archive_namestr""$reset\n"
    echo -ne "$blue""$_archive_propstr""$reset\n"
  else
    echo -ne "rederror""something strange happened!""$reset\n"
  fi
}


# useful when building in newly created terminal (stays for a while after program exit)
#   ~~~~~~~~~~~~~~~~~~~~~
#        sleep_then
#   ~~~~~~~~~~~~~~~~~~~~~
function sleep_then() {
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

##################################################################################################

##################################################################################################
#
# special runs
#
##################################################################################################


# remake devel reminder
echo
echo -ne "$hlblueyellow""remake devel reminder\n$reset\n"
echo -ne "$magenta""TODO: ""$boldmagenta""remake next warning sucks\n"
echo -ne "$magenta""TODO: ""$boldmagenta""remake daily changes sucks\n"
echo no build.file possibly causes these errors
echo but everything else shall work 
echo
#interrupt


#   remove makediff_file for fresh build
#   ~~~~~~~~~~~~~~~~~~~~~
#             all
#   ~~~~~~~~~~~~~~~~~~~~~
if [ "$1" == "all" -o "$1" == "-a" ]; then
  if [ "$2" == "G" ]; then
    _bf=" GL GTK DATA "
    echo -ne "$hlgreenwhite"" :: \n :: recompiling $_bf ...\n :: "
    echo -ne "$red""errrrrrr"
    #$0 bf=*:GL:GTK:DATA
    bf="*:GL:GTK:DATA"
    #exit
    IS_BUILDFILES="bf"
  else
    echo -ne "$hlgreenwhite"" :: \n :: recompiling all source files...\n :: "
    echo -ne "$reset\n$red""rm ""$boldblue""$makediff_file""$reset"
    rm $makediff_file
    #rm $build_file # after.....
  fi
fi

#   ~~~~~~~~~~~~~~~~~~~~~
#            run
#   ~~~~~~~~~~~~~~~~~~~~~
if [ "$1" == "run" ]; then
   echo
   echo -ne "$hlgreenwhite"" :: \n :: execute mode...\n :: "
   echo -ne "$reset"
   echo
  ./$projectname 2>&1 | $gawkcmd -f $awkprojectfile
# exit  
  exit
fi

NOPE="$boldmagenta""nope.\n$reset"
#   ~~~~~~~~~~~~~~~~~~~~~
#            clean
#   ~~~~~~~~~~~~~~~~~~~~~
if [ "$1" == "clean" ]; then
  echo -ne "$magenta""\nmr proper requested""$yellow""...\n"
  echo -ne "$white""delete objects?  ""$green""[y] ""$white""/""$magenta"" n\b""$reset"
  read keypressed
  if [ "$keypressed" == "n" ]; then
    echo -ne $NOPE
  else
    echo -ne "$boldmagenta""deleting objects...\n$reset"
    rm $OBJ_DIR/*
  fi
  echo -ne "$white""delete binary?  ""$green""[y] ""$white""/""$magenta"" n\b""$reset"
  read keypressed
  if [ "$keypressed" == "n" ]; then
    echo -ne $NOPE
  else 
    echo -ne "$boldmagenta""deleting binary...\n$reset"
    rm $BIN_DIR/$projectname
  fi
# exit
  exit
fi

#   ~~~~~~~~~~~~~~~~~~~~~
#             verify
#   ~~~~~~~~~~~~~~~~~~~~~
if [ "$1" = "verify" -o "$1" == "-v" ]; then
  verify "and_print_remakes"
  exit
fi

#
# remove makediff_file for fresh build
# this function need global $TAR_DIR and $GZIP_FILE_OUT variables set

#   ~~~~~~~~~~~~~~~~~~~~~
#             removetar
#   ~~~~~~~~~~~~~~~~~~~~~
if [ "$1" = "removetar" ]; then
  echo -ne "$magenta""\narchive update forced...$reset\n"
  echo -ne "$red""rm ""$boldblue""$TAR_DIR/$GZIP_FILE_OUT""$reset\n\n"
  interrupt
  if [ -f $TAR_DIR/$GZIP_FILE_OUT ]; then
    echo -ne "$boldblue""$TAR_DIR/$GZIP_FILE_OUT""$white"" exists, "$rederror""deleting."$reset\n\n"
    rm $TAR_DIR/$GZIP_FILE_OUT
  else
    echo -ne "$white""no today file to delete.\n"
    exit
  fi
fi


##################################################################################################

##################################################################################################
#
# setup build

#
# prepare build file - if make.diff file exists - compile only modified files
#                      else make clean and compile all

#
# if old file exists and option "next" is NOT used

if [ "$1" != "next" ]; then

  if [ -f $makediff_file ]; then

    # copy file from previous build to old
    cp $makediff_file $makediff_file_old

    # get current file listing
    ls -l --time-style=full-iso src/*.c > $makediff_file
    # or: ls --full-time

    # compare last and and save build files
    diff $makediff_file $makediff_file_old | grep "< " | cut -f2 -d/ | cut -f1 -d. > $build_file

    # if zero size (same files)
    #filesize=`ls -s $build_file | cut -f1 -d" "`
    filesize=`ls -l $build_file | egrep -o ' [[:digit:]]+ [[:digit:]]{2,4}-[[:digit:]]{2}' | cut -f2 -d" "`
    if [ "$filesize" = "0" ]; then
      echo "main" > $build_file
    fi

    rm $makediff_file_old

# else - no makediff_file - chose all files.
  else

    # if NOT just remake (when no makediff file)
    if [ "$1" != "" ]; then
    # build all files - so make clean
    if [ "$colorize" = "yes" ]; then
      make clean 2>&1 | $gawkcmd -f $awkmakefile
      #$0 all
    else
      make clean
    fi

    # save current file listing
    ls -l src/*.c > $makediff_file

    # create build file with all files
    ls src/*.c | cut -f2 -d/ | cut -f1 -d. > $build_file
  fi
  fi
fi


##################################################################################################
#
# next - for cleaning up. remake.sh next warning deletes object if any warning

#
# compile only one file, just after last successfully compiled

# check

if [ "$1" == "next" ]; then

  # all .c sources
  C_SOURCES=`ls src/*.c | cut -f2 -d/ | cut -f1 -d.`
  #echo all c sources: $C_SOURCES

  rm $build_file

  for file in $C_SOURCES; do
    objfile="$OBJ_DIR/""$file"".o"

    if [ -f $objfile ]; then
      echo -ne "$reset"
    else
      # if no object is found create build file and exit loop
      echo $file >> $build_file
    fi
  done

# make 

  echo -ne "\n$hlblueyellowb"" :: \n :: compiling...\n :: $reset""\n\n"
  echo -ne "$boldmagenta""please wait...\n$reset"

  #make compile        2>&1 | $gawkcmd -f $awkmakefile
  make_output=".make_output_log"
  # compile and redirect output to file
  make compile      &> $make_output
  # print 

  cat $make_output | $gawkcmd -f $awkmakefile

  # check warnings 
  if [ "$2" = "warning" ]; then

    has_implicit=`cat $make_output | grep implicit | cut -f2 -d‘ | cut -f1 -d’`
    has_err=`cat $make_output | grep warning`

    max_prints="2"
    for func in `echo $has_implicit`; do
      if [ "$has_implicit" != "" ]; then
        #echo func = $func
        if [ "$max_prints" -gt "0" ]; then
          ./grep_files.sh src $func
        fi
        max_prints=$((max_prints-1))
      fi
    done

    if [ "$has_err" != "" ]; then
      echo -ne "$boldmagenta""removing object...\n$reset\n"
      rm $OBJ_DIR/$buildfile.o
    fi

  fi

  exit
fi


if [ -f $build_file ]; then
  echo -ne "$reset"
else
  echo -ne "$yellow""nothing to recompile at this point. exitting.""$reset\n"
  exit
fi


###########################################
#
# selected files build

###########################################
#
# in case building only some sources .. (makediff file is replaced)

IS_BUILDFILES=`echo $1 | cut -f1 -d=`

if [ "$IS_BUILDFILES" = "buildfiles" -o "$IS_BUILDFILES" = "bf" ]; then

  echo $1 | cut -f2 -d= | tr ":" "\n" > $build_file

  build_file_tmp="$build_file"".tmp"
  if [ -f "$build_file_tmp" ]; then 
    rm "$build_file_tmp"
  fi

  first_build_file=`cat $build_file | sed -n "1p"`
  if [ "$first_build_file" = "*" ]; then           # redo build_file
    bfilepatterns=`cat $build_file | wc -l`
    for ((bfile=1; bfile<$bfilepatterns; bfile++)); do
      pattern=`cat $build_file | sed -n "$((bfile+1))""p"`
      ls src/*"$pattern"*c | cut -f2 -d/ | cut -f1 -d. >> "$build_file_tmp"
    done
    cp "$build_file_tmp" "$build_file"
    echo -ne "\n""$boldblue""$build_file""$white"" contents: \n""$yellow"
    cat $build_file
    echo
    # so user may abort now and
    interrupt
    # automatic exit if any of the files not exists
    for buildfile in `cat $build_file`
    do
      if [ -f "$build_file" ]; then continue
      else 
        exit
      fi
    done
  fi
  
  filesize=`du -b build.files | sed -n 1p | cut -f1`
#  echo $filesize
  if [ $filesize -lt 2 ]; then
    echo -ne "$rederror""no files given!!!""$reset\n"
    exit
  fi
fi


###########################################
#
# printing build files:
# " :: files to recompile: ""$green\n\n"

echo
echo -ne "$hlblueyellowb"" :: files to recompile: ""$green\n\n"
CATBUILDFILE=`cat $build_file`
echo $CATBUILDFILE
echo
b_filecount=`cat $build_file | wc -l`
c_files=`ls -1B src | egrep -c '[.]c\>'`
h_files=`ls -1B src | egrep -c '[.]h\>'`
i_files=`ls -1B src | egrep -c '[.]cincl\>'`
c_filecount="$hlblueyellowb"" | *.c: ""$hlbluewhiteb""$c_files"
h_filecount="$hlblueyellow"" | *.h: $h_files"
i_filecount="$hlblueyellow"" | *.cincl: $i_files | "
ls_src_count="\t\t $hlgreenwhite all sources: $c_filecount""$h_filecount""$i_filecount"
echo -ne "$hlblueyellowb"" :: total: ""$hlbluewhiteb""$b_filecount""$ls_src_count""$reset\n\n"


#   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   this does not need to shine so much
#   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

if [ "$colorize" = "nocolor" ]; then

  echo
  make compile
  verify
  make $projectname
  #./$BIN_DIR/$projectname
  # when symbolic link is present
  ./$projectname
# exit
  exit

fi


#   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   compile, verify and link
#   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

######################################################################################
# compile                                  ###########################################
# compile                                  ###########################################

# if just 'remake' typed - compile files in $build_file. no compile if no files, so

if [ "$1" == "" ]; then
  echo just remake, cleaning $build_file
  echo "" > $build_file
fi

for file in `cat $build_file`; do
  if [ -f "$OBJ_DIR/$file.o" ]; then
    if [ "$1" != "" ]; then # if not just 'remake' used
      echo -ne "$boldmagenta""removing $OBJ_DIR/$file.o""$reset\n"
      #echo WHYwhy?
      rm $OBJ_DIR/$file.o
    fi
  fi
done

echo

echo -ne "$hlblueyellowb"" :: \n :: compiling...\n :: "
make compile        2>&1 | $gawkcmd -f $awkmakefile

#
# exit here if parameter buildfiles= is used

if [ "$IS_BUILDFILES" = "buildfiles" ]; then
  exit
# exit
fi



######################################################################################
# verify                                   ###########################################
# verify                                   ###########################################

verify


######################################################################################
# link and play                            ###########################################
# link and play                            ###########################################

echo
echo -ne "$hlgreenwhite"" :: \n :: linking...\n :: "
make $projectname   2>&1 | $gawkcmd -f $awkmakefile
echo -ne "$reset\n"

EXIT_CODE="0"

# if binary is present...
if [ -f bin/$projectname ]; then
  echo -ne "$hl_separator""\n$reset\n"

  # binary is placed in: ./bin/$projectname
  if [ -f ./$projectname ]; then
    today_is=`date`
    echo -ne "$reset\n""$boldblue""build successful: ""$blue""$today_is""\n"
    echo -ne "$green""link to binary is present...\n"
    echo -ne "$boldgreen""executing application...\n\n"
  echo -ne "$hl_separator""\n$reset"
  else
    ln -s ./bin/$projectname ./$projectname
  fi

  ./$projectname 2>&1 | $gawkcmd -f $awkprojectfile
  EXIT_CODE="${PIPESTATUS[0]}"
  #EXIT_CODE="$?"
  #echo "exit code: ${?} [AFTER]"

  # after execution
  if [ "$SLEEP_FLAG" = "yes" ]; then
    sleep_then $sleep_time_after_compilation
  fi

  if [ -d $TAR_DIR ]; then
    #echo -ne "$green""tar directory present\n"
    echo
  else
    echo -ne "$magenta""no tar directory, mkdir $TAR_DIR\n"
    mkdir $TAR_DIR
  fi

  if   [ "$EXIT_CODE" = "0" -o "$EXIT_CODE" = "44" ]; then
    make_tar # default
  elif [ "$EXIT_CODE" = "139" ]; then
    make_tar "segfault"
  fi

### ~~~~~~~~~~~~~~~~~~~~~~ ###
### when compilation fails ###
### ~~~~~~~~~~~~~~~~~~~~~~ ###
else
  echo -ne "$rederror""there was an error during building "
  echo -ne "$boldyellow"" $projectname  ""$rederror\n$reset\n"
  if [ "$SLEEP_FLAG" = "yes" ]
  then
    sleep_then $sleep_time_after_compilation
  else
    echo -ne "$white""\nhit enter...\n""$reset"
    read
  fi
fi


### ~~~~~~~~~~~~~~~~~~~~~~ ###
### program termination... ###
### ~~~~~~~~~~~~~~~~~~~~~~ ###
echo -ne "$hl_separator""\n$reset\n"
echo program terminated with exit code: $EXIT_CODE

if [ "$1" == "all" -o "$1" == "-a" ]; then
#  rm $build_file
#  rm $build_file_tmp
  echo
fi

#
# known exit codes ...

if   [ "$EXIT_CODE" = "44" ]; then
  echo nice..
elif [ "$EXIT_CODE" = "134" ]; then
  echo -ne "$red""GTK says: ""$white""jobs is killed with abort signal""\n$reset"
elif [ "$EXIT_CODE" = "139" ]; then
  echo -ne "$red""GTK says: ""$white""segfault""\n$reset"
fi

# all done.

echo -ne "\n $boldgreen""done.""$reset\n"

# reset color for terminal

echo -ne "$reset\n"


