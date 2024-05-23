FLAGS := $(shell pkg-config allegro-5 allegro_font-5 allegro_image-5 --libs --cflags)
snake: *.cpp *.hpp
	g++ *.cpp -o snake $(FLAGS)
run: snake
	./snake
