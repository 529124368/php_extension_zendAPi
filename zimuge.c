/* zimuge extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_zimuge.h"

#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif
zend_class_entry *zimuge_ce;
//function ############# start
PHP_FUNCTION(zimuge_print)
{
	zval *var;
	zend_string *retval;
	//param 解析 start
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(var)
	ZEND_PARSE_PARAMETERS_END();
	//parma end
	retval = strpprintf(0, "hello wolrd %d", var);
	zval *real_val = Z_REFVAL_P(var);
	Z_STR_P(real_val) = zval_get_string(var); 
	RETURN_STR(retval);
}
ZEND_BEGIN_ARG_INFO(zimugeParms, 1)
ZEND_ARG_INFO(1,var)
ZEND_END_ARG_INFO()
const zend_function_entry zimuge_functions[]={
    PHP_FE(zimuge_print, zimugeParms)
    PHP_FE_END
};
//function ############# end

//class 定義
PHP_METHOD(zimuge_class,display)
{
	zval *name;
	zval *sex;
	name = zend_read_property(zimuge_ce,Z_OBJ_P(getThis()),"name",sizeof("name")-1,0,NULL);
	sex = zend_read_property(zimuge_ce,Z_OBJ_P(getThis()),"sex",sizeof("sex")-1,0,NULL);
	//php_var_dump(name, 1);
    php_printf("%s %s\n",name->value.str->val,sex->value.str->val);
}
//Mehtod ---- getName
PHP_METHOD(zimuge_class,getName) {
	zval *name;
	name = zend_read_property(zimuge_ce,Z_OBJ_P(getThis()),"name",sizeof("name")-1,0,NULL);
	RETURN_STR(zval_get_string(name)); 
}
//Mehtod ---- getSex
PHP_METHOD(zimuge_class,getSex){
	zval *sex;
	sex = zend_read_property(zimuge_ce,Z_OBJ_P(getThis()),"sex",sizeof("sex")-1,0,NULL);
	RETURN_STR(zval_get_string(sex));
}
//Mehtod ---- setName
PHP_METHOD(zimuge_class,setName) {
	char *name;
	size_t name_len;
	ZEND_PARSE_PARAMETERS_START(1,1)
		Z_PARAM_STRING(name,name_len)
	ZEND_PARSE_PARAMETERS_END();
	zend_update_property_string(zimuge_ce,Z_OBJ_P(getThis()),"name",sizeof("name")-1,name);
}
//Mehtod ---- setSex
PHP_METHOD(zimuge_class,setSex) {
	zend_string *sex;
	ZEND_PARSE_PARAMETERS_START(1,1)
		Z_PARAM_STR(sex)
	ZEND_PARSE_PARAMETERS_END();
	zend_update_property_str(zimuge_ce,Z_OBJ_P(getThis()),"sex",sizeof("sex")-1,sex);
}
//Mehtod ---- __construct
PHP_METHOD(zimuge_class,__construct)
{
	char *name;
	char *sex;
	zval *info;
	zend_array *t;
	size_t name_len;
	size_t sex_len;
	//param 解析 start
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STRING(name,name_len) 
		Z_PARAM_STRING(sex,sex_len)
		Z_PARAM_ARRAY(info)
	ZEND_PARSE_PARAMETERS_END();
	//parma end
	zend_update_property_string(zimuge_ce,Z_OBJ_P(getThis()),"name",sizeof("name")-1,name);
	zend_update_property_string(zimuge_ce,Z_OBJ_P(getThis()),"sex",sizeof("sex")-1,sex);
	t = Z_ARRVAL_P(info);
    //php_printf("构造函数start....%s..%s..%d.....\n",name,sex,zend_hash_num_elements(t));
	//############
	zend_ulong num_idx;
	zend_string *str_idx;
	zval *entry;
	//loop
	ZEND_HASH_FOREACH_KEY_VAL(t, num_idx, str_idx, entry) {
        if (str_idx) {
            zend_printf("string key=%s \n", str_idx->val);
        } else {
            zend_printf("numerical key=%d \n", num_idx);
        }
        if (Z_TYPE_P(entry) == IS_LONG) {
            zend_long value = Z_LVAL_P(entry);
            zend_printf("numerical value=%d \n", value);
        } else if (Z_TYPE_P(entry) == IS_STRING) {
            zend_string *value = Z_STR_P(entry);
            zend_printf("string value=%s \n", value->val);
        }
    } ZEND_HASH_FOREACH_END();
}

//パラメータ定義
ZEND_BEGIN_ARG_INFO(null, 0)
ZEND_END_ARG_INFO()
// add method to list
const zend_function_entry ext_functions[]={
    PHP_ME(zimuge_class,display,null,ZEND_ACC_PUBLIC)
	PHP_ME(zimuge_class,getName,null,ZEND_ACC_PUBLIC)
	PHP_ME(zimuge_class,setName,null,ZEND_ACC_PUBLIC)
	PHP_ME(zimuge_class,setSex,null,ZEND_ACC_PUBLIC)
	PHP_ME(zimuge_class,getSex,null,ZEND_ACC_PUBLIC)
	PHP_ME(zimuge_class,__construct,null,ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_FE_END
};
//MINIt
PHP_MINIT_FUNCTION(zimuge){
	zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "zimuge_class" , ext_functions);
    zimuge_ce = zend_register_internal_class(&ce);
	//
	zend_declare_property_null(zimuge_ce,"name",sizeof("name")-1,ZEND_ACC_PRIVATE);
    zend_declare_property_null(zimuge_ce,"sex",sizeof("sex")-1,ZEND_ACC_PRIVATE);
	return SUCCESS;
}
//###########################
PHP_MINFO_FUNCTION(zimuge)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "zimuge support", "enabled");
	php_info_print_table_row(2, "author", "zimuge"); /* Replace with your name */
	php_info_print_table_end();
}
//PINT 
PHP_RINIT_FUNCTION(zimuge)
{
#if defined(ZTS) && defined(COMPILE_DL_ZIMUGE)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

zend_module_entry zimuge_module_entry = {
	STANDARD_MODULE_HEADER,
	"zimuge",					/* Extension name */
	zimuge_functions,					/* zend_function_entry */
	PHP_MINIT(zimuge),				/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(zimuge),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(zimuge),			/* PHP_MINFO - Module info */
	PHP_ZIMUGE_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ZIMUGE
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(zimuge)
#endif
