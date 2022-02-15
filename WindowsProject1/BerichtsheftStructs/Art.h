#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "../mk_sqlite/database.h"
#include "../mk_sqlite/statement.h"
#include "../mk_sqlite/result.h"

struct Art {
	int64_t id{};
	std::string name;


	bool operator==(const Art& other) const {
		return id == other.id && name == other.name;
	}
};


class ArtTabelle {
	mk::sqlite::database m_db;

	int64_t Insert(const Art& val);

	int64_t Update(const Art& val);

public:
	ArtTabelle(mk::sqlite::database db);

	int64_t Save(const Art& val);

	Art Load(int64_t id);

	std::vector<Art> List();

	void provision();
};
