#include "sqlite3.h"
#include <string>

int main()
{
	sqlite3 *db = nullptr;
	sqlite3_open("test.db", &db);
	std::string sql = "create table test (tbl_name text, tbl_status int);";
	sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);

	return 0;
}
