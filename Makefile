#all for opencv project

CC = c++
CFLAGS = -Wall -Wextra -ggdb
LDFLAGS = -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs

all: 
	$(CC) -I./include/ $(CFLAGS) -o build/main src/*.cpp $(LDFLAGS)