#!/bin/bash

CC := arm-none-linux-gnueabi-gcc

obj-y += char_app.o


all: char_app plat_app


char_app: char_app.c
	$(CC) -o $@ $<


plat_app: plat_app.c
	$(CC) -o $@ $<


clean:
	
	ls  | egrep  -v '*.c|Makefile' | xargs rm
