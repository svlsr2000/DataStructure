LIBRARY=-pthread

all:
	gcc sem_init.c -o sem_init $(LIBRARY)
	gcc sem_child.c -o execute_child $(LIBRARY)


clean:
	rm -rf sem_init execute_child

test:
	./sem_init &
	./execute_child
