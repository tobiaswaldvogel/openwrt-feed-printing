git clone https://github.com/lede-project/source

cd source

echo "src-git printing https://github.com/MCTRACO/openwrt-feed-printing.git" >> feeds.conf.default

./scripts/feeds update -a

./scripts/feeds install -a

make menuconfig (set Network->Printing->cups as "M")

also u need to compile gutenprint on your machine and move it to build_dir/hostpkg/gutenprint-5.3.3

make -j1 V=sc

copy /source/bin/packages/printing/*.ipk to machine & opkg install
