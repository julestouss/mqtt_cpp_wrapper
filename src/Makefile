CC = g++ 
SOURCE_DIR = src
BUILD_DIR = bin
SOURCE = main.cpp
BUILD = main
CCFLAGS = -std=c++17 -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lpaho-mqttpp3 -lpaho-mqtt3as -lpaho-mqtt3cs


all:
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/$(SOURCE) -o $(BUILD_DIR)/$(BUILD) $(LDFLAGS)

clean : 
	rm -f $(BUILD)/*

