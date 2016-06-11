/*
   Copyright (C) 2015 Andreas Franz Borchert
   ----------------------------------------------------------------------------
   The Astl Library for Tanach is free software; you can redistribute it
   and/or modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either version
   2 of the License, or (at your option) any later version.

   Astl Library for Tanach is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef ASTL_TANACH_SCANNER_H
#define ASTL_TANACH_SCANNER_H

#include <iostream>
#include <memory>
#include "parser.hpp"
#include "location.hpp"

namespace AstlTanach {

   typedef parser::semantic_type semantic_type;

   class Scanner {
      public:
	 Scanner(std::istream& in_param, const std::string& input_name_param);

	 // mutators
	 int get_token(semantic_type& yylval, location& yylloc);

      private:
	 std::istream& in;
	 std::string input_name;
	 unsigned char ch; // individual byte, delivered by nextch()
	 char32_t unicode_char; // Unicode codepoint, delivered by next_unicode()
	 bool eof_seen; // set by nextch()
	 bool eof; // set by next_codepoint
	 int lasttoken; // last token returned by get_token()
	 position oldpos, pos;
	 location tokenloc;
	 std::unique_ptr<std::string> tokenstr;
	 bool multi_char_sequence;
	 bool enable_white;

	 // private mutators
	 void nextch();
	 void next_unicode();
	 void error(char const* msg);
   };

   inline int yylex(semantic_type* yylval, location* yylloc, Scanner& scanner) {
      return scanner.get_token(*yylval, *yylloc);
   }

} // namespace AstlTanach

#endif
