#pragma once

#include "exception.h"
#include "database.h"

#include <memory>
#include <string>
#include <vector>

struct sqlite3_stmt;


namespace mk {
namespace sqlite {
   

   class statement_exception : public exception {
   public:
      statement_exception(int _errorcode, const std::string& _errmsg, const std::string& _query);
   };

   class bind_exception : public exception {
   public:
      bind_exception(int _errorcode, const std::string& _errmsg, int _index, const std::string& _datatype, const std::string& _query);
   };


   class statement {
   private:
      database db_;
      std::string sql_;
      using stmthandle = std::shared_ptr<sqlite3_stmt>;
      stmthandle handle_{};

      template<typename Arg>
      statement& bind_next (int pos, const Arg& first)
      {
         return bind_at(pos, first);
      }

      template<typename Arg, typename... Args>
      statement& bind_next (int _pos, const Arg& _first, Args... _args)
      {
         bind_at(_pos, _first);
         return bind_next(++_pos, _args...);
      }

   public:
      statement (database _db, std::string _sql);

      statement& bind_at (int _pos, const std::string& _val);
      statement& bind_at (int _pos, int _val);
      statement& bind_at (int _pos, int64_t _val);
      statement& bind_at (int _pos, const std::vector<unsigned char> _val);

      template<typename Arg>
      statement& bind (const Arg& _first) 
      {
         // The leftmost SQL parameter has an index of 1. (sic)
         bind_at(1, _first); 
         return *this;
      }

      template<typename Arg, typename... Args>
      statement& bind (const Arg& _first, Args... _args)
      {
         return bind_next(1, _first, _args...);
      }

      operator sqlite3_stmt* () const;
      operator sqlite3* () const;
   };


}
}