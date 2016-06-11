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

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unistd.h>
#include <astl/run.hpp>
#include "location.hpp"
#include "operators.hpp"
#include "parser.hpp"
#include "scanner.hpp"
#include "yytname.hpp"

using namespace std;
using namespace Astl;
using namespace AstlTropes;

static char* cmdname;

void usage() {
   cerr << "Usage: " << cmdname << " source rules [pattern [count]]" << endl;
   exit(1);
}

int main(int argc, char** argv) {
   cmdname = *argv++; --argc;
   /* fetch source argument */
   if (argc == 0) usage();
   char* source_name = *argv++; --argc;
   ifstream source(source_name);
   if (!source) {
      std::cerr << cmdname << ": unable to open " << source_name
	 << std::endl;
      exit(1);
   }
   /* fetch rules argument */
   if (argc == 0) usage();
   char* rules_name = *argv++; --argc;
   /* fetch pattern argument, if given */
   unsigned int count = 0; char* pattern = 0;
   if (argc > 0) {
      pattern = *argv++; --argc;
   }
   /* fetch count argument, if given */
   if (argc > 0) {
      char* count_string = *argv++; --argc;
      count = atoi(count_string);
      if (count < 1) usage();
   }
   /* all arguments should have been processed by now */
   if (argc > 0) usage();

   try {
      Scanner scanner(source, source_name);
      NodePtr root;
      parser p(scanner, root);
      if (p.parse() != 0) exit(1);

      run(root, rules_name, pattern, count, Op::BOOK, cout);
   } catch (Exception e) {
      cout << endl;
      cerr << e.what() << endl;
   }
}
