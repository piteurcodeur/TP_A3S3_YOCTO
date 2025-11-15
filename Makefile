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

# Cible clean
clean:
	rm -f esme-gpio-toggle *.o
	rm -rf $(INSTALL_DIR)
