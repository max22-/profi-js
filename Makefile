DLL = mujs.dll

all: $(DLL)
CC = i686-w64-mingw32-gcc.exe
CFLAGS = -Imujs

OBJS = dllmain.o libmujs.o

$(DLL): $(OBJS)
	$(CC) -shared -static-libgcc -Wl,--add-stdcall-alias $(OBJS) -o $(DLL)

dllmain.o: dllmain.cpp dll.h
	$(CC) $(CFLAGS) -c -o dllmain.o dllmain.cpp

libmujs.o: mujs/one.c
	$(CC) -O2 -c -o libmujs.o mujs/one.c

.PHONY: clean

clean:
	rm -f $(DLL) $(OBJS)
