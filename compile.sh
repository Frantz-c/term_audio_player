#gcc -O3 `sdl2-config --cflags` -lSDL2 -lSDL2_mixer -lcurses -Ilibterm sources/main.c libterm/*.c -o termplayer
gcc -fsanitize=address -g3 -O3 `sdl2-config --cflags` -lSDL2 -lSDL2_mixer -lcurses -Ilibterm sources/main.c libterm/*.c -o termplayer
