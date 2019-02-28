CFLAGS = -g -Wall

default: program

program: rooms.o items.o event_list.o adventure.o
	gcc $(CFLAGS) -o program rooms.o items.o event_list.o adventure.o

rooms.o: rooms.c rooms.h event_list.h items.h
	gcc $(CFLAGS) -c rooms.c
items.o: items.c items.h 
	gcc $(CFLAGS) -c items.c
event_list.o: event_list.c event_list.h rooms.h
	gcc $(CFLAGS) -c event_list.c
adventure.o: adventure.c rooms.h items.h event_list.h
	gcc $(CFLAGS) -c adventure.c

clean:
	$(RM) program *.o *~
