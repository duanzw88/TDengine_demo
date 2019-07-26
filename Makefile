ROOT = ./
TARGET = test
LFLAGS = -Wl,-rpath,/usr/lib/ -ltaos -lpthread -lm -lrt
CFLAGS = -O3 -g -Wall -Wno-deprecated -fPIC -Wno-unused-result -Wconversion -Wno-char-subscripts -D_REENTRANT -Wno-format -D_REENTRANT -DLINUX -msse4.2 -Wno-unused-function -D_M_X64 -std=gnu99 -I/usr/local/include/taos/

all: $(TARGET)
test:
	gcc $(CFLAGS) ./test.c -o $(ROOT)/test $(LFLAGS)
clean:
	rm $(ROOT)test
