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
  # reset=white
  realreset="\033[0;0;0m"
  reset=realreset
  beep="\007"
  clearscr="\033[2J"

  # print ""


  split("#*include,#*ifdef,#*ifndef,#*endif,#*define ([A-Z0-9]+_*)*", syntax_preproc, ",")

  split("static,typedef,struct,void,int,char,float,double", syntax_c_type, ",")

  split("for,if,else,while,do,switch,case,default,continue,break,NULL", syntax_c_keyword, ",")

  split("GFile,gpointer,gint,guint[[:digit:]]*,gfloat,gdouble,gchar", syntax_glib_type, ",")

  split("GtkWidget", syntax_gtk_type, ",")

  split("TRUE,FALSE", syntax_boolean, ",")

#for gtk there should be a pattern instead of an array

  RS="\n" # default "\n"

}

#
# functions definitions

function ne() { ECHO="no" }

# matched array
matched = ""
# current string
string = ""

function match_string(keywords_array, color) {

  for (iter in keywords_array) {
  	string = keywords_array[iter]
  	# if found and not matched yet
    if ((match ($0, "\\y"string) > 0) && (match (matched, string) == 0)) {
      gsub (string, color "&" reset)
	  matched = matched "," string
	}
  }
}


#
# main colorizing rules


# line numbers 
{ gsub ("[[:digit:]]+:", boldmagenta"&"reset" ") }


#syntax highlight - all keywords 
{
  ne()

  # line comments
  gsub ("([/][/][~]*[[:alnum:]]*)+( [[:graph:]]*)*", blue "&" reset)

  # functions should be called with the priority of matching
  # that means - longest similar matches goes first
  match_string(syntax_preproc, red)
  # strings
  gsub ("\"[[:print:]]*\"", magenta "&" reset)
  match_string(syntax_gtk_type, boldblue)
  match_string(syntax_glib_type, boldblue)
  match_string(syntax_c_type, yellow)
  match_string(syntax_c_keyword, boldyellow)
  match_string(syntax_boolean, yellow)

  # filename string 
  gsub ("  filename: ",  boldgreen "&" boldblue "  ")
  # paths and uris -- if not required - leave it - it does a big mess
  #gsub ("(([./])|(file:)|(http:))[/]*([[:alnum:]]*/*)*", boldblue"&"reset)
  # strings
  #gsub ("\"[[:print:]]*\"", magenta "&" reset)

  print $0 
}


#
# when nothing strange happens, and if there were no /regexp/ {} rule matched,
# print line -- otherwise set echo flag to yes
#   (otherwise - the rule was matched, so the rule prints line)
{ if (ECHO=="yes") print $0 realreset
  else ECHO="yes" }

#if (ECHO=="no") ECHO="yes";


END {
#  realreset="\033[0;0;0m";
#  print realreset  ""
}


#Black       0;30     Dark Gray     1;30
#Blue        0;34     Light Blue    1;34
#Green       0;32     Light Green   1;32
#Cyan        0;36     Light Cyan    1;36
#Red         0;31     Light Red     1;31
#Purple      0;35     Light Purple  1;35
#Brown       0;33     Yellow        1;33
#Light Gray  0;37     White         1;37
#
#
#- Position the Cursor:
#  \033[<L>;<C>H
#     Or
#  \033[<L>;<C>f
#  puts the cursor at line L and column C.
#- Move the cursor up N lines:
#  \033[<N>A
#- Move the cursor down N lines:
#  \033[<N>B
#- Move the cursor forward N columns:
#  \033[<N>C
#- Move the cursor backward N columns:
#  \033[<N>D
#
#- Clear the screen, move to (0,0):
#  \033[2J
#- Erase to end of line:
#  \033[K
#
#- Save cursor position:
#  \033[s
#- Restore cursor position:
#  \033[u







