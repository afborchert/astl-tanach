/*
   Copyright (C) 2015 Andreas Franz Borchert
   ----------------------------------------------------------------------------
   The Astl Tanach Library is free software; you can redistribute it
   and/or modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either version
   2 of the License, or (at your option) any later version.

   Astl Tanach Library is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <iomanip>
#include <memory>
#include <sstream>
#include <astl/syntax-tree.hpp>
#include <astl/token.hpp>
#include <astl/utf8.hpp>
#include "error.hpp"
#include "location.hpp"
#include "scanner.hpp"

using namespace Astl;

namespace AstlTanach {

// private functions =========================================================
static bool is_space(char32_t unicode_char) {
   return unicode_char == ' ' || unicode_char == '\n' ||
      unicode_char == '\t' || unicode_char == '\r' ||
      unicode_char == 0xa0 /* non-breaking space */;
}

static bool is_digit(char32_t unicode_char) {
   return unicode_char >= '0' && unicode_char <= '9';
}

// constructor ===============================================================

Scanner::Scanner(std::istream& in_param, const std::string& input_name_param) :
      in(in_param), input_name(input_name_param),
      ch(0), unicode_char(0), eof_seen(false), eof(false),
      tokenstr(nullptr), multi_char_sequence(false), enable_white(false) {
   pos.initialize(&input_name);
   nextch();
   next_unicode();
}

// mutator ===================================================================

