#include <stdio.h>
#include <string.h>
#include <libmemcached/memcached.h>

int main() {
    char* config = "--SERVER=127.0.0.1:11211";
    memcached_st* mc = memcached(config, strlen(config));
    if (mc == NULL) {
        printf("Init failed\n");
    }

    char* key = "somekey";
    char* value = "VALUE333";

    time_t expire_time = time(NULL) + 1000;

    memcached_return_t result = memcached_set(
            mc, key, strlen(key),
            value, strlen(value), expire_time, 0);

    const char* err = memcached_last_error_message(mc);
    printf("Error: %s\n", err);
    memcached_free(mc);

    printf("Done\n");
}