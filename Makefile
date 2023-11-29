all: build run

CPP_STANDARD := -std=c++17 
SFML_LIBS := -LC:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE_PATH := -IC:/SFML/include
INCLUDE := -I./include $(SFML_INCLUDE_PATH)

build:
	@g++ -g -Wall $(INCLUDE) ./src/*.cpp -o ./bin/main $(SFML_LIBS) $(CPP_STANDARD)
run:
	@./bin/main.exe