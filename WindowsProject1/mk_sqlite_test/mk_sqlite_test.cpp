#include "pch.h"
#include "CppUnitTest.h"

#include "../mk_sqlite/mk_sqlite.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mksqlitetest
{
	TEST_CLASS(mksqlitetest)
	{
	public:
		
		TEST_METHOD(create_insert_select)
		{

			auto db = mk::sqlite::database{":memory:"};

			mk::sqlite::execute(db, R"(
CREATE TABLE person (
	id INTEGER PRIMARY KEY AUTOINCREMENT, 
	name TEXT, 
	forename TEXT
))");

			auto stmt = mk::sqlite::statement{db, 
				"INSERT INTO person (name, forename) VALUES(?, ?)"};
			for (int i = 0; i < 20; ++i) {
				execute(stmt.bind(
					"Name " + std::to_string(i)
					, "Vorname " + std::to_string(i))
				);
			}


			auto result = mk::sqlite::result{db, 
				"SELECT * FROM person WHERE name LIKE ?", "Name 1%"};

			Assert::AreEqual(3, result.column_count());
			Assert::AreEqual(std::string{"id"}, result.column_name(0));
			Assert::AreEqual(std::string{"name"}, result.column_name(1));
			Assert::AreEqual(std::string{"forename"}, result.column_name(2));

			for (int i = 0; i < 11; ++i) {
				Assert::AreEqual(true, result.has_data());
            Assert::AreEqual(i + (i < 1 ? 2 : 10), result[0].Int());
				Assert::AreEqual("Name " + std::to_string(i + (i < 1 ? 1 : 9)), result[1].string());
				Assert::AreEqual("Vorname " + std::to_string(i + (i < 1 ? 1 : 9)), result[2].string());
				result.fetch();
			}

			Assert::AreEqual(false, result.has_data());

		}

	};


}
