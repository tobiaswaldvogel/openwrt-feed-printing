CFLAGS += \
    -g \
    -std=gnu99 \
    -fPIC -fpic \
    -fvisibility=hidden \
    -fno-exceptions \
    -ffunction-sections \
    -fdata-sections \
    -Wall -Werror \
    -Wl,--gc-sections \
    -Wno-unused-variable \
    -Wno-unused-but-set-variable \
    -Wno-deprecated-declarations \
    -DPACKAGE=\"brhl3040cncupswrapper\" \
    -DVERSION=\"1.0\"

all: brhl3040cncupswrapper

.PHONY: all clean

brhl3040cncupswrapper: brhl3040cncupswrapper.c
	$(CC) $(CFLAGS) -lcupsimage -lcups $(RASTERTOPPM_OBJ) -o $@ $^

clean:
	-rm -f brhl3040cncupswrapper
	-rm -f *.o

