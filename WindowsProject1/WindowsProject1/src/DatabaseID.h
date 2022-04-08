#pragma once

#include "../wx/clntdata.h"

struct DatabaseID : wxClientData 
{ 
	int64_t id;
	wxDateTime Datum;
	int64_t azubi_id;
	DatabaseID(int64_t _id) : id(_id) { }/*int64_t azubi_id*/
};

