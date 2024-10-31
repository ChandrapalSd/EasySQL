#pragma once
#include "db.hpp"

namespace esql::api {
	void run(DB& db);
	DB& getDB();
}
