#/bin/sh

seed=`date +%N`
echo "seed is " $seed  "saving in map_"$seed".map";
./tremgen $seed > "map_"$seed".map";
./minimap $seed

