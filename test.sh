#!/bin/sh

f=$1
mkdir -p ~/.tremulous/base/maps
mkdir -p ~/.tremulous/base/levelshots
cp $f* ~/.tremulous/base/maps/
cp levelshot.tga ~/.tremulous/base/levelshots/$f.tga
tremulous +sv_pure 0 +devmap $1

