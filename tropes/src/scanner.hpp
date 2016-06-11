/*
   Copyright (C) 2015 Andreas Franz Borchert
   ----------------------------------------------------------------------------
   The Astl Library for Tropes is free software; you can redistribute it
   and/or modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either version
   2 of the License, or (at your option) any later version.

   The Astl Library for Tropes is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef ASTL_TROPES_SCANNER_H
#define ASTL_TROPES_SCANNER_H

#include <iostream>
#include "location.hpp"
#include "parser.hpp"

namespace AstlTropes {

   typedef parser::semantic_type semantic_type;

   class Scanner {
      public:
	 Scanner(std::istream& in, const std::string& input_name);

	 // mutators
	 int get_token(semantic_type& yylval, location& yylloc);

      private:
	 std::istream& in;
	 std::string input_name;
	 unsigned char ch;
	 char32_t codepoint; // Unicode codepoint, delivered by next_codepoint()
	 bool eof_seen; // set by next_ch()
	 bool eof; // set by next_codepoint()
	 position oldpos, pos;
	 location tokenloc;
	 std::unique_ptr<std::string> tokenstr;

	 // private mutators
	 void next_ch();
	 void next_codepoint();
	 void error(char const* msg);
   };

   inline int yylex(semantic_type* yylval, location* yylloc, Scanner& scanner) {
      return scanner.get_token(*yylval, *yylloc);
   }

} // namespace AstlTropes

#endif
