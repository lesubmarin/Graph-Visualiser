all:
	g++ -I src_SDL/include \
	    -L src_SDL/lib \
	    -L /usr/lib/gcc/x86_64-w64-mingw32/11 \
	    -o main \
	    src/main.cpp \
	    -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer