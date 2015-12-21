# Typing_Speed

## Description

Currently, typing_speed.c compiles into a command line game that counts how many characters you can type in a minute or less! Works on linux.

## How to use

You can call the executable with no arguments to test your typing speed for 5 seconds by default. Otherwise, put a number between 1 and 60 (inclusive) as the sole argument:
```
$ ./typing_speed_char 10
```

Compile using gcc:
```
$ gcc typing_speed.c -lpthread -lm
```

OR use the provided Makefile:
```
$ make
```

At execution the program will listen for keystrokes for the time limit and then tell you how good of a typer you are!

Enjoy!