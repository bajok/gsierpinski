#! /bin/gawk -f
#
# script for colorizing make output when sth shit happens
# use in shell script like that:
# (shell prompt)$ make sth 2>$1 gawk -f $awk-program-file


BEGIN {
  ECHO="yes"
  
  # manipulate output (e.g. return with output when file built nice)
  O_SETPOS="\033[s"
  O_GETPOS="\033[u"
  CLEAN_LINES=4
  O_MOVE_CLEAN_UP="\033[<3>A"
  # to disable this just set above variables to ""

  red="\033[0;31m"
  green="\033[0;32m"
  yellow="\033[0;33m"
  blue="\033[0;34m"
  magenta="\033[0;35m"
  cyan="\033[0;36m"
  white="\033[0;37;0m"
  boldred="\033[1;31m"
  boldgreen="\033[1;32m"
  boldyellow="\033[1;33m"
  boldblue="\033[1;34m"
  boldmagenta="\033[1;35m"
  boldcyan="\033[1;36m"
  boldwhite="\033[1;37m"
  underlinered="\033[4;31m"
  underlinegreen="\033[4;32m"
  underlineyellow="\033[4;33m"
  underlineblue="\033[4;34m"
  underlinemagenta="\033[4;35m"
  underlinecyan="\033[4;36m"
  underlinewhite="\033[4;37m"

  rederror="\033[0;37;41m"
  hlgreenwhite="\033[0;37;42m"
  hlyellowblue="\033[0;34;43m"
  hlblueyellow="\033[1;33;44m"
  hlmagentayellow="\033[1;33;45m"
  hlmagentawhite="\033[1;37;45m"
  
  hl_filename="\033[1;34;40m"
  hl_compiler="\033[1;32;40m"
  hl_linenum="\033[1;37;45m"
  hl_function="\033[1;37;44m"
  hl_funcmark="\033[0;37;44m"
  hl_identifier="\033[0;33m"
  hl_idenmark="\033[2;33m"

  rederror="\033[0;37;41m"
  underline="\033[4m"
  blinkon="\033[4;92m""\033[1m"
  blinkoff="\033[24;32m"
  blinkmid="\033[8;34m"
  reset="\033[0;0;0m"
  reset=white
  beep="\007"
  clearscr="\033[2J"

  hl_blue="\033[1;34;40m"
  hl_green="\033[0;32;40m"
  hl_white="\033[2;37;40m"
  hl_magenta="\033[1;37;45m"
  #hl_magenta_dark="\033[1;30;45m"

  separator=""
  print ""
  #dirty_sanchez=" :: building sources...\n :: "
  dirty_sanchez=" :: "
  is_dirty_calls=0

  # to shell variable
  #SYSCMD="echo -ne \"\\033[s\""
  #system (SYSCMD)
  #print O_SETPOS 

}

#
# functions definitions

function ne() { ECHO="no" }


function is_dirty () {
  if ((match (dirty_sanchez, "clean")) > 0 ) {
    print      green " :: "  dirty_sanchez " "reset
    # so if clean, we do not need this, so recall position
    #print O_GETPOS
    
    #SYSCMD="echo -ne \"\\033[u\"" # update pos
    SYSCMD="echo -ne \"\\033["CLEAN_LINES"A\"" # move lines up

    system (SYSCMD)
    #print O_MOVE_CLEAN_UP
    
  }
  else if ((match (dirty_sanchez, "dirty")) > 0 ) {
    print "\n" hl_magenta " :: " dirty_sanchez
#    print O_SETPOS
  }
  else if ((match (dirty_sanchez, "very dirty")) > 0 ) {
    print "\n" rederror " :: " dirty_sanchez
#    print O_SETPOS
  }
#  else if ((match (dirty_sanchez, "building sources...")) > 0 ) {
#    print "\n" hlblueyellow " :: " dirty_sanchez
#  }
  dirty_sanchez="clean"

  #
  # hm.. lets say a feature, when file built with no warnings: return cursor to start of input.
  


  is_dirty_calls++
}



#
# main colorizing rules

# convention is: 
#   whole line colorizing uses  /regexp/ { } patterns -- suppress printng line by ECHO="no"
#   single word colorizing uses gsub ("text", replacedtext) as pattern

# colorize warning messages
{ substs=gsub ("warning:", magenta "&" reset); if (substs > 0) dirty_sanchez="dirty" }

