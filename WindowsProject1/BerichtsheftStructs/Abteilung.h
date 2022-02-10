#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "../mk_sqlite/database.h"
#include "../mk_sqlite/statement.h"
#include "../mk_sqlite/result.h"

struct Abteilung {
	int64_t id{};
	std::string name;


	bool operator==(const Abteilung& other) const {
		return id == other.id && name == other.name;
	}
};


class AbteilungTabelle {
	mk::sqlite::database m_db;

	int64_t Insert(const Abteilung& val);

	int64_t Update(const Abteilung& val);

public:
	AbteilungTabelle(mk::sqlite::database db);

	int64_t Save(const Abteilung& val);
	
	Abteilung Load(int64_t id);

	std::vector<Abteilung> List();

	void provision();
};
