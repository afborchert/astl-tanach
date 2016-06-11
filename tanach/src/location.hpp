/*
   Copyright (C) 2015 Andreas Franz Borchert
   ----------------------------------------------------------------------------
   The Astl Library for Tanach is free software; you can redistribute it
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

#ifndef ASTL_TANACH_LOCATION_H
#define ASTL_TANACH_LOCATION_H

#include "position.hh"
#include "location.hh"
#include <astl/treeloc.hpp>

namespace AstlTanach {

   inline Astl::Location make_loc(const location& loc) {
      return Astl::Location(
	 Astl::Position(
	    /* fix a bison bug where the initial position is w/o filename */
	    loc.begin.filename? loc.begin.filename: loc.end.filename,
	    loc.begin.line, loc.begin.column),
	 Astl::Position(loc.end.filename,
	    loc.end.line, loc.end.column));
   }

} // namespace AstlTanach

#endif
