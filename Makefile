#!#/usr/bin/make -f

.PHONY = all clean

CC = g++
AR = ar
CFLAGS = -std=c++0x -Wall -pthread
LDFLAGS = -L. -l image

all: image

raytracer.o: Camera.h Camera.cpp Ray.h Surface.h Sphere.h main.cpp Light.h AreaLight.h AreaLight.cpp libimage.a
	$(CC) $(CFLAGS) -static main.cpp Camera.cpp AreaLight.cpp $(LDFLAGS) -o raytracer.o

libimage.a: SimpleImage.cpp SimpleImage.h stb.cpp stb_image.h stb_image_write.h
	$(CC) $(CFLAGS) -c SimpleImage.cpp stb.cpp
	$(AR) -rcs libimage.a stb.o SimpleImage.o

clean:
	rm libimage.a SimpleImage.o stb.o raytracer.o output.png
