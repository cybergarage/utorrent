noinst_PROGRAMS = printpeers

INCLUDES = -I$(top_srcdir)/include

printpeers_SOURCES = \
	../printpeers.c
	
if HAVE_LIBTOOL
printpeers_LDADD = ../../../lib/unix/libcgbittorrent.la
else
printpeers_LDADD = ../../../lib/unix/libcgbittorrent.a
endif
