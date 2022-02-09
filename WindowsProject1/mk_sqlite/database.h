#pragma once

#include "exception.h"

#include <memory>
#include <string>

struct sqlite3;


namespace mk {
namespace sqlite {
   

   using database_exception = exception;

   class database {
   private:
	   using dbhandle = std::shared_ptr<sqlite3>;
      dbhandle handle_{};
      std::string path_;

   public:
      explicit database (std::string _path);
      const std::string& path () const;
      operator sqlite3* () const;
   };


}
}
