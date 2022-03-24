#pragma once

#include <cstdint>
#include <vector>
#include <string>


#include "../mk_sqlite/database.h"
#include "../mk_sqlite/statement.h"
#include "../mk_sqlite/result.h"

struct Berichtsheft {
	int64_t id{};
	int64_t minuten{};
	int64_t woche_fk{};
	int64_t taetigkeit_fk{};
	int64_t azubi_fk{};


	bool operator==(const Berichtsheft& other) const {
		return id == other.id && minuten == other.minuten && woche_fk == other.woche_fk && taetigkeit_fk == other.taetigkeit_fk && azubi_fk == other.azubi_fk;
	}
};



class BerichtsheftTabelle {
	mk::sqlite::database m_db;

	int64_t Insert(const Berichtsheft& val);

	int64_t Update(const Berichtsheft& val);

public:
	BerichtsheftTabelle(mk::sqlite::database db);

	int64_t Save(const Berichtsheft& val);

	Berichtsheft Load(int64_t id);

	std::vector<Berichtsheft> List();

	void provision();
};


