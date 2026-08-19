CC = g++
CFLAGS = -std=c++11 -Wall
TARGET = emp
OBJS=职工管理系统.o workerManager.o Boss.o Employee.o Manager.o
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
%.o:%.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(TARGET) *.o
.PHONY:clean