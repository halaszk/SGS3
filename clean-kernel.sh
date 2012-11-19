cp .config .config.bkp;
make ARCH=arm  mrproper;
cp .config.bkp .config;
make clean;
