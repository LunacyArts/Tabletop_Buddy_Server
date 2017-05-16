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
		obj[L"session-id"] = json::value::string(L"idgaf");
		request.reply(status_codes::OK, obj);
		
	}
	else {
		json::value obj;
		obj[L"error"] = json::value::string(U("Invalid username or password"));
		request.reply(status_codes::Unauthorized, obj);
	}

}

//called when rest service receives a request with method PUT
void ServerComms::handle_put(http_request request)
{
	web::uri path = request.relative_uri();

	string_t return_session_id = L"to be set later idk";

	bool error = false;
	string_t error_details;
	status_code code = status_codes::OK;

	if (path.path() == uri(L"/v1/create/user/").path()) {
		cout << "Got user creation uri" << endl;
		cout << utility::conversions::to_utf8string(path.path()) << endl;

		http_headers headers = request.headers();
		
			//do shit
			//check session against roger's db
			string_t firstname = L"firstname";
			string_t lastname = L"lastname";
			string_t username = L"username";
			string_t email = L"email";
			string_t password = L"password";
			json::value req_json = request.extract_json().get();
			if (req_json.has_field(firstname) && req_json.has_field(lastname) && req_json.has_field(username) && req_json.has_field(email) && req_json.has_field(password)) {
				string_t got_first = req_json.at(firstname).as_string();
				string_t got_last = req_json.at(lastname).as_string();
				string_t got_user = req_json.at(username).as_string();
				string_t got_email = req_json.at(email).as_string();
				string_t got_pass = req_json.at(password).as_string();

				cout << conv(got_first) << " " << conv(got_last) << " " << conv(got_user) << " " << conv(got_email) << " " << conv(got_pass) << endl;
				//TODO get session id from roger
			}
			else {
				error = true;
				error_details = U("some required fields missing");
				code = status_codes::BadRequest;
			}
		

	}

	if (error) {
		//handle error state
		json::value obj;
		obj[L"error"] = json::value::string(error_details);
		request.reply(code, obj);
	}
	else {
		//success
		json::value obj;
		obj[L"session-id"] = json::value::string(return_session_id);
		request.reply(status_codes::Created, obj);
	}
	
	//request.reply(status_codes::OK, "value returned PUT");
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
