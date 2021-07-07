#include "sqlite3.h"
#include <cstdio>
#include <cstdlib>
#include <string>

sqlite3* db;
char* err_msg = 0;

int callBack(void*, int, char**, char**);

void sqlError(const char* errorInfo)
{
	fprintf(stderr, "%s\n", errorInfo);
	if (err_msg)
	{
		fprintf(stderr, "SQL error: %s\n", err_msg);
	}
	sqlite3_free(err_msg);
	sqlite3_close(db);
	exit(1);
}

void connectStudentsDB() // create student database
{
	int rc = sqlite3_open("mp1.db", &db); // connect to mp1.db
	if (rc != SQLITE_OK) 
	{
		fprintf(stderr, "Cannnot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	std::string strSql = "DROP TABLE IF EXISTS Students;"; // drop the former table

	rc = sqlite3_exec(db, strSql.c_str(), 0, 0, &err_msg); 
	if (rc != SQLITE_OK)
	{
		sqlError("Drop Table Error");
	}
	
	strSql = "CREATE TABLE Students(ID INT, Name TEXT, GPA DOUBLE, Age INT);"; // create student database of 4 columns
	rc = sqlite3_exec(db, strSql.c_str(), 0, 0, &err_msg);
	if (rc != SQLITE_OK)
	{
		sqlError("Create Table Error");
	}
}

void addStudent(const char* stuID, const char* stuName, const char* stuGPA, const char* stuAge) // add a student
{
	std::string strSql = "INSERT INTO Students VALUES(";
	strSql += stuID;
	strSql += ", '";
	strSql += stuName;
	strSql += "', ";
	strSql += stuGPA;
	strSql += ", ";
	strSql += stuAge;
	strSql += ");";

	int rc = sqlite3_exec(db, strSql.c_str(), 0, 0, &err_msg);
	if (rc != SQLITE_OK)
	{
		sqlError("Add Student Error");
	}
	else
	{
		printf("Success add student: %s\n\n", stuName);
	}
}

void deleteStudentByID(const char* stuID) // delete a student according to ID
{
	std::string strSql = "DELETE FROM Students WHERE ID=";
	strSql += stuID;
	strSql += ";";

	int rc = sqlite3_exec(db, strSql.c_str(), 0, 0, &err_msg);
	if (rc != SQLITE_OK)
	{
		sqlError("Failed to delete student");
	}
	else
	{
		printf("Success delete student: ID = %s\n\n", stuID);
	}
}

void deleteStudentByName(const char* stuName) // delete a student according to Name
{
	std::string strSql = "DELETE FROM Students WHERE Name='";
	strSql += stuName;
	strSql += "';";

	int rc = sqlite3_exec(db, strSql.c_str(), 0, 0, &err_msg);
	if (rc != SQLITE_OK)
	{
		sqlError("Failed to delete student");
	}
	else
	{
		printf("Success delete student: Name = %s\n\n", stuName);
	}
}

void findStudentByID(const char* stuID) // find the information of the student with given ID
{
	printf("The information of the student whose ID = %s:\n", stuID);

	std::string strSql = "SELECT Name, GPA, Age FROM Students WHERE ID=";
	strSql += stuID;
	strSql += ";";

	int rc = sqlite3_exec(db, strSql.c_str(), callBack, 0, &err_msg);
	printf("\n");
	if (rc != SQLITE_OK)
	{
		sqlError("Failed to find students");
	}
}

void closeDatabase() // close the database
{
	sqlite3_close(db);
}

void viewStudents()  // show all students in the database
{
	printf("All students in the database are as follow:\n");

	std::string strSql = "SELECT * FROM Students";

	int rc = sqlite3_exec(db, strSql.c_str(), callBack, 0, &err_msg);
	printf("\n");
	if (rc != SQLITE_OK)
	{
		sqlError("Failed to view students");
	}
}

int callBack(void* NotUsed, int argc, char** argv, char** azColName) // show the information of a student
{
	NotUsed = 0;

	for (int i = 0; i < argc; i++)
	{
		printf("%s = %s, ", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");

	return 0;
}

int main(void)
{
	connectStudentsDB(); // create student database

	addStudent("114", "Sunset", "4.0", "19");  // add a student to the database
	addStudent("514", "yanQval", "4.0", "20");
	addStudent("250", "krydom", "1.3", "19");
	viewStudents();

	deleteStudentByID("514");  // delete a student according to ID
	viewStudents();

	deleteStudentByName("Sunset"); // delete a student according to Name
	viewStudents();
	
	findStudentByID("250");  // find a student by ID

	findStudentByID("114");
	addStudent("114", "YMDragon", "4.0", "20");
	findStudentByID("114");

	closeDatabase(); // close the database

	return 0;
}