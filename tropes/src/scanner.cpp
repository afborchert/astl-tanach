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

#include <memory>
#include <astl/syntax-tree.hpp>
#include <astl/token.hpp>
#include <astl/utf8.hpp>
#include "error.hpp"
#include "keywords.hpp"
#include "location.hpp"
#include "scanner.hpp"

using namespace Astl;

namespace AstlTropes {

// private functions =========================================================

bool is_letter(char32_t ch) {
   return ((ch >= 'a') && (ch <= 'z')) ||
      ((ch >= 'A') && (ch <= 'Z')) || ch == '_';
}

bool is_digit(char32_t ch) {
   return (ch >= '0') && (ch <= '9');
}

bool is_whitespace(char32_t ch) {
   return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' ||
      ch == '\f' || ch == '\v';
}

// constructor ===============================================================

Scanner::Scanner(std::istream& in, const std::string& input_name) :
      in(in), input_name(input_name), ch(0), codepoint(0),
      eof_seen(false), eof(false), tokenstr(nullptr) {
   pos.initialize(&this->input_name);
   next_ch(); next_codepoint();
}

// mutator ===================================================================

int Scanner::get_token(semantic_type& yylval, location& yylloc) {
   int token = 0;
   yylval = NodePtr(nullptr);

restart:
   for(;;) {
      if (eof) {
	 break;
      } else if (is_whitespace(codepoint)) {
	 next_codepoint();
      } else {
	 break;
      }
   }
   tokenloc.begin = oldpos;
   if (is_letter(codepoint)) {
      tokenstr = std::make_unique<std::string>();
      next_codepoint();
      while (is_letter(codepoint) || is_digit(codepoint)) {
	 next_codepoint();
      }
      int keyword_token;
      if (keyword_table.lookup(*tokenstr, keyword_token)) {
	 token = keyword_token;
	 /* a semantic value is no longer required for keywords */
	 tokenstr = nullptr;
	 if (token == parser::token::COMMENT) {
	    /* skip rest of line */
	    while (!eof && codepoint != '\n') {
	       next_codepoint();
	    }
	    next_codepoint();
	    goto restart;
	 }
      } else {
	 error("unknown keyword");
      }
   } else if (is_digit(codepoint)) {
      tokenstr = std::make_unique<std::string>();
      next_codepoint();
      while (is_digit(codepoint)) {
	 next_codepoint();
      }
      token = parser::token::INTEGER;
      yylval = std::make_shared<Node>(make_loc(tokenloc),
	 Token(token, std::move(tokenstr)));
   } else {
      switch (codepoint) {
	 case 0:
	    /* eof */
	    break;
	 case '"':
	    next_codepoint();
	    if (codepoint == 0x200f) {
	       next_codepoint();
	       tokenstr = std::make_unique<std::string>();
	       while (!eof && codepoint != 0x202c) {
		  next_codepoint();
	       }
	       if (eof) {
		  error("right-to-left sequnce not ended with U+202C");
	       }
	       token = parser::token::UTF8_STRING;
	       yylval = std::make_shared<Node>(make_loc(tokenloc),
		  Token(token, std::move(tokenstr)));
	       next_codepoint();
	       if (eof || codepoint != '"') {
		  error("string not ended with '\"'");
	       }
	       next_codepoint();
	    } else {
	       tokenstr = std::make_unique<std::string>();
	       while (!eof && codepoint != '"') {
		  next_codepoint();
	       }
	       if (eof) {
		  error("string not ended with '\"'");
	       }
	       token = parser::token::HEX_STRING;
	       yylval = std::make_shared<Node>(make_loc(tokenloc),
		  Token(token, std::move(tokenstr)));
	       next_codepoint();
	    }
	    break;
	 // punctuators
	 case '{':
	    next_codepoint(); token = parser::token::LBRACE; break;
	 case '}':
	    next_codepoint(); token = parser::token::RBRACE; break;
	 case ':':
	    next_codepoint(); token = parser::token::COLON; break;
	 case ',':
	    next_codepoint(); token = parser::token::COMMA; break;
	 default:
	    error("invalid token");
      }
   }

   yylloc = tokenloc;
   return token;
}

// private methods ===========================================================

/*
 * get next character from the input stream, if available
 */

void Scanner::next_ch() {
   oldpos = pos;
   if (eof_seen) {
      ch = 0; return;
   }
   char c;
   if (!in.get(c)) {
      eof_seen = true; ch = 0; return;
   }
   ch = c;
}

void Scanner::next_codepoint() {
   char32_t char_val = 0;
   unsigned int expected = 0;
   tokenloc.end = oldpos;
   if (eof_seen) {
      eof = true; codepoint = 0; return;
   }
   if (tokenstr != nullptr && codepoint) {
      convert_to_utf8(std::back_inserter(*tokenstr), codepoint);
   }
   for(;;) {
      if (expected) {
	 if ((ch >> 6) == 2) {
	    char_val = (char_val << 6) | (ch & ((1<<6)-1));
	    if (--expected == 0) {
	       codepoint = char_val; break;
	    }
	 } else {
	    error("invalid UTF-8 byte sequence");
	 }
      } else if ((ch & 0x80) == 0) {
	 codepoint = ch; break;
      } else if ((ch >> 5) == 6) {
	 /* lead character with one byte following */
	 char_val = ch & ((1<<5)-1); expected = 1;
      } else if ((ch >> 4) == 14) {
	 /* lead character with two bytes following */
	 char_val = ch & ((1<<4)-1); expected = 2;
      } else if ((ch >> 3) == 30) {
	 /* lead character with three bytes following */
	 char_val = ch & ((1<<3)-1); expected = 3;
      } else if ((ch >> 2) == 62) {
	 /* lead character with four bytes following */
	 char_val = ch & ((1<<2)-1); expected = 4;
      } else if ((ch >> 1) == 126) {
	 /* lead character with five bytes following */
	 char_val = ch & 1; expected = 5;
      } else {
	 error("invalid UTF-8 byte sequence");
      }
      next_ch();
   }
   next_ch();

   if (codepoint == '\n') {
      pos.lines();
   } else if (codepoint == '\t') {
      unsigned blanks = 8 - (pos.column - 1) % 8;
      pos.columns(blanks);
   } else {
      pos.columns();
   }
}

void Scanner::error(char const* msg) {
   yyerror(&tokenloc, msg);
}

} // namespace AstlTropes
