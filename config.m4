dnl config.m4 for extension zimuge

PHP_ARG_ENABLE([zimuge],
  [whether to enable zimuge support],
  [AS_HELP_STRING([--enable-zimuge],
    [Enable zimuge support])],
  [no])

if test "$PHP_ZIMUGE" != "no"; then
  AC_DEFINE(HAVE_ZIMUGE, 1, [ Have zimuge support ])

  PHP_NEW_EXTENSION(zimuge, zimuge.c, $ext_shared)
fi
