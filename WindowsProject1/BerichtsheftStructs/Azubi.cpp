#include "Azubi.h"

int64_t AzubiTabelle::Insert(const Azubi & val)
{
	mk::sqlite::execute(m_db, R"(
 INSERT INTO azubi (vorname, nachname) VALUES (?, ?)
)", val.vorname, val.nachname);
	return m_db.last_autoincrement();
}

int64_t AzubiTabelle::Update(const Azubi & val)
{
	mk::sqlite::execute(m_db, R"(
 UPDATE azubi SET (vorname, nachname) = (?, ?) WHERE azubi_id = ?
)", val.vorname, val.nachname, val.id);
	return val.id;
}

AzubiTabelle::AzubiTabelle(mk::sqlite::database db) : m_db(db) { }

int64_t AzubiTabelle::Save(const Azubi & val)
{
	if (val.id == 0) {
		return Insert(val);
	}
	return Update(val);
}

Azubi AzubiTabelle::Load(int64_t id)
{
	auto res = mk::sqlite::result{ m_db, R"(
SELECT vorname, nachname FROM azubi WHERE azubi_id = ?
)", id };

	if (res.has_data()) {
		Azubi a;
		a.id = id;
		a.vorname = res[0];
		a.nachname = res[1];
		return a;
	}

	throw std::runtime_error{ "Datensatz wurde nicht gefunden" };
}

std::vector<Azubi> AzubiTabelle::List()
{
	auto res = mk::sqlite::result{ m_db, R"(
SELECT azubi_id FROM azubi ORDER BY nachname
)" };

	std::vector<Azubi> vec;
	for (; res.has_data(); res.fetch()) {
		vec.push_back(Load(res[0]));
	}

	return vec;
}

void AzubiTabelle::provision()
{
	mk::sqlite::execute(m_db, R"(
 CREATE TABLE azubi (
   azubi_id INTEGER PRIMARY KEY AUTOINCREMENT
    , vorname VARCHAR
    , nachname VARCHAR
    
 );
)");
}