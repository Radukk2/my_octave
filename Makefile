# Copyright 2023 Constantinescu Radu

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=my_octave

build: $(TARGETS)

my_octave: my_octave.c
	$(CC) $(CFLAGS) my_octave.c matlab_functions.c -o my_octave

pack:
	zip -FSr 323CA_ConstantinescuRadu_Ioan_Tema2.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
