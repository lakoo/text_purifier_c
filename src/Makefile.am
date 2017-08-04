lib_LTLIBRARIES = libtextpurifier.la

AM_CXXFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/lib/include -Wpedantic -Wall -Wextra -Werror

libtextpurifier_la_SOURCES = \
	text_purifier.cpp \
	../lib/src/char_node.cpp \
	../lib/src/filter_list.cpp \
	../lib/src/string_utils.cpp \
	../lib/src/text_purifier.cpp

################################################################################

check_LTLIBRARIES = libtextpurifier.gcov.la

libtextpurifier_gcov_la_CXXFLAGS = ${AM_CXXFLAGS} -ftest-coverage -fprofile-arcs
libtextpurifier_gcov_la_LDFLAGS = -ftest-coverage -fprofile-arcs

libtextpurifier_gcov_la_SOURCES = ${libtextpurifier_la_SOURCES}

################################################################################

clean-local:
	rm -f *.gcda *.gcno *.gcov
