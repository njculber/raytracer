CC = g++
FLAGS = -Wall -Wextra -g

OBJ_FILE = ray.o ray-main.o
EXE_FILE = ray

ray: ray-main.o geometry.o
	$(CC) $(FLAGS) -o $(EXE_FILE) ray-main.o geometry.o

ray-main.o: ray-main.cpp geometry.h vector.h perspective.h
	$(CC) $(FLAGS) -c ray-main.cpp

geometry.o: geometry.h

clean:
	rm -f ray *.png *.o *.tgz