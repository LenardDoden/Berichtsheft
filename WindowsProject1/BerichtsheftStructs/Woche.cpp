#include "Woche.h"
#include "ValidationUtility.h"
#include <regex>

int64_t WocheTabelle::Insert(const Woche & val)
{
	mk::sqlite::execute(m_db, R"(
 INSERT INTO Woche (beginn, ende, ausbildungsjahr, abteilung_fk) VALUES (?, ?, ?, ?)
)", val.beginn, val.ende, val.ausbildungsjahr, val.abteilung_fk);
	return m_db.last_autoincrement();
}

int64_t WocheTabelle::Update(const Woche & val)
{
	mk::sqlite::execute(m_db, R"(
 UPDATE Woche SET (beginn, ende, ausbildungsjahr, abteilung_fk) = (?, ?, ?, ?) WHERE Woche_id = ?
)", val.beginn, val.ende, val.ausbildungsjahr, val.abteilung_fk, val.id);
	return val.id;
}

WocheTabelle::WocheTabelle(mk::sqlite::database db) : m_db(db) { }



int64_t WocheTabelle::Save(const Woche & val)
{
	/*
	if (validationUtility::isValid(val.beginn) == true && (validationUtility::isValid(val.ende) == true))
	{
		if (val.id == 0) {
			return Insert(val);
		}
		return Update(val);
		
	}

	throw std::runtime_error{ "Beginn/Ende falsch" };
	*/

	if (val.id == 0) {
		return Insert(val);
	}
	return Update(val);

	/*
	if (!val.beginn.size() == 10 && val.beginn[4] == '-' && val.beginn[7] == '-')
	{
		throw std::runtime_error{ "Falsches Datenformat. Bitte im Format 'YYYY-MM-DD' eingeben" };
	}

	else
	{
		if (val.id == 0) {
			return Insert(val);
		}
		return Update(val);
	}
	*/
	

}

Woche WocheTabelle::Load(int64_t id)
{
	auto res = mk::sqlite::result{ m_db, R"(
SELECT beginn, ende, ausbildungsjahr, abteilung_fk FROM Woche WHERE Woche_id = ?
)", id };

	if (res.has_data()) {
		Woche a;
		a.id = id;
		a.beginn = res[0];
		a.ende = res[1];
		a.ausbildungsjahr = res[2];
		a.abteilung_fk = res[3];
		return a;
	}

	throw std::runtime_error{ "Datensatz wurde nicht gefunden" };
}

std::vector<Woche> WocheTabelle::List()
{
	auto res = mk::sqlite::result{ m_db, R"(
SELECT Woche_id FROM Woche ORDER BY beginn
)" };

	std::vector<Woche> vec;
	for (; res.has_data(); res.fetch()) {
		vec.push_back(Load(res[0]));
	}

	return vec;
}




void WocheTabelle::provision()
{
	mk::sqlite::execute(m_db, R"(
CREATE TABLE woche (
    woche_id INTEGER PRIMARY KEY AUTOINCREMENT
    , beginn DATE
    , ende DATE 
    , ausbildungsjahr INTEGER
    , abteilung_fk INTEGER, FOREIGN KEY(abteilung_fk) REFERENCES abteilung(abteilung_fk)
 );
)");
}