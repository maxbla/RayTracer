all: image

image: stb.cpp SimpleImage.cpp SimpleImage.h stb_image.h stb_image_write.h camera.h camera.cpp Ray.h Surface.h Sphere.h main.cpp
	g++ -Wall stb.cpp SimpleImage.cpp Camera.cpp main.cpp -o RayTracer.o
clean:
	rm RayTracer
