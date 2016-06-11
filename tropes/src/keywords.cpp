/*
   Copyright (C) 2015 Andreas Franz Borchert
   ----------------------------------------------------------------------------
   The Astl Library for Tropes is free software; you can redistribute it
   and/or modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either version
   2 of the License, or (at your option) any later version.

   The Astl Library for Tanach is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <cstdlib>
#include "keywords.hpp"
#include "parser.hpp"
#include "scanner.hpp"

namespace AstlTropes {

static struct {
   char const* keyword;
   int token;
} keywords[] = {
   /* regular keywords */
   {"book", parser::token::BOOK},
   {"clause", parser::token::CLAUSE},
   {"fragment", parser::token::FRAGMENT},
   {"letter", parser::token::LETTER},
   {"paragraph", parser::token::PARAGRAPH},
   {"verse", parser::token::VERSE},
   {"word", parser::token::WORD},
   /* Hebrew delimiters */
   {"maqaf", parser::token::MAQAF},
   {"paseq", parser::token::PASEQ},
   {"sof_pasuq", parser::token::SOF_PASUQ},
   /* characters used as paragraph markers */
   {"pe", parser::token::PE},
   {"samekh", parser::token::SAMEKH},
   {"nun_hafukha", parser::token::NUN_HAFUKHA},
   /* tropes */
   {"darga", parser::token::DARGA},
   {"etnahta", parser::token::ETNAHTA},
   {"geresh_muqdam", parser::token::GERESH_MUQDAM},
   {"geresh", parser::token::GERESH},
   {"gershayim", parser::token::GERSHAYIM},
   {"legarmeh", parser::token::LEGARMEH},
   {"mahapakh", parser::token::MAHAPAKH},
   {"merkha_kefula", parser::token::MERKHA_KEFULA},
   {"merkha", parser::token::MERKHA},
   {"metigah_zaqef", parser::token::METIGAH_ZAQEF},
   {"munah_zaqef", parser::token::MUNAH_ZAQEF},
   {"munah", parser::token::MUNAH},
   {"pashta", parser::token::PASHTA},
   {"pazer", parser::token::PAZER},
   {"qadma", parser::token::QADMA},
   {"qarney_para", parser::token::QARNEY_PARA},
   {"revia", parser::token::REVIA},
   {"segol", parser::token::SEGOL},
   {"shalshelet_gedolah", parser::token::SHALSHELET_GEDOLAH},
   {"shalshelet_qetannah", parser::token::SHALSHELET_QETANNAH},
   {"siluq", parser::token::SILUQ},
   {"telisha_gedola", parser::token::TELISHA_GEDOLA},
   {"telisha_qetana", parser::token::TELISHA_QETANA},
   {"tevir", parser::token::TEVIR},
   {"tipeha", parser::token::TIPEHA},
   {"yerah_ben_yomo", parser::token::YERAH_BEN_YOMO},
   {"yetiv", parser::token::YETIV},
   {"zaqef_gadol", parser::token::ZAQEF_GADOL},
   {"zaqef_qatan", parser::token::ZAQEF_QATAN},
   {"zarqa", parser::token::ZARQA},
   /* comments */
   {"xxxx", parser::token::COMMENT},
};

KeywordTable::KeywordTable() {
   for (std::size_t i = 0; i < sizeof(keywords)/sizeof(keywords[0]); ++i) {
      tab[keywords[i].keyword] = keywords[i].token;
   }
}

bool KeywordTable::lookup(const std::string& ident, int& token) const {
   std::map<std::string, int>::const_iterator it = tab.find(ident);
   if (it == tab.end()) {
      return false;
   } else {
      token = it->second;
      return true;
   }
}

KeywordTable keyword_table;

} // namespace AstlTropes
