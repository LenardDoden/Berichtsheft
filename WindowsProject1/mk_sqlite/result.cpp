#include "result.h"

#include <cassert>

#include <sqlite3.h>

namespace mk {
namespace sqlite {


result::result (statement _stmt) 
   : stmt_{std::move(_stmt)}
{
   fetch();
}

result::result (database _db, std::string _sql) 
   : result{statement{std::move(_db), std::move(_sql)}}
{
}

result::~result () noexcept
{
   (void)sqlite3_reset(stmt_);
}

int result::column_count () const 
{
   return sqlite3_column_count(stmt_);
}

std::string result::column_name (int _index) const
{
   assert(_index < column_count());
   return sqlite3_column_name(stmt_, _index);
}

result& result::fetch () 
{
   const auto rc = sqlite3_step(stmt_);
   if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
      throw result_exception{rc, sqlite3_errmsg(stmt_)};
   }

   has_data_ = (rc != SQLITE_DONE);
   return *this;
}

bool result::has_data () const 
{
   return has_data_;
}

void result::column_check_data (int _index) const 
{
   assert(_index < column_count());
   assert(has_data());
   (void)_index;
}

std::string result::column_text (int _index) const 
{
   column_check_data(_index);
   return std::string{
      reinterpret_cast<const char*>(sqlite3_column_text(stmt_, _index)), 
      static_cast<size_t>(sqlite3_column_bytes(stmt_, _index))
   };
}

int result::column_int (int _index) const 
{
   column_check_data(_index);
   return sqlite3_column_int(stmt_, _index);
}

int64_t result::column_int64 (int _index) const 
{
   column_check_data(_index);
   return sqlite3_column_int64(stmt_, _index);
}

std::vector<unsigned char> result::column_blob (int _index) const 
{
   column_check_data(_index);
   const auto first = reinterpret_cast<const unsigned char*>(sqlite3_column_blob(stmt_, _index));
   return std::vector<unsigned char>{
      first, 
      first + sqlite3_column_bytes(stmt_, _index)
   };
}

result::operator bool () const 
{
   return has_data();
} 

result& result::operator++ ()
{
   return fetch();
}


void execute (statement& _stmt) 
{
   (void)result{_stmt};
}

void execute (database& _db, const std::string& _query) 
{
   auto stmt = statement{_db, _query};
   execute(stmt);
}


}
}