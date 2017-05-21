#pragma once
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "SCUtility.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;
typedef std::wstring string_t;

#define TRACE(msg)            wcout << msg
class ServerComms {
	http_listener listener;
	
public:
	ServerComms(const http::uri& url);
	void start_server();
	void stop_server();
	string conv(string_t toconv);

private:
	void handle_get(http_request request);
	void handle_put(http_request request);
	void handle_post(http_request request);
	void handle_delete(http_request request);
	

};

//constructor
ServerComms::ServerComms(const http::uri& url) : listener(http_listener(url))

{
	listener.support(methods::GET,
		std::tr1::bind(&ServerComms::handle_get,
			this,
			std::tr1::placeholders::_1));
	listener.support(methods::PUT,
		std::tr1::bind(&ServerComms::handle_put,
			this,
			std::tr1::placeholders::_1));
	listener.support(methods::POST,
		std::tr1::bind(&ServerComms::handle_post,
			this,
			std::tr1::placeholders::_1));
	listener.support(methods::DEL,
		std::tr1::bind(&ServerComms::handle_delete,
			this,
			std::tr1::placeholders::_1));
	
}

//called when rest service receives a request with method GET
void ServerComms::handle_get(http_request request)
{
	TRACE(L"\nhandle GET\n");
	web::uri path = request.relative_uri();
	
	//fucking bs equality checks wtf microsoft
	if (path.path() == uri(L"/test/").path()) {
		cout << "Got /test uri" << endl;
		cout << utility::conversions::to_utf8string(path.path()) << endl;
	}
	

	request.reply(status_codes::OK, "value returned GET");
}

//called when rest service receives a request with method POST
void ServerComms::handle_post(http_request request)
{
	TRACE("\nhandle POST\n");
	web::uri path = request.relative_uri();
	
	bool login_ok = false;
	
	//auth section
	//check for appropriate path
	if (path.path() == uri(L"/v1/auth/").path()) {
		handle_auth(request);
	}

}

//called when rest service receives a request with method PUT
void ServerComms::handle_put(http_request request)
{
	web::uri path = request.relative_uri();
	if (path.path() == uri(L"/v1/create/user/").path()) {
		handle_user_creation(request);
	}

}

//called when rest service receives a request with method DEL/DELETE
void ServerComms::handle_delete(http_request request)
{
	TRACE("\nhandle DEL\n");
	request.reply(status_codes::OK, "value returned DEL");
}


void ServerComms::start_server(){
	
	try
	{
		listener
			.open()
			.then([]() {TRACE(L"\nServer comms : now listening\n"); })
			.wait();
	}
	catch (exception const & e)
	{
		wcout << e.what() << endl;

	}
}

void ServerComms::stop_server() {
	listener.close();

}

//convert fucky string to normal string
inline string ServerComms::conv(string_t toconv)
{
	return utility::conversions::to_utf8string(toconv);
}
