TARGETS := pc pc2 test_list
OBJ=pc.o mylist.o
OBJ2=pc2.o mylist.o

all: $(TARGETS)

test_list: test_list.o mylist.o
	gcc -Wall -o $@ $^


pc: $(OBJ)
	gcc -Wall -o $@ $^ -pthread

pc2: $(OBJ2)
	gcc -Wall -o $@ $^ -pthread

pc.o: pc.c mylist.c mylist.h 

pc2.o: pc2.c mylist.c mylist.h 

%.o: %.c
	gcc -Wall -g -c $<
	
clean: 
	rm $(OBJ) $(TARGETS)


