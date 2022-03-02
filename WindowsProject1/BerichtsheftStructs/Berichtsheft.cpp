#include "Berichtsheft.h"


int64_t BerichtsheftTabelle::Insert(const Berichtsheft & val)
{
	mk::sqlite::execute(m_db, R"(
 INSERT INTO Berichtsheft (minuten, woche_fk, taetigkeit_fk, abteilung_fk, azubi_fk) VALUES (?, ?, ?, ?, ?)
)", val.minuten, val.woche_fk, val.taetigkeit_fk, val.abteilung_fk, val.azubi_fk);
	return m_db.last_autoincrement();
}

int64_t BerichtsheftTabelle::Update(const Berichtsheft & val)
{
	mk::sqlite::execute(m_db, R"(
 UPDATE Berichtsheft SET (minuten, woche_fk, taetigkeit_fk, abteilung_fk, azubi_fk) = (?, ?, ?, ?, ?) WHERE Berichtsheft_id = ?
)", val.minuten, val.woche_fk, val.taetigkeit_fk, val.abteilung_fk, val.azubi_fk, val.id);
	return val.id;
}

BerichtsheftTabelle::BerichtsheftTabelle(mk::sqlite::database db) : m_db(db) { }

int64_t BerichtsheftTabelle::Save(const Berichtsheft & val)
{
	if (val.id == 0) {
		return Insert(val);
	}
	return Update(val);
}

Berichtsheft BerichtsheftTabelle::Load(int64_t id)
{
	auto res = mk::sqlite::result{ m_db, R"(
SELECT minuten, woche_fk, taetigkeit_fk, abteilung_fk, azubi_fk FROM Berichtsheft WHERE Berichtsheft_id = ?
)", id };

	if (res.has_data()) {
		Berichtsheft a;
		a.id = id;
		a.minuten = res[0];
		a.woche_fk = res[1];
		a.taetigkeit_fk = res[2];
		a.abteilung_fk = res[3];
		a.azubi_fk = res[4];
		return a;
	}

	throw std::runtime_error{ "Datensatz wurde nicht gefunden" };
}

std::vector<Berichtsheft> BerichtsheftTabelle::List()
{
	auto res = mk::sqlite::result{ m_db, R"(
SELECT Berichtsheft_id FROM Berichtsheft ORDER BY minuten
)" };

	std::vector<Berichtsheft> vec;
	for (; res.has_data(); res.fetch()) {
		vec.push_back(Load(res[0]));
	}

	return vec;
}

void BerichtsheftTabelle::provision()
{
	mk::sqlite::execute(m_db, R"(
 CREATE TABLE berichtsheft (
    berichtsheft_id INTEGER PRIMARY KEY AUTOINCREMENT
    , minuten INTEGER
    , woche_fk INTEGER
    , taetigkeit_fk INTEGER
    , abteilung_fk INTEGER
    , azubi_fk INTEGER

	, FOREIGN KEY(woche_fk) REFERENCES woche(woche_id)
	, FOREIGN KEY(taetigkeit_fk) REFERENCES taetigkeit(taetigkeit_id)
	, FOREIGN KEY(abteilung_fk) REFERENCES abteilung(abteilung_id)
	, FOREIGN KEY(azubi_fk) REFERENCES azubi(azubi_id)
 );
)");
}
