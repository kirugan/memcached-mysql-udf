PLUGIN_DIR = /usr/lib/mysql/plugin/
INCLUDE_DIR = /usr/include/mysql
OBJFILE = udf_memcached2.so

all: $(OBJFILE)

$(OBJFILE): .FORCE
	$(CC) -fPIC -I $(INCLUDE_DIR) -shared -o $(OBJFILE) udf_memcached.c -Wl,--whole-archive /usr/lib/x86_64-linux-gnu/libmemcached.so -Wl,--no-whole-archive
install:
	cp $(OBJFILE) $(PLUGIN_DIR)
clean:
	rm *.so

.FORCE: