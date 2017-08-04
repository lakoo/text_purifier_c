TESTS =
check_PROGRAMS =
check_SCRIPTS =

################################################################################

TESTS += cppcheck.sh
check_SCRIPTS += cppcheck.sh

################################################################################

TESTS += test
check_PROGRAMS += test

AM_CXXFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/lib/include -Wpedantic -Wall -Wextra -Werror
AM_LDFLAGS = -L$(top_srcdir)/src -I$(top_srcdir)/lib/src

test_LDADD = -lcppunit -ltextpurifier

test_SOURCES = \
	main.cpp \
	test.cpp

################################################################################

TESTS += valgrind.sh
check_SCRIPTS += valgrind.sh
