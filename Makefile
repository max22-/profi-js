DLL = mujs.dll

all: $(DLL)
CC = i686-w64-mingw32-gcc.exe
CFLAGS = -Imujs

OBJS = dllmain.o libmujs.o

$(DLL): $(OBJS)
	$(CC) -shared -static-libgcc -Wl,--add-stdcall-alias $(OBJS) -o $(DLL)

dllmain.o: dllmain.cpp dll.h builtin_script.xxd
	$(CC) $(CFLAGS) -c -o dllmain.o dllmain.cpp

libmujs.o: mujs/one.c
	$(CC) -O2 -c -o libmujs.o mujs/one.c

builtin_script.xxd: builtin_script.js
	xxd -i < builtin_script.js > builtin_script.xxd
	echo ", 0x00" >> builtin_script.xxd

.PHONY: clean

clean:
	rm -f $(DLL) $(OBJS) builtin_script.xxd
