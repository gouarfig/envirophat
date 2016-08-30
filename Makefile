CC=gcc
CFLAGS=-c -Wall -O2
LDFLAGS=-l wiringPi -l wiringPiDev -lm
SOURCES_MAIN=get_temp.c pi.c pi_temp.c sensor.c bmp180.c
HEADERS_MAIN=pi.h pi_temp.h sensor.h bmp180.h
OBJECTS_MAIN=$(SOURCES_MAIN:.c=.o)
EXECUTABLE_MAIN=get_temp

all: $(SOURCES_MAIN) $(EXECUTABLE_MAIN)

$(EXECUTABLE_MAIN): $(OBJECTS_MAIN) $(HEADERS_MAIN)
	$(CC) $(LDFLAGS) $(OBJECTS_MAIN) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm $(EXECUTABLE_MAIN)

