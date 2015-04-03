PROJECTROOT=$(PIPELINE_TOOLKIT_ROOT)/hash_table
INCLUDES=-I$(PROJECTROOT)/include 

all : lib/libhash_table.so

lib/libhash_table.so : src/hash_table.c include/hash_table.h
	g++ -c -Wall -Werror -fpic $(INCLUDES) src/hash_table.c -o lib/hash_table.o
	g++ -shared -o lib/libhash_table.so lib/hash_table.o

install:
	mkdir lib

clean:
	rm -f lib/hash_table.o
	rm -f lib/libhash_table.so

