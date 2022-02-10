#include "database.h"

#include <sqlite3.h>

namespace mk {
namespace sqlite {


database::database(std::string _path)
   : path_{std::move(_path)}
{
   sqlite3* raw{};
   const auto rc = sqlite3_open(path_.c_str(), &raw);
   handle_ = {raw, &sqlite3_close};
   if (rc) {
      throw database_exception{rc, sqlite3_errmsg(raw)};
   }

}

const std::string& database::path () const 
{
   return path_;
}

int64_t database::last_autoincrement() const
{
	return sqlite3_last_insert_rowid(handle_.get());
}

database::operator sqlite3*() const
{
   return handle_.get();
}


}
}
