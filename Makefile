CC=gcc
CFLAGS=-c -Wall -O2
LDFLAGS=-l wiringPi -l wiringPiDev -l curl -lm
SOURCES_MAIN=envirophat.c pi.c pi_temp.c sensor.c bmp180.c bmp280.c
HEADERS_MAIN=pi.h pi_temp.h sensor.h bmp180.h bmp280.h
OBJECTS_MAIN=$(SOURCES_MAIN:.c=.o)
EXECUTABLE_MAIN=envirophat

all: $(SOURCES_MAIN) $(EXECUTABLE_MAIN)

$(EXECUTABLE_MAIN): $(OBJECTS_MAIN) $(HEADERS_MAIN)
	$(CC) $(LDFLAGS) $(OBJECTS_MAIN) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm $(EXECUTABLE_MAIN)

