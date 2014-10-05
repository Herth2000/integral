include common.mk

.PHONY: all static shared samples clean

all:
	cd src && $(MAKE) $@

static:
	cd src && $(MAKE) $@

shared:
	cd src && $(MAKE) $@

samples: static
	cd samples && $(MAKE) all

install: all
	mkdir -p $(INSTALL_INC) $(INSTALL_LIB)
	install -p -m 0644 src/*.h $(INSTALL_INC)
	install -p -m 0644 src/$(INTEGRAL_STATIC_LIB_NAME) src/$(INTEGRAL_SHARED_LIB_NAME) $(INSTALL_LIB)

uninstall:
	$(RM) -R $(INSTALL_INC)
	$(RM) $(INSTALL_LIB)/$(INTEGRAL_STATIC_LIB_NAME) $(INSTALL_LIB)/$(INTEGRAL_SHARED_LIB_NAME)

clean:
	cd src && $(MAKE) $@
	cd samples && $(MAKE) $@
