AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = tv_control_server

tv_control_server_SOURCES = src/main.cpp \
                            src/controller.cpp src/controller.h

AM_CPPFLAGS = $(DEPS_CFLAGS)
tv_control_server_LDADD = $(DEPS_LIBS)
