#include "Abteilung.h"

int64_t AbteilungTabelle::Insert(const Abteilung & val)
{
	mk::sqlite::execute(m_db, R"(
 INSERT INTO abteilung (name) VALUES (?)
)", val.name);
	return m_db.last_autoincrement();
}

int64_t AbteilungTabelle::Update(const Abteilung & val)
{
	mk::sqlite::execute(m_db, R"(
 UPDATE abteilung SET (name) = (?) WHERE abteilung_id = ?
)", val.name, val.id);
	return val.id;
}

AbteilungTabelle::AbteilungTabelle(mk::sqlite::database db) : m_db(db) { }

 int64_t AbteilungTabelle::Save(const Abteilung & val)
{
	if (val.id == 0) {
		return Insert(val);
	}
	return Update(val);
}

 Abteilung AbteilungTabelle::Load(int64_t id)
 {
	 auto res = mk::sqlite::result{ m_db, R"(
SELECT name FROM abteilung WHERE abteilung_id = ?
)", id };

	 if (res.has_data()) {
		 Abteilung a;
		 a.id = id;
		 a.name = res[0];
		 return a;
	 }

	 throw std::runtime_error{ "Datensatz wurde nicht gefunden" };
 }

std::vector<Abteilung> AbteilungTabelle::List()
{
	auto res = mk::sqlite::result{ m_db, R"(
SELECT abteilung_id FROM abteilung ORDER BY name
)" };

	std::vector<Abteilung> vec;
	for (; res.has_data(); res.fetch()) {
		vec.push_back(Load(res[0]));
	}

	return vec;
}

 void AbteilungTabelle::provision()
{
	mk::sqlite::execute(m_db, R"(
 CREATE TABLE abteilung (
   abteilung_id INTEGER PRIMARY KEY AUTOINCREMENT
    , name VARCHAR
 );
)");
}
