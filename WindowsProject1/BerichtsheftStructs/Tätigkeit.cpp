#include "Tätigkeit.h"

int64_t TaetigkeitTabelle::Insert(const Taetigkeit & val)
{
	mk::sqlite::execute(m_db, R"(
 INSERT INTO taetigkeit (beschreibung, art_fk) VALUES (?, ?)
)", val.beschreibung, val.art_fk);
	return m_db.last_autoincrement();
}

int64_t TaetigkeitTabelle::Update(const Taetigkeit & val)
{
	mk::sqlite::execute(m_db, R"(
 UPDATE taetigkeit SET (beschreibung, art_fk) = (?, ?) WHERE taetigkeit_id = ?
)", val.beschreibung, val.art_fk, val.id);
	return val.id;
}

TaetigkeitTabelle::TaetigkeitTabelle(mk::sqlite::database db) : m_db(db) { }

int64_t TaetigkeitTabelle::Save(const Taetigkeit & val)
{
	if (val.id == 0) {
		return Insert(val);
	}
	return Update(val);
}

Taetigkeit TaetigkeitTabelle::Load(int64_t id)
{
	auto res = mk::sqlite::result{ m_db, R"(
SELECT beschreibung, art_fk FROM taetigkeit WHERE taetigkeit_id = ?
)", id };

	if (res.has_data()) {
		Taetigkeit a;
		a.id = id;
		a.beschreibung = res[0];
		a.art_fk = res[1];
		return a;
	}

	throw std::runtime_error{ "Datensatz wurde nicht gefunden" };
}

std::vector<Taetigkeit> TaetigkeitTabelle::List()
{
	auto res = mk::sqlite::result{ m_db, R"(
SELECT taetigkeit_id FROM taetigkeit ORDER BY beschreibung
)" };

	std::vector<Taetigkeit> vec;
	for (; res.has_data(); res.fetch()) {
		vec.push_back(Load(res[0]));
	}

	return vec;
}

void TaetigkeitTabelle::provision()
{
	mk::sqlite::execute(m_db, R"(
 CREATE TABLE taetigkeit (
   taetigkeit_id INTEGER PRIMARY KEY AUTOINCREMENT
    , beschreibung VARCHAR
	, art_fk INTEGER
 );
)");
}
