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

#! /bin/gawk -f
#
# script for colorizing make output when sth shit happens
# use in shell script like that:
# (shell prompt)$ make sth 2>$1 gawk -f $awk-program-file


BEGIN {
  ECHO="yes"

  red="\033[0;31m"
  green="\033[0;32m"
  yellow="\033[0;33m"
  blue="\033[0;34m"
  magenta="\033[0;35m"
  cyan="\033[0;36m"
  white="\033[0;37m"

  boldred="\033[1;31m"
  boldgreen="\033[1;32m"
  boldyellow="\033[1;33m"
  boldblue="\033[1;34m"
  boldmagenta="\033[1;35m"
  boldcyan="\033[1;36m"
  boldwhite="\033[1;37m"

  rederror="\033[0;37;41m"
  hlgreenwhite="\033[0;37;42m"
  hlyellowblue="\033[0;34;43m"
  hlblueyellow="\033[0;33;44m"

  rederror="\033[0;37;41m"
  underline="\033[4m"
  reset=white
  #reset="\033[0;0;0m"
  beep="\007"
  clearscr="\033[2J"

  print ""
}

#
# functions definitions

function ne() { ECHO="no" }


#
# main colorizing rules

# convention is:
#   whole line colorizing uses  /regexp/ { } patterns -- suppress printng line by ECHO="no"
#   single word colorizing uses gsub ("text", replacedtext) as pattern

/(gdk)|(GDK)|(OpenGL)/ {
  ne();
  gsub ("( = TRUE)|( = \"TRUE\")", boldblue "&")
  gsub ("( = FALSE)|( = \"FALSE\")", boldred "&")
  gsub (" = [[:digit:]]+", boldmagenta "&")
  gsub ("[.]i[.]   ", blue"&"reset)
  gsub ("OpenGL", boldyellow "&" boldwhite)
  print yellow $0 reset
}

# warnings
/undefined reference to/ {
  ne(); print magenta $0 reset }

# config file

# paths and uris - beautiful
{ gsub ("(([./])|(file:)|(http:))[/]*([[:alnum:]]*/*)*", boldblue"&"reset) }

# config file variable names
{ gsub ("[[:graph:]]+ = ", red"&"reset) }

# window resolution
{ gsub ("[[:digit:]]+x[[:digit:]]+", blue"&"reset) }


#define DEBUG_GL                        "GL"
#define DEBUG_GTK                       "GTK"
#(...)

# colorizing modules 
{ gsub ("GL ", boldyellow"&"reset) }
{ gsub ("GTK ", boldblue"&"reset) }
{ gsub ("cb_.+", blue"&"reset) }
{ gsub ("DATA ", magenta"&"reset) }
{ gsub ("EXTIO ", boldred"&"reset) }
{ gsub ("STAT ", green"&"reset) }
{ gsub ("MEM ", red"&"reset) }
{ gsub ("THREAD ", boldcyan"&"reset) }

{ gsub ("dbg   ", yellow"&"reset) }
{ gsub ("flow  ", green"&") 
 # if flow is matched -- colorize 3rd element to green
}
{ gsub ("[.]i[.]   ", blue"&"reset) }
{ gsub ("[[]wrn[]] ", magenta"&"boldmagenta) }
{ gsub ("[(]err[)] ", red"&"boldred) }
{ gsub ("successfully", green"&"reset) }

{ gsub ("[._]width", magenta"&"reset) }
{ gsub ("[._]height", magenta"&"reset) }



# colorizing message types
#{ gsub (" i ", blue"&"reset) }
#{ gsub (" f ", boldgreen"&"reset) }
#{ gsub (" d ", magenta"&"reset) }
#{ gsub ("\(e\)", boldred"&"reset) }


  # colorizing file names .c, .cpp, .h, .hpp
#{ gsub ("[[:print:]]+\\.[ch][p]*:", blue "&" reset) }
#{ gsub ("[[:digit:]]+: ", yellow "&" reset) }


#
# when nothing strange happens, and if there were no /regexp/ {} rule matched,
# print line -- otherwise set echo flag to yes
#   (otherwise - the rule was matched, so the rule prints line)
{ if (ECHO=="yes") print white $0
  else ECHO="yes" }


END {
  realreset="\033[0;0;0m";
  print realreset  ""
}


