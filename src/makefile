
IDIR = ../include
CC = gcc
CFLAGS = -Wall -I$(IDIR) -g

ODIR = obj

LIBS = -lm

_DEPS = LinkedList.h Queue.h PriorityQueue.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = my_scheduler.o Queue.o PriorityQueue.o LinkedList.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

myscheduler: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

myshell: my_shell.c
	$(CC) -Wall -g -o myshell my_shell.c

p1: p1.c
	$(CC) -Wall -o p1 p1.c	

p2: p2.c
	$(CC) -Wall -o p2 p2.c	

p3: p3.c
	$(CC) -Wall -o p3 p3.c	

p4: p4.c
	$(CC) -Wall -o p4 p4.c	

p5: p5.c
	$(CC) -Wall -o p5 p5.c	
	
compile: p1 p2 p3 p4 p5 myscheduler myshell

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ p1 p2 p3 p4 p5 myscheduler myshell