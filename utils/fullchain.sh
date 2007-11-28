#/bin/sh
a=`./generate.sh  | grep -P "^map_[0-9]+"` || exit 1
echo "working on "$a
./compil.sh $a.map || exit 2
tmp=`mktemp -td tremgen.XXXXXX` || exit 3
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
