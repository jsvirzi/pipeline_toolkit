#include "http_request_parser.h"

void HttpRequestParser::setup(const char *str, int msg_len) {
	content = 0;
	int i, j;
	buff_length = msg_len + 1;
	buff = new char [ buff_length ]; /* handle null termination */
	memcpy(buff, str, msg_len);
	buff[msg_len] = 0; /* null-terminate if not already so */
	get_content_length();
	if(content_length > 0) {
		content = new unsigned char [ content_length ];
		unsigned char cha = buff[0], chb = buff[1], chc = buff[2], chd;
		for(i=3;i<msg_len;++i) {
			chd = buff[i];
			if(cha == '\r' && chb == '\n' && chc == '\r' && chd == '\n') {
				for(j=0;j<content_length;++j) content[j] = buff[i+1+j];
				break;
			}
			cha = chb; chb = chc; chc = chd; /* comb filter */
		}
	}

#if 0
	for(i=0;i<msg_len;++i) {
		ch = str[i];
		buff[i] = (ch == 0xa || ch == 0xd) ? 0 : ch; /* replace '\n' and '\r' with 0 */
	} 
	for(i=0;i<msg_len;++i)
#endif

}

HttpRequestParser::HttpRequestParser(const char *str, int msg_len) {
	setup(str, msg_len);
}

HttpRequestParser::HttpRequestParser(std::string &str) {
	setup(str.c_str(), str.length());
}

HttpRequestParser::~HttpRequestParser() {
	if(buff) delete [] buff;
	if(content) delete [] content;
}

int HttpRequestParser::get_content_length() {
	return get_content_length(buff, buff_length);
}

int HttpRequestParser::get_content_length(const char *msg, int msg_len) {
	bool found = false;
	const char *field = "Content-Length:";
	int i, j, k, field_len = strlen(field);
	content_length = -1;
	for(i=0;i<(msg_len - field_len);++i) {
		if(found) break;
		if(strncmp(&msg[i], field, field_len)) continue;
		for(j=i+field_len;j<msg_len;++j) {
			if(msg[j] == 0xa || msg[j] == 0xd) {
				int line_length = j - i - field_len;
#define TMPBUFSIZE 256
				char tmp_str [ TMPBUFSIZE ]; /* more than ample */
				if(line_length > TMPBUFSIZE) return -1;
				for(k=0;k<line_length;++k) tmp_str[k] = msg[i+field_len+k];
				tmp_str[k] = 0; /* null terminate */
				content_length = atoi(tmp_str);
printf("content_length = %d\n", content_length);
				found = true;
				break;
			}
		}
	}
	return content_length;
}

unsigned char *HttpRequestParser::get_content(unsigned char *p, int max_len) {
	if(p && (content_length <= max_len)) memcpy(p, content, content_length);
	else if(p) return 0;
	return content;
}

