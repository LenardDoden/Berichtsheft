#include "statement.h"

#include <sqlite3.h>

namespace mk {
namespace sqlite {


statement_exception::statement_exception(int _errorcode, const std::string& _errmsg, const std::string& _query)
   : exception{_errorcode, _errmsg + "\nquery:\n\n" + _query}
{
}

bind_exception::bind_exception(int _errorcode, const std::string& _errmsg, int _index, const std::string& _datatype, const std::string& _query)
   : exception{_errorcode, _errmsg + "\nindex: " + std::to_string(_index) + ", datatype: " + _datatype + "\nquery:\n\n" + _query}
{
}

statement::statement (database _db, std::string _sql)
   : db_{std::move(_db)}
   , sql_{std::move(_sql)}
{
   sqlite3_stmt* raw{};
   const auto rc = sqlite3_prepare_v2(db_, sql_.c_str(), (int)sql_.size(), &raw, nullptr);
   handle_ = {raw, &sqlite3_finalize};
   if (rc) {
      throw statement_exception{rc, sqlite3_errmsg(db_), sql_};
   }
}



statement& statement::bind_at (int _pos, const std::string& _val)
{
   const auto rc = sqlite3_bind_text(*this, _pos, _val.c_str(), (int)_val.size(), SQLITE_TRANSIENT);
   if (rc) {
      throw bind_exception{rc, sqlite3_errmsg(db_), _pos, "text", sql_};
   }
   return *this;
}

statement& statement::bind_at (int _pos, int _val) 
{
   const auto rc = sqlite3_bind_int(*this, _pos, _val);
   if (rc) {
      throw bind_exception{rc, sqlite3_errmsg(db_), _pos, "int", sql_};
   }
   return *this;
}

statement& statement::bind_at (int _pos, int64_t _val) 
{
   const auto rc = sqlite3_bind_int64(*this, _pos, _val);
   if (rc) {
      throw bind_exception{rc, sqlite3_errmsg(db_), _pos, "int64", sql_};
   }

   return *this;
}

statement& statement::bind_at (int _pos, const std::vector<unsigned char> _val) 
{
   const auto rc = sqlite3_bind_blob(*this, _pos, _val.data(), (int)_val.size(), SQLITE_TRANSIENT);
   if (rc) {
      throw bind_exception{rc, sqlite3_errmsg(db_), _pos, "blob", sql_};
   }
   return *this;
}

      
statement::operator sqlite3_stmt* () const 
{
   return handle_.get();
}

statement::operator sqlite3* () const 
{
   return db_;
}


}
}
