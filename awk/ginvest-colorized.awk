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

BEGIN {
  # ease of use actually. the higher value the less colors in use.
  # 0: disabled
  # 1: all basic colors (but red=yellow, cyan=white), all bold = white, .
  # 2: a
  # 10: bold   : white
  # 20: normal : boldwhite
  # 30: normal : boldwhite, bold : blue
  # 33: mostly white, hl: nulls, flow, pointers, labels
  # 87: allwhite
  EASE_OF_COLORIZE_LEVEL=0 # 

  # init value: do not modify
  ECHO="yes"

  fg_color="\033[0;30;0;0m"
  bg_color="\033[0;38;0;0m"

  darkgray="\033[0;30m"
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
  hlgraywhite="\033[0;37;40m"
  hlwhitemagenta="\033[1;37;45m"
  hlwhitemagentadim="\033[0;37;45m"
  hlredred="\033[1;31;41m"
  hlwhitered="\033[1;37;41m"

  hl_app_close="\007""\033[4;32m"
  hl_function="\033[1m""\033[4;37m"

  hlgrayyellow="\033[1;33;40m"

  boldgreen_good="\033[1;32;40m"
  boldmagenta_warn="\033[1;37;45m"
  boldred_bad="\033[1;37;41m"


  flow_mark="[+]  "
  flow_mark_color="\033[2;32;40m"
  counter_color="\033[1;33;45m"

  rederror="\033[0;37;41m"
  underline="\033[4m"
  #reset=fg_color
  reset="\033[0m"
  beep="\007"
  clearscr="\033[2J"

  flt2="[-]?[0-9]+[.][0-9][0-9]"
  flt3="[-]?[0-9]+[.][0-9][0-9][0-9]"
  pointer="(0x)[[:xdigit:]]+"
  PTRcounter=0
  PTRnamearr[0]=""
  PTRvaluearr[0]=""
  variable="([[:graph:]]+ )([[][[:graph:]]+[]] )*(=)"

  print ""

  if (EASE_OF_COLORIZE_LEVEL==0) { # disabled
    red=red
  }

  if (EASE_OF_COLORIZE_LEVEL==1) {
    red=yellow
    cyan=white
    hlyellowblue=white
    hlblueyellow=white
    hlgraywhite=white
    hlredred=white
    hlwhitered=white
  }
  if (EASE_OF_COLORIZE_LEVEL==2) {
    magenta=yellow
    cyan=white
    boldmagenta=boldwhite
    boldcyan=boldwhite
    hlyellowblue=boldwhite
    hlblueyellow=boldwhite
  }

  if (EASE_OF_COLORIZE_LEVEL==10) { # all bold white
    boldred=boldwhite
    boldgreen=boldwhite
    boldyellow=boldwhite
    boldblue=boldwhite
    boldmagenta=boldwhite
    boldcyan=boldwhite
    boldwhite=white
    #rederror=white
  }

  if (EASE_OF_COLORIZE_LEVEL==20) { # all normal boldwhite
    red=boldwhite
    green=boldwhite
    yellow=boldwhite
    blue=boldwhite
    magenta=boldwhite
    cyan=boldwhite
    white=white
    #rederror=white
 }

  if (EASE_OF_COLORIZE_LEVEL==30) { # all normal boldwhite, bold yellow
    boldwhite=yellow=blue
    red=boldwhite
    green=boldwhite
    yellow=boldwhite
    blue=boldwhite
    magenta=boldwhite
    cyan=boldwhite
    white=white
    boldred=boldyellow
    boldgreen=boldyellow
    boldblue=boldyellow
    boldmagenta=boldyellow
    boldcyan=boldyellow
    #rederror=white
 }


  if (EASE_OF_COLORIZE_LEVEL==33) {
    yellow=blue
    blue=boldwhite
    boldmagenta=blue
#    magenta=yellow
    cyan=white
#    hlgreenwhite=boldwhite
#    hlyellowblue=boldwhite
#    hlblueyellow=boldwhite
#    hlgraywhite=boldwhite
#    hlwhitemagenta=boldwhite
#    hlwhitemagentadim=boldwhite
#    hlredred=white
#    hlwhitered=boldwhite
#    hl_app_close=white
#    hl_function=white
    #hlgrayyellow=white
#    boldgreen_good=white
#    boldmagenta_warn=white
#    boldred_bad=white

  }

  if (EASE_OF_COLORIZE_LEVEL==87) { # allwhite
    red=white
    green=white
    yellow=white
    blue=white
    magenta=white
    cyan=white
    white=white
    boldred=white
    boldgreen=white
    boldyellow=white
    boldblue=white
    boldmagenta=white
    boldcyan=white
    boldwhite=white
    rederror=white
    hlgreenwhite=white
    hlyellowblue=white
    hlblueyellow=white
    hlgraywhite=white
    hlwhitemagenta=white
    hlwhitemagentadim=white
    hlredred=white
    hlwhitered=white
    hl_app_close=white
    hl_function=white
    boldgreen_good=white
    boldmagenta_warn=white
    boldred_bad=white
  }
}

