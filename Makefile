build:
	gcc ./src/main.c -o run -lSDL2 -lSDLmain

exec:
	gcc ./src/main.c -o run -lSDL2 -lSDL2main
	./run
