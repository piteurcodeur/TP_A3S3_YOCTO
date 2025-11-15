esme-gpio-toggle: esme-gpio-toggle.o
	$(CC) $(LDFLAGS) -o $@ $< $(LDLIBS)

# Règles implicites conservées (CC, LD, etc.)
CFLAGS += $(shell pkg-config --cflags libgpiod)
LDLIBS += $(shell pkg-config --libs libgpiod)

# Variable INSTALL_DIR avec valeur par défaut
INSTALL_DIR ?= ./.install

# Cible install
install: esme-gpio-toggle
	install -d $(INSTALL_DIR)/usr/bin
	install -m 0755 esme-gpio-toggle $(INSTALL_DIR)/usr/bin/
	install -d $(INSTALL_DIR)/etc/init.d
	install -m 0755 esme-gpio26-toggle $(INSTALL_DIR)/etc/init.d/

# Cible clean
clean:
	rm -f esme-gpio-toggle *.o
	rm -rf $(INSTALL_DIR)