#
# functions definitions

function ne() { ECHO="no" }


#
# main colorizing rules

# convention is:
#   whole line colorizing uses  /regexp/ { } patterns -- suppress printng line by ECHO="no"
#   single word colorizing uses gsub ("text", replacedtext) as pattern

##############################################################################
/(gdk)|(GDK)|(OpenGL)/ {
  ne();
  gsub ("( = TRUE)|( = \"TRUE\")", boldblue "&")
  gsub ("( = FALSE)|( = \"FALSE\")", boldred "&")
  gsub (" = [[:digit:]]+", boldmagenta "&")
  gsub (" [.]i[.] ", boldblue"&"reset)
  gsub ("OpenGL", boldyellow "&" boldwhite)
  print yellow $0 reset
}


###############################################################################
# warnings
/undefined reference to/ {
  ne(); print magenta $0 reset }

# ############################################################################
# paths and uris - breaks many rules. if "wtf!? wtf?!" this is it. 
# ############################################################################

# paths:
#{ gsub ("( ([./])|(file:)|(http:))[/]*([[:alnum:]]*/*)*", boldblue"&"reset) }

# #########
# versions:
# # #
# 1
# { gsub ("( ([./])|(file:)|(http:))[/]*([[:alnum:]]*/*)*", boldblue"&"reset) }

# ############################################################################


##############################################################################
# functions
{ gsub ("([[:graph:]]+ )([(][[:alnum:]]*[)])", hl_function"& "reset) }

#{ if (EASE_OF_COLORIZE_LEVEL == 3) {
#  { gsub (" = [[:digit:]]+", boldwhite"& "reset) }
#}
#}


##############################################################################
# window resolution
#{ gsub ("[[:digit:]]+x[[:digit:]]+", blue"&"reset) }

# points, e.g. ( 0.1, 0.2, -0.4 )
#{ gsub ("[(] "flt2", "flt2", "flt2" [)]", boldgreen"&"reset) }
#{ gsub ("[(] "flt2", "flt2", "flt2" [)]", boldgreen"&"reset) }

# points 
#{ gsub ("("flt2")+ [,]* *", green"&"reset) }


##############################################################################
# parentheses
#{ gsub ("[(] ", boldyellow"&"reset) }
#{ gsub (" [)]", boldyellow"&"reset) }
# colons
{ gsub (", ", blue"&"reset) }

##############################################################################
# indexes
#{ gsub ("[[]([[:alnum:]]+)~(wrn)[]]", boldblue"&"blue) }
#{ gsub ("[[]([[:alnum:]]+)[]]", boldblue"&"blue) }

# labels
/ label = / {
#  gsub ("label = ", blue"&")
  gsub ("[[]([[:alnum:]]+)[]]", boldblue"&"boldwhite)
}
#

{ gsub ("configure_main_gldisplay", hlredred"&"reset) }

# floats
{ gsub (flt2, green"&") }
{ gsub (flt3, green"&"reset) }
# pointers (num of digits sensitive...)
# 

# ##############################
# ##############################
# ##############################
# ##############################
# ##############################
# get pointer then check if matches table of pointers, then print its type, e.g. (glgraph *)
# first look for init in record, if not look table, then print type name
#/$pointer/ 

# add to array 
/ptr_init:[(][[:print:]]+ \*[)]/ {

#  print rederror"ptr match entered"
  FS=" "
  RS="\n"

  # SPLIT all line, then split, split, split...
  
  # array init, elem counting starts at 1
  dbgline[0]=""
  split ($0, dbgline, "=")
  
  # dbgline[2] is:
  # "0x00ff00ff ptr_init:(gpointer *)"

  pointermatch[0]=""
  split (dbgline[2], pointermatch, " ")

  # is: gpointer
  pointername[0]=""
  split (pointermatch[2], pointername, "ptr_init:[(]")

  #pointermatch[1] is pointer value
  #pointermatch[2] is pointer name with ptr_init

  # colorize indexes if present
  if ( (match (pointername[2], "[[][[:digit:]]+[]]")) > 0 ) {

    arrayname[0]=""
    arrayindex[0]=""
    split (pointername[2], arrayname, "[[]")
    split (arrayname[2], arrayindex, "[]]")

    PTRnamearr[PTRcounter]=red arrayname[1] hlredred " " hlwhitered "[" hlwhitered arrayindex[1] hlredred "]" reset

  }
  else {
    PTRnamearr[PTRcounter]=pointername[2]
  }

  PTRvaluearr[PTRcounter]=pointermatch[1]
  PTRcounter++

  gsub ("ptr_init", red"&"bg_color)
}

# match pointer:
/(0x)[[:xdigit:]]+/ {
  FS=" "
  for (i=1; i<NF+1; i++) {
    # match pointer then check if it is in value array
    if ( (match ($i, pointer)) > 0 ) {
      for (j=0; j<PTRcounter; j++) {
        # if it is in
        if ( (match ($i, PTRvaluearr[j])) > 0 ) {
          #gsub (pointer, red"|"boldyellow"&"red"|"magenta PTRnamearr[j] red"|"blue)
          
          # add info: type, index
          gsub (pointer, boldblue "&" boldyellow "|" magenta PTRnamearr[j] blue)

        }
      }
    }
  }
}

