CC = g++
CFLAGS = -g -Wall -std=c++11 `pkg-config --cflags opencv4`
LDFLAGS = `pkg-config --libs opencv4`
TARGET=demo
OBJS=test1.o
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
%.o:%.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(TARGET) *.o
.PHONY:clean