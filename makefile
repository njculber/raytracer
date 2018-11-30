CC = g++
FLAGS = -Wall -Wextra -g

OBJ_FILE = ray.o ray-main.o
EXE_FILE = ray

ray: ray-main.o geometry.o perspective.o
	$(CC) $(FLAGS) -o $(EXE_FILE) ray-main.o geometry.o perspective.o

ray-main.o: ray-main.cpp geometry.h ray.h vector.h perspective.h
	$(CC) $(FLAGS) -c ray-main.cpp

geometry.o: geometry.h ray.h

perspective.o: perspective.h vector.h ray.h

clean:
	rm ray reference.png custom.png normals.png geometry.o perspective.o ray-main.o raytracer.tgz