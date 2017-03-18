// #include <libmemcached/memcached.h>

#ifdef STANDARD
/* STANDARD is defined, don't use any mysql functions */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef __WIN__
typedef unsigned __int64 ulonglong;	/* Microsofts 64 bit types */
typedef __int64 longlong;
#else
typedef unsigned long long ulonglong;
typedef long long longlong;
#endif /*__WIN__*/
#else
#include <my_global.h>
#include <my_sys.h>
#if defined(MYSQL_SERVER)
#include <m_string.h>		/* To get strmov() */
#else
/* when compiled as standalone */
#include <string.h>
#define strmov(a,b) stpcpy(a,b)
#define bzero(a,b) memset(a,0,b)
#endif
#endif
#include <mysql.h>
#include <ctype.h>

#ifdef HAVE_DLOPEN

my_bool mc_set_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 3)
  {
    strmov(message, "MC_SET accepts only three arguments");
    return 1;
  }

  if (args->arg_type[0] != STRING_RESULT || args->arg_type[1] != STRING_RESULT || args->arg_type[2] != INT_RESULT)
  {
    strmov(message, "wrong argument types: MC_SET() requires STRING, STRING, INT");
    return 1;
  }

  initid->ptr= (char*)"Wrong length";
  initid->max_length = 100;
  return 0;
}

char * mc_set(UDF_INIT *initid, UDF_ARGS *args __attribute__((unused)),
                char *result, unsigned long *length,
                char *is_null, char *error __attribute__((unused)))
{
  strmov(result, initid->ptr);
  *length= (uint) strlen(result);
  *is_null= 0;
  return result;
}

#endif /* HAVE_DLOPEN */