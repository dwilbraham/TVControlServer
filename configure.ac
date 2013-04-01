AC_INIT([tv_control_server], [0.0.1], [dwilbraham+git@gmail.com],
        [tv_control_server], [https://github.com/dwilbraham/TVControlServer])
AC_PREREQ([2.64])
AM_INIT_AUTOMAKE([1.11 -Wall no-define])

## debugging symbols
AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug],
  [include debug symbols (default is no)])],
  [use_debug=$enableval],
  [use_debug=no])

if test "x$use_debug" = "xyes"; then
  CXXFLAGS="$CXXFLAGS -ggdb"
fi

PKG_CHECK_MODULES([DEPS], [libcec >= 2:1:0])

AC_CONFIG_HEADERS([config.h])
AC_PROG_CXX
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
