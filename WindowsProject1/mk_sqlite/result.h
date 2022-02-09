#pragma once

#include "exception.h"
#include "database.h"
#include "statement.h"

#include <memory>
#include <string>


namespace mk {
namespace sqlite {
   

   using result_exception = exception;

   
   /// <summary>
   ///    <c>result</c> of a <c>statement</c>
   /// </summary>
   ///
   /// <example> process a result
   /// <code><![CDATA[
   ///    for (auto res = result{db, "SELECT * FROM person WHERE name LIKE ?", "Name 1%"}; res; ++res) {
   ///       std::cout << res[0] << ", " << res[1] << ", " << res[2] << "\n"
   ///    }
   /// ]]></code>
   /// </example>
   class result {
   private:
      statement stmt_;
      bool has_data_{};

      void column_check_data (int _index) const;

      class proxy {
         const result& result_;
         int index_{};

      public:
         proxy (const result& _result, int _index) : result_(_result), index_(_index) { }

         operator int () const { return result_.column_int(index_); }
         operator int64_t () const { return result_.column_int64(index_); }
         operator std::string () const { return result_.column_text(index_); }
         operator std::vector<unsigned char> () const { return result_.column_blob(index_); }

         int Int () const { return static_cast<int>(*this); }
         int64_t Int64 () const { return static_cast<int64_t>(*this); }
         std::string string () const { return static_cast<std::string>(*this); }
         std::vector<unsigned char> blob() const { return static_cast<std::vector<unsigned char>>(*this); }
      };

   public:
      explicit result (statement _stmt);
      result (database _db, std::string _sql);

      template<typename... Args>
      result (database _db, std::string _sql, Args... _args) 
         : stmt_{std::move(_db), std::move(_sql)}
      {
         stmt_.bind(_args...);
         fetch();
      }

      result (const result& /*other*/) = delete;
      result (result&& /*other*/) noexcept = default;
      result& operator= (const result& /*other*/) = delete;
      result& operator= (result&& /*other*/) noexcept = default;
      ~result () noexcept;

      int column_count () const;
      std::string column_name (int _index) const;
      std::string column_text (int _index) const;
      int column_int (int _index) const;
      int64_t column_int64 (int _index) const;
      std::vector<unsigned char> column_blob(int _index) const;

      proxy operator[] (int _index) const { return proxy{*this, _index}; }

      /// shortcut for <c>has_data</c>
      operator bool () const;

      /// shortcut for <c>fetch</c>
      result& operator++ (); 

      bool has_data () const;
      result& fetch ();
   };



   void execute (statement& _stmt);
   void execute (database& _db, const std::string& _query);

   template<typename... Args>
   void execute (database& _db, const std::string& _query, Args... _args) 
   {
      auto stmt = statement{_db, _query}.bind(_args...);
      execute(stmt);
   }


} // sqlite
} // mk

