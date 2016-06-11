AstlPath := ../../astl
System := $(shell uname -s)
BisonSources :=	$(wildcard *.ypp)
GeneratedCPPSourcesFromBison := $(patsubst %.ypp,%.tab.cpp,$(BisonSources))
GeneratedCPPSources := $(GeneratedCPPSourcesFromBison) \
   yytname.cpp operators.cpp
GeneratedHPPSources := $(patsubst %.ypp,%.tab.hpp,$(BisonSources)) \
   operators.hpp $(wildcard *.hh)
CPPSources := $(GeneratedCPPSources) \
   error.cpp scanner.cpp testlex.cpp \
   testparser.cpp run.cpp
Objects := $(patsubst %.cpp,%.o,$(CPPSources))
MainCPPSources := astl-tanach.cpp testlex.cpp
MainObjects := $(patsubst %.cpp,%.o,$(MainCPPSources))
stt_lib := $(AstlPath)/astl/libastl.a
core_objs := error.o parser.tab.o scanner.o \
   yytname.o operators.o
testlex_objs := $(core_objs) testlex.o $(stt_lib)
testparser_objs := $(core_objs) testparser.o $(stt_lib)
run_objs := $(core_objs) run.o $(stt_lib)
astltanach_objs := $(core_objs) astl-tanach.o $(stt_lib)
Utils := $(AstlPath)/bison-scripts
Binaries := testlex testparser run astl-tanach

CXX :=		g++
CXXFLAGS :=	-Wall -g -O2
LDFLAGS :=
CPPFLAGS +=	-I$(AstlPath) -std=gnu++14
LDLIBS := -lgmp -lpcre2-8
BISON := bison

.PHONY:		all clean depend
all:		$(GeneratedCPPSourcesFromBison) $(Objects) $(Binaries)
clean:		; rm -f $(Objects) $(GeneratedCPPSources) c-parser.output \
		   $(MainObjects)
realclean:	clean
		rm -f $(GeneratedCPPSources) $(GeneratedHPPSources) \
		   $(Binaries)

testlex:	$(testlex_objs)
		$(CXX) $(LDFLAGS) -o $@ $(testlex_objs) $(LDLIBS)
testparser:	$(testparser_objs)
		$(CXX) $(LDFLAGS) -o $@ $(testparser_objs) $(LDLIBS)
run:		$(run_objs)
		$(CXX) $(LDFLAGS) -o $@ $(run_objs) $(LDLIBS)
astl-tanach:	$(astltanach_objs)
		$(CXX) $(LDFLAGS) -o $@ $(astltanach_objs) $(LDLIBS)

yytname.cpp:	parser.tab.cpp
		perl $(Utils)/extract_yytname.pl AstlTanach parser.tab.cpp >$@

operators.hpp operators.cpp:	parser.tab.cpp operators.txt
		perl $(Utils)/gen_operators.pl -op operators.txt AstlTanach astl/operator.hpp parser.tab.cpp \
		  operators.hpp operators.cpp

$(GeneratedCPPSourcesFromBison): %.tab.cpp: %.ypp
	$(BISON) -d $<

c-parser.tab.o:	operators.hpp

depend:		$(CPPSources)
		gcc-makedepend $(CPPFLAGS) $(CPPSources) $(MainCPPSources)
# DO NOT DELETE
parser.tab.o: parser.tab.cpp ../../astl/astl/syntax-tree.hpp \
 ../../astl/astl/attribute.hpp ../../astl/astl/exception.hpp \
 ../../astl/astl/treeloc.hpp ../../astl/astl/location.hpp \
 ../../astl/astl/position.hh ../../astl/astl/location.hh \
 ../../astl/astl/position.hh ../../astl/astl/function.hpp \
 ../../astl/astl/arity.hpp ../../astl/astl/bindings.hpp \
 ../../astl/astl/types.hpp ../../astl/astl/builtin-functions.hpp \
 ../../astl/astl/integer.hpp ../../astl/astl/context.hpp \
 ../../astl/astl/operator.hpp ../../astl/astl/token.hpp operators.hpp \
 scanner.hpp parser.hpp location.hpp position.hh location.hh yystype.hpp \
 parser.tab.hpp stack.hh yytname.hpp
yytname.o: yytname.cpp
operators.o: operators.cpp ../../astl/astl/operator.hpp \
 ../../astl/astl/token.hpp
error.o: error.cpp error.hpp location.hpp position.hh location.hh \
 ../../astl/astl/treeloc.hpp ../../astl/astl/location.hpp \
 ../../astl/astl/position.hh ../../astl/astl/location.hh \
 ../../astl/astl/position.hh parser.hpp yystype.hpp \
 ../../astl/astl/syntax-tree.hpp ../../astl/astl/attribute.hpp \
 ../../astl/astl/exception.hpp ../../astl/astl/function.hpp \
 ../../astl/astl/arity.hpp ../../astl/astl/bindings.hpp \
 ../../astl/astl/types.hpp ../../astl/astl/builtin-functions.hpp \
 ../../astl/astl/integer.hpp ../../astl/astl/context.hpp \
 ../../astl/astl/operator.hpp ../../astl/astl/token.hpp parser.tab.hpp \
 stack.hh
