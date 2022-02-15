#include "Art.h"

int64_t ArtTabelle::Insert(const Art & val)
{
	mk::sqlite::execute(m_db, R"(
 INSERT INTO art (name) VALUES (?)
)", val.name);
	return m_db.last_autoincrement();
}

int64_t ArtTabelle::Update(const Art & val)
{
	mk::sqlite::execute(m_db, R"(
 UPDATE art SET (name) = (?) WHERE art_id = ?
)", val.name, val.id);
	return val.id;
}

ArtTabelle::ArtTabelle(mk::sqlite::database db) : m_db(db) { }

 int64_t ArtTabelle::Save(const Art & val)
{
	if (val.id == 0) {
		return Insert(val);
	}
	return Update(val);
}

 Art ArtTabelle::Load(int64_t id)
 {
	 auto res = mk::sqlite::result{ m_db, R"(
SELECT name FROM art WHERE art_id = ?
)", id };

	 if (res.has_data()) {
		 Art a;
		 a.id = id;
		 a.name = res[0];
		 return a;
	 }

	 throw std::runtime_error{ "Datensatz wurde nicht gefunden" };
 }

std::vector<Art> ArtTabelle::List()
{
	auto res = mk::sqlite::result{ m_db, R"(
SELECT art_id FROM art ORDER BY name
)" };

	std::vector<Art> vec;
	for (; res.has_data(); res.fetch()) {
		vec.push_back(Load(res[0]));
	}

	return vec;
}

 void ArtTabelle::provision()
{
	mk::sqlite::execute(m_db, R"(
 CREATE TABLE art (
   art_id INTEGER PRIMARY KEY AUTOINCREMENT
    , name VARCHAR
 );
)");
}
