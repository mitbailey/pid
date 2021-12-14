CXX = g++
CPPOBJS = src/main.o src/pid.cc src/test.cc
EDCXXFLAGS = -I ./ -I ./include/ -Wall -pthread $(CXXFLAGS)
EDLDFLAGS := -lpthread -lm $(LDFLAGS)
TARGET = pid.out

all: $(CPPOBJS)
	$(CXX) $(EDCXXFLAGS) $(CPPOBJS) -o $(TARGET) $(EDLDFLAGS)
	./$(TARGET)

%.o: %.cc
	$(CXX) $(EDCXXFLAGS) -o $@ -c $<

%.o: %.c
	$(CC) $(EDCFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	$(RM) *.out
	$(RM) *.o
	$(RM) src/*.o

spotless: clean
	$(RM) $(COBJS)
	$(RM) $(CPPOBJS)