# #######################
# colorize error messages
# #######################
/error:/ { # call grepfiles on error string

  GREPFILES=1
  system_command=""
  error_type="generic"

  # if -w<n> -- search up to nth word after 'error:'
  # 1th word
  if (1 == 1) { # looking for one word after 'error:'
    
    errline[0]=""      # [1]              [2] 
    # splits errline to: src/filename:120 'variable' undeclared
    split ($0, errline, "error:")
    grepwordl1[0]=""
    grepword[0]=""
    filename[0]=""
    errstring[0]=""
    split (errline[1], filename, ":")
    # look for words between "‘" and "’"
    split (errline[2], grepwordl1, "‘")
    split (grepwordl1[2], grepword, "’")
    split (errline[2], errstring, " ")    # just get the words to find most errorneous string :)

    # detect error type
    for (iter in errstring) {
      #print $iter "\n"
      if (errstring[iter] == "undeclared")  { error_type=errstring[iter] } 
      if (errstring[iter] == "expected")    { error_type=errstring[iter];
       if (errstring[iter+1] == "statement") { error_type="expectedstatement"; GREPFILES=0; } }
      if (errstring[iter] == "conflicting") { error_type=errstring[iter] }
      #if (errstring[iter] == ""
    }

    if (match (errline[2], "‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’") > 0) {
      error_type="struct;"
    }

    #print red "error_type = " yellow error_type "\n"
    
    # look in file - preprare grep command
    system_command="./grepfiles --onefile "filename[1]" "grepword[1]
  }

  # if ( grepword[1] == "else

  substs=gsub ("error:", rederror "&" reset ); 
  if (substs > 0) 
    dirty_sanchez="very dirty"

  ne()
  
  # ######################
  # awk make file asistant
  # you may choose an 'asistant' that will call grepfiles to find errored string in failed file

  # [colors]
  awatercolor="\033[1;34;44m"
  afishcolor="\033[0;32;44m"
  agrasscolor="\033[1;32;42m"
  asheepcolor="\033[1;37;42m"
  ammcolor="\033[1;35;44m"
  asuncolor="\033[1;33;43m"

  # [inventory:fauna] 
  # ACaterpillar=",/\,/\,/\,/\,/\,/\,o"
  # AFishLeft="<`)))><"
  # AFishRight="><((('>"
  # AFishSwimming="¸.·´¯`·.´¯`·.¸¸.·´¯`·.¸><(((º>"
  AFishSwimmingFish=afishcolor"><(((º>"
  AFishSwimmingSwimming=awatercolor"¸.·´¯`·.´¯`·.¸¸.·´¯`·.¸"
  # AHappyCat="<(^.^)>"
  ALochNessmonster=ammcolor"_mmmP"
  # AMonkey="@('_')@"
  # AMouse="<:3 )~~~~"
  # ARatLeft="<^__)~"
  # ARatRight="~(__^>"
  ASheep=asheepcolor"°l°(,,,,);"
  #ASpider="///\oo/\\\"
  # [inventory:flora]
  AGrassSomeGrass=agrasscolor"¸¸.¸¸_¸¸¸¸¸"
  AGrassSomeRocks=agrasscolor"¸¸.¸ ¸_¸"
  ASun=asuncolor"°"
  AWater=awatercolor"_._._"
  # i think this feature does not need to make variable for number of asisstants.. even if random :)
  asistant_fish=AFishSwimmingSwimming AFishSwimmingFish reset
  asistant_sheep=AGrassSomeGrass ASheep AGrassSomeRocks ASun reset
  asistant_mmm=AWater ALochNessmonster AWater reset

  # errortype checked hopefully...

  # rand () returns 0..1 no idea...
  #if (
  
  OPT_N=""
  OPT_N="\n"

  #print 
  if      (error_type == "undeclared")    { print $0 "    " OPT_N asistant_sheep }
  else if (error_type == "expected")      { print $0 "    " OPT_N asistant_fish }  # <><
  else if (error_type == "conflicting")   { print $0 "    " OPT_N asistant_mmm }
  else if (error_type == "struct;")       
    { print $0 "    " hl_blue " probably lack of ';' after struct" reset }
  else                                     print $0 #      NO_asistant :)

  # #####################
  # call                       system         command
  if ( GREPFILES ) { system (system_command) }

  # print green"system ("boldblue system_command green")"reset
}


/Error/ {
  print beep
  print beep
  print beep
}

/(\/bin\/rm)/ {
  ne(); print yellow $0 reset }

