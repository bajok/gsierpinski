#! /bin/bash

cd /home/ed/projects/ginvest/

COMMAND="/home/ed/projects/ginvest/remake"
GEOMETRY=" --geometry=140x100+1100+140 "
PROFILE=" --profile=make "

EXECUTE=`echo -ne "gnome-terminal --command $COMMAND $GEOMETRY $PROFILE"`

echo $EXECUTE
$EXECUTE
