//       $Id: scanner.h 41742 2020-11-21 13:18:22Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/bin/cepheiden/pfc/trunk/pfc/inc/pfc/scanner.h $
// $Revision: 41742 $
//     $Date: 2020-11-21 14:18:22 +0100 (Sa., 21 Nov 2020) $
//   $Author: p20068 $
//   Creator: Peter Kulczycki
//  Creation: November 14, 2020
// Copyright: (c) 2020 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg.
//            It is distributed under the Boost Software License (see
//            https://www.boost.org/users/license.html).

#pragma once

#undef  PFC_SCANNER_VERSION
#define PFC_SCANNER_VERSION "2.5.0"

#include <cassert>
#include <functional>
#include <iostream>
#include <locale>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

using namespace std::string_literals;
using namespace std::string_view_literals;

// -------------------------------------------------------------------------------------------------

namespace pfc { namespace scn { namespace details {

struct symbol_kind final {
   enum class tag_t {
      keyword, terminal_class, terminal_symbol, undefined
   };

   friend std::ostream & operator << (std::ostream & lhs, symbol_kind const & rhs) noexcept {
      return lhs << '{' << rhs.str << ',' << to_string_view (rhs.tag) << ',' << rhs.num << '}';
   }

   static constexpr std::string_view to_string_view (tag_t const tag) noexcept {
      switch (tag) {
         case tag_t::keyword:         return "kw"sv; break;
         case tag_t::terminal_class:  return "tc"sv; break;
         case tag_t::terminal_symbol: return "ts"sv; break;
         case tag_t::undefined:       return "ud"sv; break;
      }

      return "??"sv;
   }

   constexpr bool operator == (symbol_kind const & rhs) const noexcept {
      return (tag == rhs.tag) && (num == rhs.num);
   }

   constexpr bool operator != (symbol_kind const & rhs) const noexcept {
      return !operator == (rhs);
   }

