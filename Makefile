DLL = mujs.dll

all: $(DLL)
CC = i686-w64-mingw32-gcc.exe
CPP = i686-w64-mingw32-g++.exe
CPPFLAGS = -Imujs

OBJS = dllmain.o libmujs.o

$(DLL): $(OBJS)
	$(CC) -shared -static-libgcc -static-libstdc++  -Wl,--add-stdcall-alias $(OBJS) -o $(DLL) -msse3 -lws2_32 -lgdi32

dllmain.o: dllmain.cpp dll.h
	$(CPP) $(CPPFLAGS) -c -o dllmain.o dllmain.cpp

libmujs.o: mujs/one.c
	$(CC) -O2 -c -o libmujs.o mujs/one.c

.PHONY: clean

clean:
	rm -f $(DLL) $(OBJS)
