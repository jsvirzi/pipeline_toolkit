PROJECTROOT=$(PIPELINE_TOOLKIT_ROOT)/http_request_parser
INCLUDES=-I$(PROJECTROOT)/include 

all : lib/libhttp_request_parser.so

lib/libhttp_request_parser.so : src/http_request_parser.c include/http_request_parser.h
	g++ -c -Wall -Werror -fpic $(INCLUDES) src/http_request_parser.c -o lib/http_request_parser.o
	g++ -shared -o lib/libhttp_request_parser.so lib/http_request_parser.o

install:
	mkdir lib

clean:
	rm -f lib/http_request_parser.o
	rm -f lib/libhttp_request_parser.so

