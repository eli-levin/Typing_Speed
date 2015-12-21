all:
	rm -rf typing_speed
	gcc typing_speed_chars.c -o typing_speed -lpthread -lm

typing_speed: typing_speed_chars.c
	gcc typing_speed_chars.c -o typing_speed -lpthread -lm

clean:
	rm -rf typing_speed
	clear
