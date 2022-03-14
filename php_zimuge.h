/* zimuge extension for PHP */

#ifndef PHP_ZIMUGE_H
# define PHP_ZIMUGE_H

extern zend_module_entry zimuge_module_entry;
# define phpext_zimuge_ptr &zimuge_module_entry

# define PHP_ZIMUGE_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_ZIMUGE)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_ZIMUGE_H */
