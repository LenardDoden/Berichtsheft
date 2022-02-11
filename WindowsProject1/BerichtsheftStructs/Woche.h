#pragma once

#include <cstdint>
#include <vector>
#include <string>


#include "../mk_sqlite/database.h"
#include "../mk_sqlite/statement.h"
#include "../mk_sqlite/result.h"

struct Woche {
	int64_t id{};
	std::string beginn;
	std::string ende;
	std::string ausbildungsjahr;
	int64_t abteilung_fk{};


	bool operator==(const Woche& other) const {
		return id == other.id && beginn == other.beginn && ende == other.ende && ausbildungsjahr == other.ausbildungsjahr && abteilung_fk == other.abteilung_fk;
	}
};


class WocheTabelle {
	mk::sqlite::database m_db;

	int64_t Insert(const Woche& val);

	int64_t Update(const Woche& val);

public:
	WocheTabelle(mk::sqlite::database db);

	int64_t Save(const Woche& val);

	Woche Load(int64_t id);

	std::vector<Woche> List();

	void provision();
};

