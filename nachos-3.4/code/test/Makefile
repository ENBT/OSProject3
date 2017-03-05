# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as

GCCDIR = ../../../gnu-decstation-ultrix/decstation-ultrix/2.95.3/

LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)

# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)

PATH = $(GCCDIR):/lib:/usr/bin:/bin

CC = $(GCCDIR)gcc -B../../../gnu-decstation-ultrix/
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = gcc -E
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: halt shell matmult sort bingo uno boi sizeTest1 sizeTest2 sizeTest3 sizeTest4 sizeTest5

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.c > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

boi.o: boi.c
	$(CC) $(CFLAGS) -c boi.c
boi: boi.o start.o
	$(LD) $(LDFLAGS) start.o boi.o -o boi.coff
	../bin/coff2noff boi.coff boi
	
halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt	
	

bingo.o: bingo.c
	$(CC) $(CFLAGS) -c bingo.c
bingo: bingo.o start.o
	$(LD) $(LDFLAGS) start.o bingo.o -o bingo.coff
	../bin/coff2noff bingo.coff bingo

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult
	
uno.o: uno.c
	$(CC) $(CFLAGS) -c uno.c
uno: uno.o start.o
	$(LD) $(LDFLAGS) start.o uno.o -o uno.coff
	../bin/coff2noff uno.coff uno
	
sizeTest1.o: sizeTest1.c
	$(CC) $(CFLAGS) -c sizeTest1.c
sizeTest1: sizeTest1.o start.o
	$(LD) $(LDFLAGS) start.o sizeTest1.o -o sizeTest1.coff
	../bin/coff2noff sizeTest1.coff sizeTest1
	
sizeTest2.o: sizeTest2.c
	$(CC) $(CFLAGS) -c sizeTest2.c
sizeTest2: sizeTest2.o start.o
	$(LD) $(LDFLAGS) start.o sizeTest2.o -o sizeTest2.coff
	../bin/coff2noff sizeTest2.coff sizeTest2
	
sizeTest3.o: sizeTest3.c
	$(CC) $(CFLAGS) -c sizeTest3.c
sizeTest3: sizeTest3.o start.o
	$(LD) $(LDFLAGS) start.o sizeTest3.o -o sizeTest3.coff
	../bin/coff2noff sizeTest3.coff sizeTest3

sizeTest4.o: sizeTest4.c
	$(CC) $(CFLAGS) -c sizeTest4.c
sizeTest4: sizeTest4.o start.o
	$(LD) $(LDFLAGS) start.o sizeTest4.o -o sizeTest4.coff
	../bin/coff2noff sizeTest4.coff sizeTest4
	
sizeTest5.o: sizeTest5.c
	$(CC) $(CFLAGS) -c sizeTest5.c
sizeTest5: sizeTest5.o start.o
	$(LD) $(LDFLAGS) start.o sizeTest5.o -o sizeTest5.coff
	../bin/coff2noff sizeTest5.coff sizeTest5
