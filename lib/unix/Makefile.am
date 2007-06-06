if HAVE_LIBTOOL
lib_LTLIBRARIES = libcgbittorrent.la
else
lib_LIBRARIES = libcgbittorrent.a
endif

INCLUDES = -I$(top_srcdir)/include

########################################
# Sources
########################################

cgbittorrent_source = \
	../../src/cybergarage/bittorrent/cbencoding.c \
	../../src/cybergarage/bittorrent/cbencoding_list.c \
	../../src/cybergarage/bittorrent/cbencoding_parse.c \
	../../src/cybergarage/bittorrent/cbencoding_print.c \
	../../src/cybergarage/bittorrent/cbencoding_string.c \
	../../src/cybergarage/bittorrent/cbittorrent.c \
	../../src/cybergarage/bittorrent/cdictionary.c \
	../../src/cybergarage/bittorrent/cdictionary_element.c \
	../../src/cybergarage/bittorrent/cdictionary_parse.c \
	../../src/cybergarage/bittorrent/cdictionary_print.c \
	../../src/cybergarage/bittorrent/cdictionary_string.c \
	../../src/cybergarage/bittorrent/chttp_fetch.c \
	../../src/cybergarage/bittorrent/cmetainfo.c \
	../../src/cybergarage/bittorrent/cmetainfo_fetch.c \
	../../src/cybergarage/bittorrent/cmetainfo_file.c \
	../../src/cybergarage/bittorrent/cmetainfo_parse.c \
	../../src/cybergarage/bittorrent/cmetainfo_print.c \
	../../src/cybergarage/bittorrent/cpeer.c \
	../../src/cybergarage/bittorrent/cpeer_list.c \
	../../src/cybergarage/bittorrent/csha1.c \
	../../src/cybergarage/bittorrent/ctracker.c \
	../../src/cybergarage/bittorrent/ctracker_fetch.c \
	../../src/cybergarage/bittorrent/ctracker_parse.c

########################################
# Library
########################################

libcgbittorrentincludedir = $(includedir)/cybergarage
nobase_libcgbittorrentinclude_HEADERS =  \
        $(cgbittorrent_header)

if HAVE_LIBTOOL
libcgbittorrent_la_SOURCES = \
        $(cgbittorrent_source)
libcgbittorrent_a_CFLAGS = $(AM_CFLAGS)
libcgbittorrent_la_LIBADD =
else
libcgbittorrent_a_SOURCES = \
        $(cgbittorrent_source)
libcgbittorrent_a_CFLAGS = $(AM_CFLAGS)
libcgbittorrent_a_LIBADD =
endif
