CC=gcc
CFLAGS_GTK=$$(pkg-config --cflags gtk4)
CFLAGS=-Wall -Wextra -pedantic -std=c18 -O3 $(CFLAGS_GTK)
LIBS_GTK=$$(pkg-config --libs gtk4) -lm
LIBS=$(LIBS_GTK)
BUILD=build
TARGET=tictactoe

MODULES=\
main.o\
view.o\
ui.o\
game.o\
game_state.o

all: prepare $(MODULES)
	$(CC) $(FLAGS) $(MODULES) $(LIBS) -o $(BUILD)/$(TARGET)

game.o: src/game.c src/game.h src/game_state.h
	$(CC) $(GLAGS) -c src/game.c -o game.o	

game_state.o: src/game_state.c src/game_state.h
	$(CC) $(CFLAGS) -c src/game_state.c -o game_state.o

ui.o: src/ui.c src/ui.h
	$(CC) $(CFLAGS) -c src/ui.c -o ui.o


view.o: src/view.c src/view.h src/game.h src/game.c src/game_state.h src/game_state.c src/ui.h
	$(CC) $(CFLAGS) -c src/view.c -o view.o


main.o: app/main.c app/../src/view.h app/../src/game_state.h
	$(CC) $(CFLAGS) -c app/main.c -o main.o


prepare:
	mkdir -pv $(BUILD)

clean:
	rm -frv $(BUILD)
	rm -fv *.o

exec:
	$(BUILD)/$(TARGET)

:w


