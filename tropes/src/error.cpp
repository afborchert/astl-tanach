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
#include <iostream>
#include "error.hpp"
#include "location.hpp"

namespace AstlTropes {

void yyerror(location const* loc, char const* msg) {
   std::cerr << make_loc(*loc) << ": " << msg << std::endl;
   std::exit(1);
}

void parser::error(const location_type& loc, const std::string& msg) {
   yyerror(&loc, msg.c_str());
}

} // namespace AstlTropes
