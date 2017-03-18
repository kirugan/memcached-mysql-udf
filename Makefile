PLUGIN_DIR = /usr/lib/mysql/plugin/
INCLUDE_DIR = /usr/include/mysql
OBJFILE = udf_memcached2.so

all: $(OBJFILE)

$(OBJFILE):
	$(CC) -fPIC -I $(INCLUDE_DIR) -shared -o $(OBJFILE) udf_memcached.c
install:
	cp $(OBJFILE) $(PLUGIN_DIR)
clean:
	rm *.so
