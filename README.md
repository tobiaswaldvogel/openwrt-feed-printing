git clone https://github.com/lede-project/source

cd source

echo "src-git printing https://github.com/MCTRACO/openwrt-feed-printing.git" >> feeds.conf.default

./scripts/feeds update -a

./scripts/feeds install -a

make menuconfig (set Network->Printing->cups as "M")

make -j1 V=sc

copy /source/bin/packages/printing/*.ipk to machine & opkg install