scanner.o: scanner.cpp ../../astl/astl/syntax-tree.hpp \
 ../../astl/astl/attribute.hpp ../../astl/astl/exception.hpp \
 ../../astl/astl/treeloc.hpp ../../astl/astl/location.hpp \
 ../../astl/astl/position.hh ../../astl/astl/location.hh \
 ../../astl/astl/position.hh ../../astl/astl/function.hpp \
 ../../astl/astl/arity.hpp ../../astl/astl/bindings.hpp \
 ../../astl/astl/types.hpp ../../astl/astl/builtin-functions.hpp \
 ../../astl/astl/integer.hpp ../../astl/astl/context.hpp \
 ../../astl/astl/operator.hpp ../../astl/astl/token.hpp \
 ../../astl/astl/utf8.hpp error.hpp location.hpp position.hh location.hh \
 parser.hpp yystype.hpp parser.tab.hpp stack.hh scanner.hpp
testlex.o: testlex.cpp ../../astl/astl/token.hpp location.hpp position.hh \
 location.hh ../../astl/astl/treeloc.hpp ../../astl/astl/location.hpp \
 ../../astl/astl/position.hh ../../astl/astl/location.hh \
 ../../astl/astl/position.hh parser.hpp yystype.hpp \
 ../../astl/astl/syntax-tree.hpp ../../astl/astl/attribute.hpp \
 ../../astl/astl/exception.hpp ../../astl/astl/function.hpp \
 ../../astl/astl/arity.hpp ../../astl/astl/bindings.hpp \
 ../../astl/astl/types.hpp ../../astl/astl/builtin-functions.hpp \
 ../../astl/astl/integer.hpp ../../astl/astl/context.hpp \
 ../../astl/astl/operator.hpp parser.tab.hpp stack.hh scanner.hpp \
 yytname.hpp
testparser.o: testparser.cpp ../../astl/astl/token.hpp location.hpp \
 position.hh location.hh ../../astl/astl/treeloc.hpp \
 ../../astl/astl/location.hpp ../../astl/astl/position.hh \
 ../../astl/astl/location.hh ../../astl/astl/position.hh parser.hpp \
 yystype.hpp ../../astl/astl/syntax-tree.hpp \
 ../../astl/astl/attribute.hpp ../../astl/astl/exception.hpp \
 ../../astl/astl/function.hpp ../../astl/astl/arity.hpp \
 ../../astl/astl/bindings.hpp ../../astl/astl/types.hpp \
 ../../astl/astl/builtin-functions.hpp ../../astl/astl/integer.hpp \
 ../../astl/astl/context.hpp ../../astl/astl/operator.hpp parser.tab.hpp \
 stack.hh scanner.hpp yytname.hpp
run.o: run.cpp ../../astl/astl/run.hpp ../../astl/astl/exception.hpp \
 ../../astl/astl/treeloc.hpp ../../astl/astl/location.hpp \
 ../../astl/astl/position.hh ../../astl/astl/location.hh \
 ../../astl/astl/position.hh ../../astl/astl/generator.hpp \
 ../../astl/astl/types.hpp ../../astl/astl/loader.hpp \
 ../../astl/astl/syntax-tree.hpp ../../astl/astl/attribute.hpp \
 ../../astl/astl/function.hpp ../../astl/astl/arity.hpp \
 ../../astl/astl/bindings.hpp ../../astl/astl/builtin-functions.hpp \
 ../../astl/astl/integer.hpp ../../astl/astl/context.hpp \
 ../../astl/astl/operator.hpp ../../astl/astl/token.hpp location.hpp \
 position.hh location.hh operators.hpp parser.hpp yystype.hpp \
 parser.tab.hpp stack.hh scanner.hpp yytname.hpp
astl-tanach.o: astl-tanach.cpp ../../astl/astl/generator.hpp \
 ../../astl/astl/exception.hpp ../../astl/astl/treeloc.hpp \
 ../../astl/astl/location.hpp ../../astl/astl/position.hh \
 ../../astl/astl/location.hh ../../astl/astl/position.hh \
 ../../astl/astl/types.hpp ../../astl/astl/loader.hpp \
 ../../astl/astl/syntax-tree.hpp ../../astl/astl/attribute.hpp \
 ../../astl/astl/function.hpp ../../astl/astl/arity.hpp \
 ../../astl/astl/bindings.hpp ../../astl/astl/builtin-functions.hpp \
 ../../astl/astl/integer.hpp ../../astl/astl/context.hpp \
 ../../astl/astl/operator.hpp ../../astl/astl/token.hpp \
 ../../astl/astl/run.hpp location.hpp position.hh location.hh \
 operators.hpp parser.hpp yystype.hpp parser.tab.hpp stack.hh scanner.hpp \
 yytname.hpp
testlex.o: testlex.cpp ../../astl/astl/token.hpp location.hpp position.hh \
 location.hh ../../astl/astl/treeloc.hpp ../../astl/astl/location.hpp \
 ../../astl/astl/position.hh ../../astl/astl/location.hh \
 ../../astl/astl/position.hh parser.hpp yystype.hpp \
 ../../astl/astl/syntax-tree.hpp ../../astl/astl/attribute.hpp \
 ../../astl/astl/exception.hpp ../../astl/astl/function.hpp \
 ../../astl/astl/arity.hpp ../../astl/astl/bindings.hpp \
 ../../astl/astl/types.hpp ../../astl/astl/builtin-functions.hpp \
 ../../astl/astl/integer.hpp ../../astl/astl/context.hpp \
 ../../astl/astl/operator.hpp parser.tab.hpp stack.hh scanner.hpp \
 yytname.hpp
