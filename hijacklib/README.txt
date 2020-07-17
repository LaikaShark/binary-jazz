gcc -o libjack.so -fPIC -shared -D_GNU_SOURCE libjack.c -ldl
LD_PRELOAD=`pwd`/libjack.so ls ~/Desktop
