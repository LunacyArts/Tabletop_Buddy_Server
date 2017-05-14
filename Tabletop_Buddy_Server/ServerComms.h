#pragma once
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

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
#define TRACE_ACTION(a, k, v) wcout << a << L" (" << k << L", " << v << L")\n"
class ServerComms {
	http_listener listener;
	
public:
	ServerComms(const http::uri& url);
	void start_server();
	void stop_server();
	

private:
	void handle_get(http_request request);
	void handle_put(http_request request);
	void handle_post(http_request request);
	void handle_delete(http_request request);


};

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


void ServerComms::handle_post(http_request request)
{
	TRACE("\nhandle POST\n");
	web::uri path = request.relative_uri();

	bool login_ok = false;
	

	if (path.path() == uri(L"/v1/auth/").path()) {
		cout << "Got auth uri" << endl;
		cout << utility::conversions::to_utf8string(path.path()) << endl;

		http_headers headers = request.headers();
		string_t requser = U("BuddyUser");
		string_t reqpass = U("BuddyPass");
		if (headers.has(requser) && headers.has(reqpass)) {
			cout << "Found username and password headers" << endl;
			
			string_t username = headers[requser];
			string_t password = headers[reqpass];

			cout << "Username: " << utility::conversions::to_utf8string(username) <<
				" Password: " << utility::conversions::to_utf8string(password) << endl;

			//someday, actually check
			login_ok = true;
		}
		else {
			cout << "Couldn't find username and password headers" << endl;
		}
}

	//utility::string_t suri = request.relative_uri().to_string();
	//string normalstring = utility::conversions::to_utf8string(suri);
	//cout << normalstring << endl;
	
	if (login_ok) {
		
		
		string session_id = "get-some-random-session-id-from-roger";
		json::value obj;
		obj[L"session-id"] = json::value::string(utility::conversions::to_string_t(session_id));
		request.reply(status_codes::OK, obj);
		
	}
	else {
		json::value obj;
		obj[L"error"] = json::value::string(U("Invalid username or password"));
		request.reply(status_codes::Unauthorized, obj);
	}

}

void ServerComms::handle_put(http_request request)
{
	TRACE("\nhandle PUT\n");
	request.reply(status_codes::OK, "value returned PUT");
}

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