int Scanner::get_token(semantic_type& yylval, location& yylloc) {
   int token = 0;
   yylval = NodePtr(nullptr);

   /* convert sequences of white space into one SPACE token */
   bool space = false;
   yylloc = tokenloc;
   while (!eof) {
      if (is_space(unicode_char)) {
	 do {
	    next_unicode();
	 } while (is_space(unicode_char));
	 space = true;
      } else if (unicode_char == '*') {
	 /* inserted in the tanach.us texts for some unknown reason;
	    we simply ignore them */
	 next_unicode();
      } else {
	 break;
      }
   }
   tokenloc.begin = oldpos;
   /* do not insert a SPACE in front of VERSE_END */
   if (space && unicode_char == 0x202c) {
      enable_white = false;
   }
   if (space && enable_white) {
      token = parser::token::SPACE;
   } else if (!eof && unicode_char == 0x202a) {
      /* left-to-right embedding,
	 we treat this as comment until we see 0x202c
	 (used by the text at tanach.us)
      */
      next_unicode();
      std::string tokenval;
      multi_char_sequence = true;
      /* within comments we accept only ASCII characters */
      while (!eof && unicode_char < 0x80) {
	 add_codepoint(tokenval, unicode_char);
	 next_unicode();
      }
      token = parser::token::COMMENT; enable_white = false;
      if (!eof) {
	 if (unicode_char != 0x202c) {
	    error("expected left-to-right comment section"
	       " to be closed with U+202c");
	 }
	 next_unicode();
      }
      yylloc = tokenloc;
      multi_char_sequence = false;
      yylval = std::make_shared<Node>(make_loc(tokenloc),
	 Token(token, tokenval, std::move(tokenstr)));
   } else if (!eof) {
      if (is_digit(unicode_char)) {
	 next_unicode();
	 multi_char_sequence = true;
	 while (!eof && is_digit(unicode_char)) {
	    next_unicode();
	 }
	 token = parser::token::INTEGER; enable_white = false;
      } else {
	 enable_white = true;
	 switch (unicode_char) {
	    /* special cases: */
	    case 0x202b: token = parser::token::VERSE_BEGIN; break;
	    case 0x202c: token = parser::token::VERSE_END; enable_white = false; break;
	    case 0x200D: token = parser::token::ZERO_WIDTH_JOINER; break;
	    /* regular Hebrew characters and accents */
	    case 0x0591: token = parser::token::ETNAHTA; break;
	    case 0x0592: token = parser::token::SEGOL; break;
	    case 0x0593: token = parser::token::SHALSHELET; break;
	    case 0x0594: token = parser::token::ZAQEF_QATAN; break;
	    case 0x0595: token = parser::token::ZAQEF_GADOL; break;
	    case 0x0596: token = parser::token::TIPEHA; break;
	    case 0x0597: token = parser::token::REVIA; break;
	    case 0x0598: token = parser::token::TSINNORIT; break; /* sic! */
	    case 0x0599: token = parser::token::PASHTA; break;
	    case 0x059A: token = parser::token::YETIV; break;
	    case 0x059B: token = parser::token::TEVIR; break;
	    case 0x059C: token = parser::token::GERESH; break;
	    case 0x059D: token = parser::token::GERESH_MUQDAM; break;
	    case 0x059E: token = parser::token::GERSHAYIM; break;
	    case 0x059F: token = parser::token::QARNEY_PARA; break;
	    case 0x05A0: token = parser::token::TELISHA_GEDOLA; break;
	    case 0x05A1: token = parser::token::PAZER; break;
	    case 0x05A2: token = parser::token::ATNAH_HAFUKH; break;
	    case 0x05A3: token = parser::token::MUNAH; break;
	    case 0x05A4: token = parser::token::MAHAPAKH; break;
	    case 0x05A5: token = parser::token::MERKHA; break;
	    case 0x05A6: token = parser::token::MERKHA_KEFULA; break;
	    case 0x05A7: token = parser::token::DARGA; break;
	    case 0x05A8: token = parser::token::QADMA; break;
	    case 0x05A9: token = parser::token::TELISHA_QETANA; break;
	    case 0x05AA: token = parser::token::YERAH_BEN_YOMO; break;
	    case 0x05AB: token = parser::token::OLE; break;
	    case 0x05AC: token = parser::token::ILUY; break;
	    case 0x05AD: token = parser::token::DEHI; break;
	    case 0x05AE: token = parser::token::ZARQA; break; /* sic! */
	    case 0x05AF: token = parser::token::MASORA_CIRCLE; break;
	    case 0x05B0: token = parser::token::SHEVA; break;
	    case 0x05B1: token = parser::token::HATAF_SEGOL; break;
	    case 0x05B2: token = parser::token::HATAF_PATAH; break;
	    case 0x05B3: token = parser::token::HATAF_QAMATS; break;
	    case 0x05B4: token = parser::token::HIRIQ; break;
	    case 0x05B5: token = parser::token::TSERE; break;
	    case 0x05B6: token = parser::token::POINT_SEGOL; break;
	    case 0x05B7: token = parser::token::POINT_PATAH; break;
	    case 0x05B8: token = parser::token::POINT_QAMATS; break;
	    case 0x05B9: token = parser::token::POINT_HOLAM; break;
	    case 0x05BA: token = parser::token::POINT_HOLAM_HASER_FOR_VAV; break;
	    case 0x05BB: token = parser::token::POINT_QUBUTS; break;
	    case 0x05BC: token = parser::token::POINT_DEGESH_OR_MAPIQ; break;
	    case 0x05BD: token = parser::token::POINT_METEG; break;
	    case 0x05BE: token = parser::token::MAQAF; break;
	    case 0x05BF: token = parser::token::POINT_RAFE; break;
	    case 0x05C0: token = parser::token::PASEQ; break;
	    case 0x05C1: token = parser::token::SHIN_DOT; break;
	    case 0x05C2: token = parser::token::POINT_SIN_DOT; break;
	    case 0x05C3: token = parser::token::SOF_PASUQ; enable_white = false; break;
	    case 0x05C4: token = parser::token::MARK_UPPER_DOT; break;
	    case 0x05C5: token = parser::token::MARK_LOWER_DOT; break;
	    case 0x05C6: token = parser::token::NUN_HAFUKHA; break;
	    case 0x05C7: token = parser::token::QAMATS_QATAN; break;
	    case 0x05D0: token = parser::token::ALEF; break;
	    case 0x05D1: token = parser::token::BET; break;
	    case 0x05D2: token = parser::token::GIMEL; break;
	    case 0x05D3: token = parser::token::DALET; break;
	    case 0x05D4: token = parser::token::HE; break;
	    case 0x05D5: token = parser::token::VAV; break;
	    case 0x05D6: token = parser::token::ZAYIN; break;
	    case 0x05D7: token = parser::token::HET; break;
	    case 0x05D8: token = parser::token::TET; break;
	    case 0x05D9: token = parser::token::YOD; break;
	    case 0x05DA: token = parser::token::FINAL_KAF; break;
	    case 0x05DB: token = parser::token::KAF; break;
	    case 0x05DC: token = parser::token::LAMED; break;
	    case 0x05DD: token = parser::token::FINAL_MEM; break;
	    case 0x05DE: token = parser::token::MEM; break;
	    case 0x05DF: token = parser::token::FINAL_NUN; break;
	    case 0x05E0: token = parser::token::NUN; break;
	    case 0x05E1: token = parser::token::SAMEKH; break;
	    case 0x05E2: token = parser::token::AYIN; break;
	    case 0x05E3: token = parser::token::FINAL_PE; break;
	    case 0x05E4: token = parser::token::PE; break;
	    case 0x05E5: token = parser::token::FINAL_TSADI; break;
	    case 0x05E6: token = parser::token::TSADI; break;
	    case 0x05E7: token = parser::token::QOF; break;
	    case 0x05E8: token = parser::token::RESH; break;
	    case 0x05E9: token = parser::token::SHIN; break;
	    case 0x05EA: token = parser::token::TAV; break;
	    default:
	       {
		  std::ostringstream os;
		  os << "invalid character: U+"
		     << std::hex << std::setw(4) << std::setfill('0')
		     << std::uppercase
		     << unicode_char
		     << std::nouppercase
		     << ", i.e. neither Hebrew nor white space";
		  error(os.str().c_str());
	       }
	 }
	 next_unicode();
      }
      std::string s(*tokenstr);
      yylval = std::make_shared<Node>(make_loc(tokenloc),
	 Token(token, std::move(tokenstr)));
      // create attributes that help in the generation of output
      AttributePtr dict = yylval->get_attribute();
      {
	 std::ostringstream os;
	 os << std::hex << std::setw(4) << std::setfill('0')
	    << std::uppercase
	    << unicode_char
	    << std::nouppercase;
	 dict->update("unicode_hex", std::make_shared<Attribute>(os.str()));
	 dict->update("utf8", std::make_shared<Attribute>(s));
      }
      multi_char_sequence = false;
      yylloc = tokenloc;
   }

   return token;
}

