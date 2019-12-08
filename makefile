CFLAGS:= -Wall  -Iinclude -Isrc

INCLUDE:= include
SRC := src
BUILD := build
BIN := bin

$(BIN)/Semaphore: $(BUILD)/queue.o $(BUILD)/main.o 
	g++ $(BUILD)/queue.o $(BUILD)/main.o -o $(BIN)/Semaphore

$(BUILD)/main.o: $(SRC)/main.c $(INCLUDE)/monitor.h $(INCLUDE)/queue.h 
	g++ $(CFLAGS) -c $(SRC)/main.c -o $(BUILD)/main.o

$(BUILD)/queue.o: $(SRC)/queue.c $(INCLUDE)/queue.h 
	g++ $(CFLAGS) -c $(SRC)/queue.c -o $(BUILD)/queue.o

clean:
	rm -f $(BUILD)/*.o
	rm -f $(BIN)/Semaphore



