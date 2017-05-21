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

//convert fucky string to normal string
inline string conv(string_t toconv)
{
	return utility::conversions::to_utf8string(toconv);
}

void handle_auth(http_request request) {
	web::uri path = request.relative_uri();

	//debugging nonsense
	//remove eventually
	cout << "Got auth uri" << endl;
	cout << utility::conversions::to_utf8string(path.path()) << endl;

	bool login_ok = false;

	//get headers from request and check for presense of req'd headers
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

void handle_user_creation(http_request request) {
	web::uri path = request.relative_uri();

	string_t return_session_id = L"to be set later idk";

	bool error = false;
	string_t error_details;
	status_code code = status_codes::OK;

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
		return_session_id = L"to be set later idk";
	}
	else {
		error = true;
		error_details = U("some required fields missing");
		code = status_codes::BadRequest;
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
}