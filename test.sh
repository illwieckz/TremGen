#!/bin/sh

f=$1
cp $f* ~/.tremulous/base/maps/
cp levelshot.tga ~/.tremulous/base/levelshots/$f.tga
tremulous +sv_pure 0 +devmap $1