/*
 * get next character from the input stream, if available
 */
void Scanner::nextch() {
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

void Scanner::next_unicode() {
   char32_t char_val = 0;
   unsigned int expected = 0;
   tokenloc.end = oldpos;
   if (eof_seen) {
      eof = true; unicode_char = 0; return;
   }
   if (!multi_char_sequence) {
      tokenstr = std::make_unique<std::string>();
   }
   if (tokenstr != nullptr && unicode_char) {
      convert_to_utf8(std::back_inserter(*tokenstr), unicode_char);
   }
   for(;;) {
      if (expected) {
	 if ((ch >> 6) == 2) {
	    char_val = (char_val << 6) | (ch & ((1<<6)-1));
	    if (--expected == 0) {
	       unicode_char = char_val; break;
	    }
	 } else {
	    error("invalid Unicode byte sequence");
	 }
      } else if ((ch & 0x80) == 0) {
	 unicode_char = ch; break;
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
	 error("invalid Unicode byte sequence");
      }
      nextch();
   }
   nextch();

   if (unicode_char == '\n') {
      pos.lines();
   } else if (unicode_char == '\t') {
      unsigned blanks = 8 - (pos.column - 1) % 8;
      pos.columns(blanks);
   } else {
      pos.columns();
   }
}

void Scanner::error(char const* msg) {
   yyerror(&tokenloc, msg);
}

} // namespace AstlTanach
