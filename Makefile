CC=g++
SRCS=SDL_Study.cpp piano_key.cpp
CFLAGS=-g -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf -O2 #-mwindows

study.exe: SDL_Study.cpp
	$(CC) $(SRCS) $(CFLAGS) -o app