   char             chr {};
   int              num {};
   std::string_view str {"undefined"sv};
   tag_t            tag {tag_t::undefined};
};

constexpr symbol_kind sk_keywd  {' ',   0, "keyword"sv,           symbol_kind::tag_t::keyword};
constexpr symbol_kind sk_ident  {' ',   1, "identifier"sv,        symbol_kind::tag_t::terminal_class};
constexpr symbol_kind sk_int    {' ',   2, "integer"sv,           symbol_kind::tag_t::terminal_class};
constexpr symbol_kind sk_real   {' ',   3, "real"sv,              symbol_kind::tag_t::terminal_class};
constexpr symbol_kind sk_str    {' ',   4, "string"sv,            symbol_kind::tag_t::terminal_class};
constexpr symbol_kind sk_assign {'=',   1, "assign"sv,            symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_caret  {'^',   2, "caret"sv,             symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_colon  {':',   3, "colon"sv,             symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_comma  {',',   4, "comma"sv,             symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_div    {'/',   5, "division"sv,          symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_dquote {'"',   6, "double quote"sv,      symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_eof    {'\0',  7, "end of file"sv,       symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_eol    {'\n',  8, "end of line"sv,       symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_lpar   {'(',   9, "left parenthesis"sv,  symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_minus  {'-',  10, "minus"sv,             symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_mult   {'*',  11, "multiply"sv,          symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_period {'.',  12, "period"sv,            symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_plus   {'+',  13, "plus"sv,              symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_rpar   {')',  14, "right parenthesis"sv, symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_semi   {';',  15, "semicolon"sv,         symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_space  {' ',  16, "space"sv,             symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_tab    {'\t', 17, "tabulator"sv,         symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_uscore {'_',  18, "underscore"sv,        symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_undef  {};

inline symbol_kind to_symbol_kind (char const c) noexcept {
   static std::unordered_map <char, symbol_kind> const map {
      {'=', sk_assign}, {'^',  sk_caret }, {':',  sk_colon }, {',', sk_comma}, {'/', sk_div  },
      {'"', sk_dquote}, {'\0', sk_eof   }, {'\n', sk_eol   }, {'(', sk_lpar }, {'-', sk_minus},
      {'*', sk_mult  }, {'.',  sk_period}, {'+',  sk_plus  }, {')', sk_rpar }, {';', sk_semi },
      {' ', sk_space }, {'\t', sk_tab   }, {'_',  sk_uscore}
   };

   if (auto const pos {map.find (c)}; pos != std::end (map)) {
      return pos->second;
   }

   return sk_undef;
}

inline auto to_string (char const c) {
   return std::string {to_symbol_kind (c).str};
}

template <typename T> constexpr bool is_alpha (T const c, std::locale const & locale = std::locale::classic ()) noexcept {
   return std::isalpha (c, locale) || std::char_traits <T>::eq (c, T {sk_uscore.chr});
}

template <typename T> constexpr bool is_digit (T const c, std::locale const & locale = std::locale::classic ()) noexcept {
   return std::isdigit (c, locale);
}

}   // namespace details

// -------------------------------------------------------------------------------------------------

struct exception final : std::runtime_error {
   explicit exception (std::string const & m) : std::runtime_error {m} {
   }
};

}   // namespace scn

// -------------------------------------------------------------------------------------------------

struct symbol final {
   constexpr symbol () noexcept = default;

   template <typename attr_t> constexpr symbol (scn::details::symbol_kind kind, attr_t attr) noexcept
      : m_kind {std::move (kind)}
      , m_attr {std::move (attr)} {
   }

   constexpr bool operator == (symbol const & rhs) const noexcept {
      return (m_kind == rhs.m_kind) && (m_attr == rhs.m_attr);
   }

   constexpr bool operator != (symbol const & rhs) const noexcept {
      return !operator == (rhs);
   }

// ------------------------------

   template <typename attr_t> constexpr attr_t const & get_attribute () const noexcept {
      return std::get <attr_t> (m_attr);
   }

   template <typename attr_t> constexpr bool holds_attribute () const noexcept {
      return std::holds_alternative <attr_t> (m_attr);
   }

// ------------------------------

   constexpr bool is (char const c) const noexcept {
      return (m_kind.tag == scn::details::symbol_kind::tag_t::terminal_symbol) && (m_kind.chr == c);
   }

   constexpr bool is_eof () const noexcept {
      return (m_kind == scn::details::sk_eof);
   }

   constexpr bool is_identifier () const noexcept {
      return (m_kind == scn::details::sk_ident) && holds_attribute <std::string> ();
   }

   constexpr bool is_integer () const noexcept {
      return (m_kind == scn::details::sk_int) && holds_attribute <int> ();
   }

   constexpr bool is_keyword () const noexcept {
      return (m_kind.tag == scn::details::symbol_kind::tag_t::keyword) && holds_attribute <std::string> ();
   }

   constexpr bool is_keyword (int const num) const noexcept {
      return is_keyword () && (m_kind.num == num);
   }

   bool is_keyword (std::string const & name) const noexcept {
      return get_keyword () == name;
   }

   constexpr bool is_real () const noexcept {
      return (m_kind == scn::details::sk_real) && holds_attribute <double> ();
   }

   constexpr bool is_number () const noexcept {
      return is_integer () || is_real ();
   }

   constexpr bool is_string () const noexcept {
      return (m_kind == scn::details::sk_str) && holds_attribute <std::string> ();
   }

   constexpr bool is_terminal_class () const noexcept {
      return m_kind.tag == scn::details::symbol_kind::tag_t::terminal_class;
   }

   constexpr bool is_terminal_symbol () const noexcept {
      return m_kind.tag == scn::details::symbol_kind::tag_t::terminal_symbol;
   }

// ------------------------------

   std::string get_identifier () const noexcept {
      return is_identifier () ? get_attribute <std::string> () : ""s;
   }

   constexpr int get_integer () const noexcept {
      return is_integer () ? get_attribute <int> () : 0;
   }

   std::string get_keyword () const noexcept {
      return is_keyword () ? get_attribute <std::string> () : ""s;
   }

   constexpr double get_number () const noexcept {
      if (is_integer ()) { return get_attribute <int> (); }
      if (is_real    ()) { return get_attribute <double> (); }

      return 0.0;
   }

   constexpr double get_real () const noexcept {
      return is_real () ? get_attribute <double> () : 0.0;
   }

   std::string get_string () const noexcept {
      return is_string () ? get_attribute <std::string> () : ""s;
   }

// ------------------------------

   std::ostream & write (std::ostream & out) const noexcept {
      out << '{' << m_kind;

      if (is_keyword () || is_terminal_class ()) {
         std::visit ([&out] (auto const & v) { out << ",'" << v << "'"; }, m_attr);
      }

      return out << '}';
   }

   friend std::ostream & operator << (std::ostream & lhs, symbol const & rhs) noexcept {
      return rhs.write (lhs);
   }

   scn::details::symbol_kind               m_kind {scn::details::sk_eof};
   std::variant <int, double, std::string> m_attr {0};
};

inline std::string to_string (symbol const & sym) noexcept {
   static std::ostringstream out; out.str (""); out << sym; return out.str ();
}

// -------------------------------------------------------------------------------------------------

class scanner final {
   public:
      scanner () noexcept {
         set_istream ();
      }

      explicit scanner (std::istream & in, bool const use_stream_exceptions = false) {
         set_istream (in, use_stream_exceptions);
      }

      scanner (std::istream &&) = delete;

      scanner (scanner const &) = delete;
      scanner (scanner &&) = default;

     ~scanner () = default;

      scanner & operator = (scanner const &) = delete;
      scanner & operator = (scanner &&) = default;

// ------------------------------

      constexpr symbol const & current_symbol () const noexcept {
         return m_current_symbol;
      }

      symbol const & next_symbol () {
         read_next_symbol (); return current_symbol ();
      }

      symbol const & next_symbol (char const chr) {
         if (!is (chr)) {
            throw scn::exception {
               "Expected '"s + scn::details::to_string (chr) + "' but have " + to_string (m_current_symbol) + '.'
            };
         }

         return next_symbol ();
      }

      symbol const & next_symbol (std::string const & name) {
         if (!is_keyword (name)) {
            throw scn::exception {
               "Expected keyword '"s + name + "' but have " + to_string (m_current_symbol) + '.'
            };
         }

         return next_symbol ();
      }

// ------------------------------

      template <typename attr_t> constexpr attr_t const & get_attribute () const noexcept {
         return m_current_symbol.get_attribute <attr_t> ();
      }

      std::string get_identifier () const noexcept {
         return m_current_symbol.get_identifier ();
      }

      constexpr int get_integer () const noexcept {
         return m_current_symbol.get_integer ();
      }

      constexpr double get_number () const noexcept {
         return m_current_symbol.get_number ();
      }

      constexpr double get_real () const noexcept {
         return m_current_symbol.get_real ();
      }

      std::string get_string () const noexcept {
         return m_current_symbol.get_string ();
      }

// ------------------------------

      constexpr bool is (char const c) const noexcept {
         return m_current_symbol.is (c);
      }

      constexpr bool is_eof () const noexcept {
         return m_current_symbol.is_eof ();
      }

      constexpr bool is_identifier () const noexcept {
         return m_current_symbol.is_identifier ();
      }

      constexpr bool is_integer () const noexcept {
         return m_current_symbol.is_integer ();
      }

      constexpr bool is_keyword () const noexcept {
         return m_current_symbol.is_keyword ();
      }

      constexpr bool is_keyword (int const num) const noexcept {
         return m_current_symbol.is_keyword (num);
      }

      bool is_keyword (std::string const & name) const noexcept {
         return m_current_symbol.is_keyword (name);
      }

      constexpr bool is_number () const noexcept {
         return m_current_symbol.is_number ();
      }

      constexpr bool is_real () const noexcept {
         return m_current_symbol.is_real ();
      }

      constexpr bool is_string () const noexcept {
         return m_current_symbol.is_string ();
      }

// ------------------------------

      constexpr bool has_symbol () const noexcept {
         return !is_eof ();
      }

// ------------------------------

      int register_keyword (std::string const & name) noexcept {
         auto kind {scn::details::sk_keywd};

         kind.num = static_cast <int> (std::size (m_keywords) + 1);
//       kind.str = name;

         return m_keywords.try_emplace (name, symbol {kind, name}).first->second.m_kind.num;
      }

// ------------------------------

      void set_istream () noexcept {
         m_p_in = nullptr; read_next_chr (); read_next_symbol ();
      }

      void set_istream (std::istream & in, bool const use_stream_exceptions = false) {
         if (use_stream_exceptions) {
//          in.exceptions (std::ios::badbit | std::ios::eofbit | std::ios::failbit);
         }

         m_p_in = &in; read_next_chr (); read_next_symbol ();
      }

      void set_istream (std::istream &&) = delete;

// ------------------------------

      std::ostream & write (std::ostream & out) const noexcept {
         out << (std::empty (m_keywords) ? "no " : "") << "registered keywords\n";

         for (auto const & k : m_keywords) {
            out << "  " << k.first << ": " << k.second << '\n';
         }

         return out << "current char:   " << scn::details::to_symbol_kind (m_current_chr) << "\n"
                       "current symbol: " << m_current_symbol      << '\n';
      }

      friend std::ostream & operator << (std::ostream & lhs, scanner const & rhs) noexcept {
         return rhs.write (lhs);
      }

   private:
      constexpr bool is_eof_chr () const noexcept {
         return m_current_chr == scn::details::sk_eof.chr;
      }

      constexpr bool is_eol_chr () const noexcept {
         return m_current_chr == scn::details::sk_eol.chr;
      }

      constexpr bool is_whitespace_chr () const noexcept {
         return (m_current_chr == scn::details::sk_space.chr) || (m_current_chr == scn::details::sk_tab.chr) || is_eol_chr ();
      }

// ------------------------------

      int keyword_is_registered (std::string const & name) const noexcept {
         if (auto const pos {m_keywords.find (name)}; pos != std::end (m_keywords)) {
            return pos->second.m_kind.num;
         }

         return -1;
      }

// ------------------------------

      void read_next_chr () noexcept {
         m_current_chr = scn::details::sk_eof.chr;

         if (m_p_in && *m_p_in) {
            m_p_in->get (m_current_chr);
         }
      }

      void read_next_symbol () {
         m_current_symbol = {}; bool scanned {false};

         while (!scanned) {
            if (is_eof_chr ()) {
               scanned = true;

            } else if (is_whitespace_chr ()) {
               read_next_chr ();

            } else if (scn::details::is_alpha (m_current_chr)) {
               scanned = scan_keyword_or_identifier ();

            } else if (scn::details::is_digit (m_current_chr)) {
               scanned = scan_number ();

            } else if (m_current_chr == scn::details::sk_period.chr) {
               read_next_chr ();

               if (scn::details::is_digit (m_current_chr)) {
                  scanned = scan_number (true);
               } else {
                  m_current_symbol = {scn::details::sk_period, 0}; scanned = true;
               }

            } else if (m_current_chr == scn::details::sk_dquote.chr) {
               scanned = scan_string ();

            } else if (m_current_chr == scn::details::sk_div.chr) {
               read_next_chr ();

                    if (m_current_chr == scn::details::sk_div .chr) { scan_comment_single_line (scn::details::sk_div.chr); }
               else if (m_current_chr == scn::details::sk_mult.chr) { scan_comment_multi_line  (scn::details::sk_div.chr); }

               else {
                  m_current_symbol = {scn::details::sk_div, 0}; scanned = true;
               }

            } else {
               m_current_symbol = {scn::details::to_symbol_kind (m_current_chr), 0};

               if ((scanned = m_current_symbol.is_terminal_symbol ()) == false) {
                  throw scn::exception {"Unknown character '"s + m_current_chr + "' encountered."};
               }

               read_next_chr ();
            }
         }
      }

// ------------------------------

      void scan_comment_multi_line (char prev_chr) {
         assert (prev_chr      == scn::details::sk_div .chr);
         assert (m_current_chr == scn::details::sk_mult.chr);

         auto        depth {0};
         std::string text  {prev_chr};

         do {
            text += m_current_chr; auto annihilate {false};

                 if (prev_chr == scn::details::sk_div .chr) { if (m_current_chr == scn::details::sk_mult.chr) { ++depth; annihilate = true; } }
            else if (prev_chr == scn::details::sk_mult.chr) { if (m_current_chr == scn::details::sk_div .chr) { --depth; annihilate = true; } }

            prev_chr = annihilate ? scn::details::sk_eof.chr : m_current_chr; read_next_chr ();
         } while ((depth > 0) && !is_eof_chr ());
      }

      void scan_comment_single_line (char const prev_chr) {
         assert (prev_chr      == scn::details::sk_div.chr);
         assert (m_current_chr == scn::details::sk_div.chr);

         std::string text {prev_chr};

         while (!is_eol_chr () && !is_eof_chr ()) {
            text += m_current_chr; read_next_chr ();
         }
      }

      bool scan_keyword_or_identifier () {
         assert (scn::details::is_alpha (m_current_chr));

         std::string text;

         while (scn::details::is_alpha (m_current_chr) || scn::details::is_digit (m_current_chr)) {
            text += m_current_chr; read_next_chr ();
         }

         if (auto const num {keyword_is_registered (text)}; num > 0) {
            m_current_symbol = {scn::details::sk_keywd, text}; m_current_symbol.m_kind.num = num;
         } else {
            m_current_symbol = {scn::details::sk_ident, text};
         }

         return true;
      }

      bool scan_number (bool have_period = false) {
         assert (scn::details::is_digit (m_current_chr));

         int integer_part {0};

         if (!have_period) {
            while (scn::details::is_digit (m_current_chr)) {
               integer_part = integer_part * 10 + (m_current_chr - '0'); read_next_chr ();
            }

            if (m_current_chr == scn::details::sk_period.chr) {
               have_period = true; read_next_chr ();
            }

            m_current_symbol = {scn::details::sk_int, integer_part};
         }

         if (have_period) {
            int    fractional_part {0};
            double exponent        {1};

            while (scn::details::is_digit (m_current_chr)) {
               fractional_part  = fractional_part * 10 + (m_current_chr - '0');
               exponent        *= 10;

               read_next_chr ();
            }

            m_current_symbol = {scn::details::sk_real, integer_part + fractional_part / exponent};
         }

         return true;
      }

      bool scan_string () {
         assert (m_current_chr == scn::details::sk_dquote.chr); read_next_chr ();

         bool        scanned {false};
         std::string text    {};

         while ((m_current_chr != scn::details::sk_dquote.chr) && !is_eol_chr () && !is_eof_chr ()) {
            text += m_current_chr; read_next_chr ();
         }

         if ((scanned = (m_current_chr == scn::details::sk_dquote.chr)) == true) {
            m_current_symbol = {scn::details::sk_str, text}; read_next_chr ();
         } else {
            throw scn::exception {
               "Expected terminating quote in string but have '"s + scn::details::to_string (m_current_chr) + "'."
            };
         }

         return scanned;
      }

      char                                     m_current_chr    {scn::details::sk_eof.chr};   //
      symbol                                   m_current_symbol {};                           //
      std::unordered_map <std::string, symbol> m_keywords       {};                           //
      std::istream *                           m_p_in           {nullptr};                    // non owning
};

}   // namespace pfc
