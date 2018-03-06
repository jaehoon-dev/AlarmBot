#pragma once

#include "libcurl/include/curl.h"


class TelegramManager
{
public:
	TelegramManager();
	~TelegramManager();

	void init();
	std::string get_update();
	void send_message( const std::string text );

	static size_t httpRecvStringChar( __in char *data, __in size_t size, __in size_t nmemb, __out std::string *writerData );
	static size_t httpRecvDummy( __in void *data, __in size_t size, __in size_t nmemb, __out void *writerData );

private:
	CURL* curl;

};

