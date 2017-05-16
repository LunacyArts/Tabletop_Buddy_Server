#pragma once

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
using namespace std;
using namespace sql;


class DBConnect {
private:
/*	Create driver, connection, and SQL statement pointers.
	They are not variables but pointers to mini-methods	*/
	Driver *driver;
	Connection *con;
	Statement *stmt;
	ResultSet  *res;

public:
	DBConnect() {
		try {
			driver = get_driver_instance();
			con = driver->connect("tcp://localhost:3306", "tabletop_buddy_accessor", "Rockets96fLy");

			cout << "Connection successfulto DB!\n";
		}
		catch (SQLException &e)
		{
			cout << "Connection failed to DB! Exited with error " << &e << "\n";
		}
	}
	//Server close and clean up methods
	bool close_DB() {
		try {
			con->close();
			delete stmt;
			delete con;
			delete stmt;
			cout << "DB Connections have been cleaned up and closed.\n";
			return true;
		}
		catch (...) {
			cout << "Unable to close DB Connections!\n";
			return false;
		}
	}
	bool create_user(string fn, string ln, string un, string e, string pass) {
		//User creation for new user
		try {
			
			return true;
		}
		//User creation failed
		catch (SQLException &e) {
			cout << "User creation failed for: " << un << "\n" << "With Error: " << &e;
			return false;
		}
	}
};