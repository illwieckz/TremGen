#!/bin/sh 

f=$1
if [ ${f:0:1} == "/" ] 
then 
f=$1;
else
f=`pwd`/$1;
fi

echo "Compiling "$f
"q3map2" -v -game tremulous -fs_basepath "/usr/share/games/tremulous/" -fs_game base -custinfoparms -meta $f > "compile.txt"
"q3map2" -v -game tremulous -fs_basepath "/usr/share/games/tremulous/" -fs_game base -vis -saveprt -fast $f >> "compile.txt"
"q3map2" -v -game tremulous -fs_basepath "/usr/share/games/tremulous/" -fs_game base -light -fast  -super 2 -filter -custinfoparms $f  >> "compile.txt"