##############################################################################
# variable names (and values) - to make value of different color set color after & mark
#{ gsub ("([[:graph:]]+ )([[][[:graph:]]+[]] )*(=)", blue"&") }

# variable
{ gsub (variable, white"&") }

# null
{ gsub ("[(]nil[)]", reset rederror"&"reset) }

# a "i  " string
{ gsub ("i  ", blue"&") }

##############################################################################
# colorizing modules 
{ gsub ("CONF ",             red"&"reset) }
{ gsub ("GL ",               boldmagenta"&"reset) }
{ gsub ("GLCB",              blue"&"reset) }
{ gsub ("GTK ",              blue"&"reset) }
{ gsub ("GRPH ",             boldyellow"&"reset) }
{ gsub ("WDGT ",             blue"&"reset) }
{ gsub ("(DATA )|(FILE )",   magenta"&"reset) }
{ gsub ("RAT ",              magenta"&"reset) }
{ gsub ("EXTIO ",            boldred"&"reset) }
{ gsub ("STAT ",             green"&"reset) }
{ gsub ("MEM ",              green"&"reset) }
{ gsub ("THRD ",             cyan"&"reset) }
# gl scene
{ gsub ("SCENE",             hlwhitemagenta"&"reset) }

##############################################################################
# misc
{ gsub ("count: [[:digit:]]+", counter_color" [ ""&"" ] "reset) }
{ gsub ("(expose^[_])|(realize^[_])|(configure^[_])", boldmagenta"&"reset) }
{ gsub ("box [[]6[]]", boldblue"&"blue) }
# separator
{ gsub ("[|] ", boldblue"&"reset) }
{ gsub (flow_mark, flow_mark_color"&") }

##############################################################################
# log type
{ gsub (" dbg  ", blue"&"reset) }
{ gsub ("flow", flow_mark_color"&"reset) }
{ gsub (flow_mark, flow_mark_color"&") }
# if flow is matched -- colorize 3rd element to green
{ gsub (".i[.] ", blue"&") }
{ gsub ("[[]wrn[]] ", boldmagenta"&"boldmagenta) }
{ gsub ("[(]err[)] ", boldred"&"boldred) }

##############################################################################
# some fancy keywords
{ gsub ("(successfully)|(done)", green"&"reset) }
{ gsub ("closing application", hl_app_close"&"reset) }
#{ gsub ("(GLGRAPH_[[:graph:]]+)", boldmagenta"&"reset) }
{ gsub ("(failed)|(FAIL)", boldred_bad" !""&""! "reset) }
{ gsub ("(DISABLED)", hlgraywhite" .""&"". "reset) }
{ gsub ("(ENABLED)|(succeeded)|(PASS)", boldgreen_good" |""&""| "reset) }
{ gsub ("(label_index)|(max_labels)|(labels)|(labels_max)|(listings_max)", boldmagenta"&") }
{ gsub ("(NOTE: )|(notice)|([-][>]label)|([-][>]displayed_label)", boldmagenta"&") }
# ##########
# app stages     note: highlights nice, dunno why
# ##########
{ gsub ("appending frontend", hlwhitemagenta"&") } 
{ gsub ("entering gtk_main loop.", hlwhitemagenta"&") }
{ gsub ("exitting gtk_main loop.", hlwhitemagenta"&") }
{ gsub ("return", darkgray"&"reset) }
# ##########
{ gsub ("no. [[:digit:]]+", hlgreenwhite"        &        "reset) }
{ gsub ("CB_GLGRAPH", hlwhitemagentadim"&"reset) }
{ gsub ("t_stock_enum = 0", boldred"&"" NEWCONNECT"reset) }
{ gsub ("t_stock_enum = 1", boldred"&"" GPW"reset) }
# is w_gid used anywhere else instead of glgraph[i] ?
{ gsub ("w_gid = ", boldwhite"&"darkgray"glgraph "reset) }
{ gsub ("skipped", darkgray"&"reset) }
{ gsub (" ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ", flow_mark_color"&"reset) }


##############################################################################
# glib, gtk messages
{ gsub ("([[:alnum:]]+-[[:alnum:]]*-*CRITICAL)", red"&") }
{ gsub ("([[:alnum:]]+-[[:alnum:]]*-*WARNING)", magenta"&") }
# (<unknown>:4844):
{ gsub ("[(][<][[:alnum:]]+[>]:[[:digit:]]+[)]:", blue"&") }


#
# when nothing strange happens, and if there were no /regexp/ {} rule matched,
# print line -- otherwise set echo flag to yes
#   (otherwise - the rule was matched, so the rule prints line)
{ if (ECHO=="yes") print white $0
  else ECHO="yes" }


END {
  realreset="\033[0;0;0m";
  print realreset  " "
}


