
CC=g++ #clang++
CFLAGS=--std=c++11 -Wall -Wextra -pedantic -g
LDFLAGS=-lpthread -L${GTEST_BASE}/lib -lgtest

INCLUDES=-I${GTEST_BASE}/include -I../

OBJS = testsuite.o \
			forward_list_test.o \
			../solution/forward_list.o \
#			sparse_array_test.o \
			../solution/sparse_array.o \

.DEFAULT: all
all: $(OBJS) testsuite.bin

run: clean testsuite.bin
	./testsuite.bin

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.bin: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f *.a
	-rm -f *.bin
	-rm -f ../solution/*.o
	-rm -f ../solution/*.a