/(gcc)|(g[+][+])/ {
  ne()

#  if ((is_dirty_calls == 0))  { print "\n"  }
#  else { is_dirty() }

  is_dirty()

  gsub ("gcc",     hl_compiler "&");
  gsub ("g[+][+]", hl_compiler "&");

  gsub ("`pkg-config [[:print:]]+`", "\n    "green "&");

  # .c files
  gsub ("[[:graph:]]+[.]c", hl_filename"&"reset);
  # .o files
  gsub ("[[:graph:]]+[.]o", boldblue"&        "green);

  #gsub ("-c ", white "&" hl_filename);
  #gsub ("-o ", boldwhite "    &");

  # colorize warning messages
  #gsub ("warning:", magenta "&" reset)
  #dirty_sanchez="dirty"

  
  #gsub ("[[:print:]]+\\.c", blue "&" reset);
  print "" $0 reset

}


  #
  # but! the gcc/g++ colorizing may be done with the for loop
  # it simply goes for every field in record (i=0; i<NF; i++)
  # check if there is e.g. "-o" and the next field is always 
  # filename, so it may be colorized in any way


  # at the end of make output
/make: [[:print:]]+ Error [[:digit:]]+/ {
  #ne(); print ""; print beep rederror $0 reset
  ne(); print ""; print rederror $0 }

  # warnings
/undefined reference to/ {
  ne(); print magenta $0 reset }


/In function/ {
  gsub ("‘", hl_funcmark "&" hl_function); gsub ("’", hl_funcmark "&" reset) }



# colorizing variable/function names
/‘[[:print:]]+’/ {
  gsub ("‘", hl_idenmark "&" hl_identifier); gsub ("’", hl_idenmark "&" reset) }



#
# rest of the rules -- colorizing only a word

#
# colorizing file names .c, .cpp, .h, .hpp
#{ gsub ("[[:print:]]+\\.[ch][p]*(incl)*(def)*:", hl_filename "& " reset) }

#
# line numbers
{ gsub ("[[:digit:]]+:", hl_linenum "&" reset) }

#
# in file included from
{ gsub ("In file included from ", white "&" green) }


#
# when nothing strange happens, and if there were no /regexp/ {} rule matched,
# print line -- otherwise set echo flag to yes
#   (otherwise - the rule was matched, so the rule prints line) 

{ if (ECHO=="yes") print white $0
  else ECHO="yes" 
}




END {
  realreset="\033[0;0;0m";
  print realreset  ""

}


#Code Action/Color
#---------------------------

#normal	\e[0m
#bold	\e[1m
#faint	\e[2m
#bold/faint off	\e[22m
#italic	\e[3m (not supported in gnome terminal)
#underline	\e[4m
#underline off	\e[24m
#blink slow	\e[5m (not supported in gnome terminal)
#blink fast	\e[6m (not supported in gnome terminal)
#blink off	\e[25m (not supported in gnome terminal)
#inverse	\e[7m
#inverse off	\e[27m
#hidden	\e[8m
#hidden off	\e[28m
#double underline	\e[21m (not supported in gnome terminal)
#foreground	\e[3%dm (where %d is 0–7, or 9 for reset)
#background	\e[4%dm (where %d is 0–7, or 9 for reset)
#foreground hi	\e[9%dm (where %d is 0–7, or 9 for reset)
#background hi	\e[10%dm (where %d is 0–7, or 9 for reset)
#move up	\e[%dA (where %d is the number of cells)
#move down	\e[%dB (where %d is the number of cells)
#move forward	\e[%dC (where %d is the number of cells)
#move backward	\e[%dD (where %d is the number of cells)
#new line	\e[%dE (where %d is the number of lines)
#backup line	\e[%dF (where %d is the number of lines)
#goto column	\e[%dG (where %d is the column)
#goto	\e[%d;%dH (where %d and %d are row and column) Alternate: \e[%d;%df
#clear screen part	\e[%dJ (values for %d: 0—to end; 1—to beginning; 2—entire)
#clear line part	\e[%dK (values for %d: 0—to end; 1—to beginning; 2—entire)
#scroll up	\e[%dS (where %d is number of lines)
#scroll down	\e[%dT (where %d is number of lines)
#save position	\e[s
#restore position	\e[u


#- Position the Cursor:
#\033[<L>;<C>H
#Or
#\033[<L>;<C>f
#puts the cursor at line L and column C.
#- Move the cursor up N lines:
#\033[<N>A
#- Move the cursor down N lines:
#\033[<N>B
#- Move the cursor forward N columns:
#\033[<N>C
#- Move the cursor backward N columns:
#\033[<N>D
#- Clear the screen, move to (0,0):
#\033[2J
#- Erase to end of line:
#\033[K
#- Save cursor position:
#\033[s
#- Restore cursor position:
#\033[u


#Other interesting codes:
#\033[2J clear screen
#\033[0q clear all keyboard LEDs (won't work from Xterm)
#\033[1q set "Scroll Lock" LED
#\033[2q set "Num Lock" LED
#\033[3q set Caps Lock LED
#\033[15;40H move the cursor to line 15, column 40
#\007 bell (beep)

