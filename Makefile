
files-all := $(shell ls *.cpp)
files-c := $(shell ls *.c)
TARGET  = duihua
CC := g++
.PHONY:all clean


all:
	$(CC) $(CFLAGS) -o $(TARGET) $(files-all) $(files-c) -lthrift -liconv


clean:
	rm -f $(TARGET)
	rm -f *.o

