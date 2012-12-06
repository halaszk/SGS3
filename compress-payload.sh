#!/bin/sh
cd PAYLOAD
if [ -e SuperSU.apk.xz ]; then
        rm SuperSU.apk.xz
        rm su.xz
	ntfs-3g.xz
fi;
if [ -e payload.tar ]; then
        rm -f payload.tar
fi;
chmod 644 SuperSU.apk
chmod 644 STweaks.apk
chmod 755 su
chmod 755 ntfs-3g
xz -zekv9 SuperSU.apk
xz -zekv9 STweaks.apk
xz -zekv9 su

mv SuperSU.apk.xz res/misc/payload/
mv STweaks.apk.xz res/misc/payload/
mv su.xz res/misc/payload/
mv ntfs-3g.xz res/misc/payload/

rm -f ../payload.tar
tar -cv res > payload.tar
stat payload.tar
mv payload.tar ../
cd ..

