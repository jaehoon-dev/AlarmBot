#include "stdafx.h"
#include "TelegramManager.h"
#include "custom_string.h"

// AlarmBot Token
#define TELEGRAM_TOKEN "312214600:AAFmC2Wtn1K0X5L9vdM0EATVC4VcEwSP1Ak"

// Test Group
//#define TELEGRAM_CHAT_ID "-155648554"

// Nyou Program
//#define TELEGRAM_CHAT_ID "-180536299"


#if IS_TEST
	// AlarmBot Group
	#define TELEGRAM_CHAT_ID "81046765"
#else
	// Hanzo of Nyou
	#define TELEGRAM_CHAT_ID "-213128676"
#endif




#define TELEGRAM_URL "https://api.telegram.org/bot" + TELEGRAM_TOKEN
#define TELEGRAM_SEND "/sendMessage?"
//#define TELEGRAM_GET_UPDATE "/getUpdates?offset=335600488"
#define TELEGRAM_GET_UPDATE "/getUpdates"




TelegramManager::TelegramManager()
{
	curl_global_init( CURL_GLOBAL_ALL );
}

TelegramManager::~TelegramManager()
{
	curl_easy_cleanup( curl );
	curl_global_cleanup();
	curl = NULL;
}

void TelegramManager::init()
{
	curl = curl_easy_init();
}

std::string TelegramManager::get_update()
{
	std::string msg = (std::string)TELEGRAM_URL + TELEGRAM_GET_UPDATE;
	std::string return_string;

	CURLcode curl_res;

	curl_easy_reset( curl );
	curl_easy_setopt( curl, CURLOPT_URL, msg.c_str() );
	curl_easy_setopt( curl, CURLOPT_FORBID_REUSE, true );
	curl_easy_setopt( curl, CURLOPT_FRESH_CONNECT, true );
	curl_easy_setopt( curl, CURLOPT_WRITEDATA, &return_string );
	curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, httpRecvStringChar );
	curl_easy_setopt( curl, CURLOPT_SSL_VERIFYPEER, 0L );
	curl_easy_setopt( curl, CURLOPT_SSL_VERIFYHOST, 0L );
	curl_easy_setopt( curl, CURLOPT_TIMEOUT_MS, 0 );
	curl_res = curl_easy_perform( curl );
	
	if( CURLE_OK != curl_res )
		return "";

	return return_string;
}

void TelegramManager::send_message( const std::string text )
{
	std::string convert_txt = CUSTOM_STRING::urlencode( CUSTOM_STRING::AnsiToUTF8( text ) );
	std::string encoding_txt = CUSTOM_STRING::replace_all( convert_txt, "\n", "%20" );

	std::string msg = ( std::string )TELEGRAM_URL + TELEGRAM_SEND;
	msg = msg + "chat_id=" + TELEGRAM_CHAT_ID;
	msg = msg + "&text=";
	msg = msg + encoding_txt;
	
	curl_easy_reset( curl );
	curl_easy_setopt( curl, CURLOPT_URL, msg.c_str() );
	curl_easy_setopt( curl, CURLOPT_FORBID_REUSE, true );
	curl_easy_setopt( curl, CURLOPT_FRESH_CONNECT, true );
	curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, httpRecvDummy );
	curl_easy_setopt( curl, CURLOPT_SSL_VERIFYPEER, 0L );
	curl_easy_setopt( curl, CURLOPT_SSL_VERIFYHOST, 0L );
	curl_easy_setopt( curl, CURLOPT_TIMEOUT_MS, 0 );
	curl_easy_perform( curl );
}

size_t TelegramManager::httpRecvStringChar( __in char *data, __in size_t size, __in size_t nmemb, __out std::string *writerData )
{
	if( writerData == NULL )
		return 0;

	writerData->append( data, size*nmemb );

	return size*nmemb;
}

size_t TelegramManager::httpRecvDummy( __in void *data, __in size_t size, __in size_t nmemb, __out void *writerData )
{
	return size * nmemb;
}