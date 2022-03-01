#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "../mk_sqlite/database.h"
#include "../mk_sqlite/statement.h"
#include "../mk_sqlite/result.h"

struct Azubi {
	int64_t id{};
	std::string vorname;
	std::string nachname;


	bool operator==(const Azubi& other) const {
		return id == other.id 
		&& vorname == other.vorname 
		&& nachname == other.nachname;
	}
};


class AzubiTabelle {
	mk::sqlite::database m_db;

	int64_t Insert(const Azubi& val);

	int64_t Update(const Azubi& val);

public:
	AzubiTabelle(mk::sqlite::database db);

	int64_t Save(const Azubi& val);

	Azubi Load(int64_t id);

	std::vector<Azubi> List();

	void provision();
};

