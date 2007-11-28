#/bin/sh
#a=`./generate.sh  | grep -P "^map_[0-9]+"` || exit 1
##Generate.sh
seed=`date +%N`
echo "seed is " $seed  "saving in map_"$seed".map";
./tremgen $seed > "map_"$seed".map" || exit 1
a="map_"$seed
##
echo "working on "$a
#./compil.sh $a.map || exit 2
##compil.sh
f=$a".map"
if [ ${f:0:1} == "/" ] 
then 
#f=$1;
echo "";
else
f=`pwd`/$f;
fi

echo "Compiling "$f
"/opt/gtkradiant/q3map2.x86" -v -game tremulous -fs_basepath "/usr/share/games/tremulous/" -fs_game base -custinfoparms -meta $f > "compile.txt" || exit 2
"/opt/gtkradiant/q3map2.x86" -v -game tremulous -fs_basepath "/usr/share/games/tremulous/" -fs_game base -vis -saveprt -fast $f >> "compile.txt" || exit 3
"/opt/gtkradiant/q3map2.x86" -v -game tremulous -fs_basepath "/usr/share/games/tremulous/" -fs_game base -light -fast  -super 2 -filter -custinfoparms $f  >> "compile.txt" || exit 4
##

tmp=`mktemp -td tremgen.XXXXXX` || exit 5
echo "tempdir is "$tmp
mkdir $tmp"/levelshots"
mkdir $tmp"/maps"
mkdir $tmp"/scripts"

cp $a.[mb]* $tmp"/maps"
cp levelshot_labs.tga $tmp"/levelshots/"$a".tga"

echo -e "{\n\tmap \"$a\"\n\tlongname \"TremGen "`echo $a |  sed -e "s/[^0-9\]//g"` "\"\n\ttype \"tremulous\"\n}" > $tmp"/scripts/"$a".arena"
path=`pwd`
cd $tmp
zip  -r $a.pk3  *
cd $path
cp $tmp/$a.pk3 .

echo "cleaning up"
rm -rf $tmp

echo "saved as"
echo $a.pk3
