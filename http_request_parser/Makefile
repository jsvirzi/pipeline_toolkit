PROJECTROOT=${HOME}/projects/pipeline_toolkit/http_request_parser
INCLUDES=-I$(PROJECTROOT)/include 
SYSLIBS = -lg2c -lm -ldl

all : lib/libHttpRequestParser.so

lib/libHttpRequestParser.so : src/http_request_parser.c include/http_request_parser.h
	g++ -c -Wall -Werror -fpic $(INCLUDES) src/http_request_parser.c -o lib/http_request_parser.o
	g++ -shared -o lib/libHttpRequestParser.so lib/http_request_parser.o

clean:
	rm -f lib/http_request_parser.o
	rm -f lib/libHttpRequestParser.so

