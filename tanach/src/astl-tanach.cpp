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

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unistd.h>
#include <astl/generator.hpp>
#include <astl/loader.hpp>
#include <astl/run.hpp>
#include "location.hpp"
#include "operators.hpp"
#include "parser.hpp"
#include "scanner.hpp"
#include "yytname.hpp"

using namespace std;
using namespace AstlTanach;
using namespace Astl;

class SyntaxTreeGeneratorForTanach: public SyntaxTreeGenerator {
   public:
      virtual NodePtr gen(int& argc, char**& argv) throw(Exception) {
	 if (argc == 0) {
	    throw Exception("no source file given");
	 }
	 char* source_name = *argv++; --argc;
	 ifstream source(source_name);
	 if (!source) {
	    std::ostringstream os;
	    os << "unable to open " << source_name;
	    throw Exception(os.str());
	 }
	 Scanner scanner(source, source_name);
	 NodePtr root;
	 parser p(scanner, root);
	 if (p.parse() != 0) {
	    std::ostringstream os;
	    os << "parsing of " << source_name << " failed";
	    throw Exception(os.str());
	 }
	 return root;
      }
};

int main(int argc, char** argv) {
   try {
      SyntaxTreeGeneratorForTanach astgen;
      Loader loader;
      char* path = getenv("ASTL_TANACH_PATH");
      if (path) {
	 char* dir = path;
	 for (char* cp = path; *cp; ++cp) {
	    if (*cp == ':') {
	       if (dir) {
		  * cp = 0;
		  loader.add_library(dir);
		  dir = 0;
	       }
	    } else if (!dir) {
	       dir = cp;
	    }
	 }
	 if (dir) loader.add_library(dir);
      } else {
	 // default path
	 loader.add_library("/home/borchert/misc/tanach/tanach/lib");
	 loader.add_library("/usr/local/share/astl/tanach");
	 loader.add_library("/usr/share/astl/tanach");
      }
      run(argc, argv, astgen, loader, Op::SPACE);
   } catch (Exception e) {
      cout << endl;
      cerr << e.what() << endl;
   } catch (std::exception& e) {
      cout << endl;
      cerr << e.what() << endl;
   }
}

/*

=head1 NAME

astl-tanach -- run Astl scripts for Tanach texts

=head1 SYNOPSIS

B<astl-tanach> F<astl-script>] F<tanach-text> [I<args>]

=head1 DESCRIPTION

Astl scripts can be started explicitly using the B<astl-tanach> interpreter
or implicitly using a shebang line in the first line of the script:

   #!/usr/bin/env astl-tanach

The construct using F</usr/bin/env> attempts to find F<astl-tanach>
anywhere in the user's path.

The text must be coded in UTF-8 and representing either a single verse
or an entire book in the format developed by the J. Alan Groves Center
for Advanced Biblical Research, downloadable at
http://www.tanach.us/Tanach.xml.  The text is parsed and an abstract
syntax tree is built. Any syntax errors cause the execution to be
aborted and an error message to be printed.

Once the abstract syntax tree is present, the Astl script is
loaded and executed following the execution order defined
in section 12.5 of the Report of the Astl Programming Language.

All arguments behind the text file are put into a list
and bound to the variable I<args> in the I<main> function.

=head1 EXAMPLE

The following example prints a warning message for each
assignment found within a condition:

   #!/usr/bin/env astl-c

   import printer;

   attribution rules {
      ("=" lvalue rvalue) as assignment in ("condition" *) as cond -> {
	 println("warning: assignment within a condition at ",
	    location(assignment), ": ", gentext(cond));
      };
   }

=head1 ENVIRONMENT

The environment variable I<ASTL_TANACH_PATH> can be used to specify
a colon-separated list of directories where library modules
are looked for. By default, F</usr/local/share/astl/tanach> and
F</usr/share/astl/tanach> are used. The script itself can add more
directories to the library search path using the Astl
library clause (see section 12.1 in the I<Report of the
Astl Programming Language>).

=head1 AUTHOR

Andreas F. Borchert

=cut

*/
