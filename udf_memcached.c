#include <libmemcached/memcached.h>
#include <my_global.h>
#include <my_sys.h>
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

    char* msg = malloc(sizeof(char) * 100);
    sprintf(msg, "Call at %ld", time(NULL));
  initid->ptr= msg;
  initid->max_length = strlen(msg);

  return 0;
}

char * mc_set(UDF_INIT *initid, UDF_ARGS *args __attribute__((unused)),
                char *result, unsigned long *length,
                char *is_null, char *error __attribute__((unused)))
{
    char* msg = malloc(sizeof(char) * 100);
    char* key = malloc(sizeof(char) * (args->lengths[0] + 1));
            strncpy(key, args->args[0], args->lengths[0]);
            key[args->lengths[0]] = '\0';



    char* config = "--SERVER=127.0.0.1:11211";
    memcached_st* mc = memcached(config, strlen(config));
    memcached_return_t mc_result = memcached_set(mc, args->args[0], args->lengths[0],
                                                     args->args[1], args->lengths[1],
                                                     time(NULL) + 1000,
                                                     0);

    memcached_free(mc);


    sprintf(msg, "test");

  strmov(result, msg);
  *length= (uint) strlen(result);
  *is_null= 0;
  return result;
}

#endif /* HAVE_DLOPEN */