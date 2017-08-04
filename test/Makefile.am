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

TESTS += test-gcov
check_PROGRAMS += test-gcov

test_gcov_CXXFLAGS = ${AM_CXXFLAGS} -ftest-coverage -fprofile-arcs
test_gcov_LDFLAGS = ${AM_LDFLAGS} -ftest-coverage -fprofile-arcs

test_gcov_LDADD = -lcppunit -ltextpurifier.gcov

test_gcov_SOURCES = ${test_SOURCES}

################################################################################

TESTS += valgrind.sh
check_SCRIPTS += valgrind.sh

################################################################################

clean-local:
	rm -f *.gcda *.gcno *.gcov
