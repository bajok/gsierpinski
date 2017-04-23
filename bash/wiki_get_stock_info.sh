#! /bin/bash

#SCRIPTNAME=$0
SCRIPTNAME="wiki_get_stock_info.sh"
LINK_FILENAME="wiki_get_stock_info.linklabels"
HTML2TEXTRC_FILE="wiki_get_stock_info.html2textrc"
#TEMP_FILENAME="cache.""$RANDOM""$RANDOM""$RANDOM"
#TEMP_FILENAME_HTML="$TEMP_FILENAME"".html"

#TEMP_FILENAME=`ls cache*html -1 | sed -n 1p | cut -f3 -d. --complement`
#TEMP_FILENAME_HTML="$TEMP_FILENAME"".html"

TEMP_FILENAME="cache.1"
TEMP_FILENAME_HTML="$TEMP_FILENAME"".html"

# this script requires html2text installed
#HTML_2_TEXT_PATH="/usr/bin/html2text"
#if [ -f "$HTML_2_TEXT_PATH" ]; then
#  echo
#else
#  echo no html2text found
#fi

# colors
blue="\033[0;34m"
magenta="\033[0;35m"
reset="\033[0;0;0m"
#red="\033[0;31m"
#green="\033[0;32m"
#yellow="\033[0;33m"
#blue="\033[0;34m"
#magenta="\033[0;35m"
#cyan="\033[0;36m"
#white="\033[0;37m"
#boldmagenta="\033[1;35m"
#hl_blue="\033[1;34;40m"
#hl_green="\033[0;32;40m"
#hl_green2="\033[1;32;40m"
#hl_magenta="\033[1;37;45m"
#hl_magenta_dark="\033[1;30;45m"
#reset="\033[0;0;0m"

#
# script for getting basic info 
# of stock from wiki. 
# uses wiki_get_stock_info.linklabels
#

# ####################################### 
#
# figyelem !!! (attention)              #
#
# #######################################
#
# exact source of this file
# 
# and ALL other scripts used by ginvest
#
# should be stored in ginvest 
#  s o u r c e  files. 
#
# ####
# how:
# remake.sh all -> concatenate this file
# into sources
#
# ? 
#
#   ?! wiki_get_stock_info.linklabels !?
# #######################################

#                                       #

# #######################################
#
# for file in linklabels cut f2 wget grep
# 


#BG="yes|no"
DBG="yes"


#
# HILFE

if [ "$1" = "-h" -o "$1" = "" -o "$1" = "--help" ]; then
  echo 
  echo -ne "$blue""usage: ""$reset""$SCRIPTNAME <label name>\n"
  echo -ne "$blue""usage: ""$reset""$SCRIPTNAME --list-labels\n"
  echo -ne "$blue""usage: ""$reset""$SCRIPTNAME --list-labels-links\n"
  echo -ne "$blue""usage: ""$reset""$SCRIPTNAME --has-label <label name>\n"
  echo
  echo -ne "$magenta""examples:\n$reset"
  echo -ne "$SCRIPTNAME ZYWIEC"
  echo 
  echo
# exit hilfe
  exit
fi

# 

if [ "$DBG" == "yes" ]; then
  echo
  echo ------------------------------------------------------------------------------- DEBUG info
  echo "\$SCRIPTNAME    = $SCRIPTNAME"
  echo "\$LINK_FILENAME = $LINK_FILENAME (file containing links for labels)"
  echo "\$TEMP_FILENAME = $TEMP_FILENAME (temporary html file)"
  echo ------------------------------------------------------------------------------- DEBUG info
  echo
  echo

  #echo "removing old cache* cache*html"
  #rm -f cache*
  #rm -f cache*html

  echo

fi

# #####################################
#
# list options

if [ "$1" == "--list-labels" ]; then
  echo listing labels...
  cat $LINK_FILENAME | cut -f1 -d,
  echo
# exit
  exit
fi

if [ "$1" == "--list-labels-links" ]; then
  echo listing links and labels...
  cat $LINK_FILENAME
  echo
# exit
  exit
fi

if [ "$1" == "--has-label" ]; then
  echo looking for label...
  cat $LINK_FILENAME | grep "$2" | cut -f1 -d,
  echo
# exit
  exit
fi


#
# get link

URI=`cat $LINK_FILENAME | grep "$1" | cut -f2 -d,`


# #####################################
#
# wget

echo "[warning]"
echo "[warning]"
echo "[warning]"
echo "[disabled] - use cached file"

#
# save html file then convert with html2text

#echo "wget -cq $URI -O $TEMP_FILENAME_HTML"
#wget -cq "$URI" -O $TEMP_FILENAME_HTML


# #####################################
#
# convert html to plain text

echo "-------------------------------------------------------"
echo "creating html cache file"
echo "\$ html2text \$TEMP_FILENAME > $TEMP_FILENAME_HTML"
echo "-------------------------------------------------------"

#html2text -rcfile $HTML2TEXTRC_FILE $TEMP_FILENAME_HTML > $TEMP_FILENAME
html2text -rcfile $HTML2TEXTRC_FILE $TEMP_FILENAME_HTML > $TEMP_FILENAME

#dbg
echo "tempfilename len... (lines)"
cat $TEMP_FILENAME | wc -l
echo -ne "\n.\n\n"


# #####################################
#
# grep for data

echo "[grep]"
echo "[grep]"
echo "[grep]"

echo cat pipe grep...
cat $TEMP_FILENAME | grep 'Forma prawna'
cat $TEMP_FILENAME | grep 'Data za.o.enia'
cat $TEMP_FILENAME | grep 'Lokalizacja'
cat $TEMP_FILENAME | grep 'Siedziba'
cat $TEMP_FILENAME | grep 'Numer KRS'
cat $TEMP_FILENAME | grep 'Prezes'
cat $TEMP_FILENAME | grep 'Bran.a'
cat $TEMP_FILENAME | grep 'Kapita. zak.adowy'

# ##
# get links: 
# cat $TEMP_FILENAME_HTML | grep 'Strona internetowa'
# ##


#echo hexdump head -n20
#cat $TEMP_FILENAME | hexdump -Cv | head -n20

#dbg
echo
echo "removing tempfile..."
echo "[disabled]"
#rm $TEMP_FILENAME
#rm $TEMP_FILENAME_HTML
if [ -f "$TEMP_FILENAME" -o -f "$TEMP_FILENAME_HTML" ]; then
  echo "error: cannot remove temporary file: $TEMP_FILENAME or $TEMP_FILENAME_HTML !!!"
fi


#
# 
# EOF
