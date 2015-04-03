#ifndef HTTP_REQUEST_PARSER_H
#define HTTP_REQUEST_PARSER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <vector>

class HttpRequestParser {
	public:
	HttpRequestParser(const char *str, int msg_len);
	HttpRequestParser(std::string &str);
	~HttpRequestParser();
	int get_content_length();
	int get_content_length(const char *msg, int msg_len);
	unsigned char *get_content(unsigned char *p = 0, int max_len = 0);
	private:
	void setup(const char *str, int msg_len);
	char *buff;
	unsigned char *content;
	int content_length, buff_length;
	std::vector<std::string> lines;
};

#endif
