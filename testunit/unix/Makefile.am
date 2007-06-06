noinst_PROGRAMS = CDistTestUnit

INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/testunit

CDistTestUnit_SOURCES = \
	../CDistTestCase.cpp \
	../cppunitmain.cpp
	
if HAVE_LIBTOOL
CDistTestUnit_LDADD = ../../lib/unix/libcgbittorrent.la -lcppunit
else
CDistTestUnit_LDADD = ../../lib/unix/libcgbittorrent.a -lcppunit
endif
