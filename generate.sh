#/bin/sh

seed=`date +%N`
echo "seed is " $seed  "saving in map_"$seed".map";
./tremgen $seed > "map_"$seed".map";
./minimap $seed
composite -gravity center -watermark 20 logo_labs.png levelshot.tga levelshot.tga
echo "map_"$seed;
