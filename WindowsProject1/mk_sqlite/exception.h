#pragma once

#include <stdexcept>

namespace mk {
namespace sqlite {

   class exception : public std::runtime_error {
      int errorcode_{};
   public:
      exception (int _errorcode, std::string _buffer) 
         : runtime_error{std::move(_buffer)}
         , errorcode_{_errorcode}
      {
      }

      int errorcode () const 
      {
         return errorcode_;
      }
   };

}
}