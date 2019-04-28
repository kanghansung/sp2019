#Assignment Makefile by KANGHANSUNG
CC = gcc
STRIP = strip

variables1 = myshell

all: myshell_exe

myshell_exe : $(variables1).o
	$(CC) -o myshell_exe $(variables1).o
	$(STRIP) myshell_exe

$(variables1).o : $(variables1).c
	$(CC) -c $(variables1).c

clean:
	rm *.o myshell_exe
