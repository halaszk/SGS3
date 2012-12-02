#!/bin/sh
cd PAYLOAD
if [ -e payload.tar ]; then
	rm -f payload.tar
fi;

mv SuperSU.apk.xz res/misc/payload/
mv STweaks.apk.xz res/misc/payload/
mv su.xz res/misc/payload/

rm -f ../payload.tar
tar -cv res > payload.tar 
stat payload.tar
mv payload.tar ../
cd ..

