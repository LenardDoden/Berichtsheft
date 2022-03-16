#pragma once

#include "../wx/clntdata.h"

struct DatabaseID : wxClientData 
{ 
	int64_t id;
	wxDateTime Datum;
	DatabaseID(int64_t _id) : id(_id) { }
};

