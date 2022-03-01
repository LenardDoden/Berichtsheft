#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "../mk_sqlite/database.h"
#include "../mk_sqlite/statement.h"
#include "../mk_sqlite/result.h"

struct Taetigkeit {
	int64_t id{};
	std::string beschreibung;


	bool operator==(const Taetigkeit& other) const {
		return id == other.id 
		&& beschreibung == other.beschreibung;
	}
};


class TaetigkeitTabelle {
	mk::sqlite::database m_db;

	int64_t Insert(const Taetigkeit& val);

	int64_t Update(const Taetigkeit& val);

public:
	TaetigkeitTabelle(mk::sqlite::database db);

	int64_t Save(const Taetigkeit& val);

	Taetigkeit Load(int64_t id);

	std::vector<Taetigkeit> List();

	void provision();
};
#pragma once
