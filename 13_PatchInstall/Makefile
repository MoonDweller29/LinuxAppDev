# xgettext --keyword=_ --language=C --add-comments --sort-output -o po/number_diviner.pot number_diviner.c
# msginit --input=po/number_diviner.pot --locale=ru --output=po/number_diviner_ru.po
# msgfmt --output-file=number_diviner.mo po/number_diviner_ru.po

CC = gcc

TGT_NAME = number_diviner

INSTALL_PATH = /usr

ifdef DESTDIR
	INSTALL_PATH = $(abspath $(DESTDIR))
endif

LOCALE_PATH = $(INSTALL_PATH)/share/locale/
BIN_DIR = $(INSTALL_PATH)/bin/


all: $(BIN_DIR)$(TGT_NAME) $(LOCALE_PATH)ru/LC_MESSAGES/$(TGT_NAME).mo


$(BIN_DIR)$(TGT_NAME): $(TGT_NAME).c
	mkdir -p $(BIN_DIR)
	$(CC) -DLOCALE_PATH=\"$(LOCALE_PATH)\" $< -o $@

$(LOCALE_PATH)%/LC_MESSAGES/$(TGT_NAME).mo: po/$(TGT_NAME).%.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

po/$(TGT_NAME).%.po: po/$(TGT_NAME).pot
	msgmerge -U $@ $<

po/$(TGT_NAME).pot: $(TGT_NAME).c
	xgettext -k_ -c $(TGT_NAME).c -o update.pot
	msgmerge -U $@ update.pot


.PHONY: clean uninstall

uninstall:
	rm -f $(BIN_DIR)$(TGT_NAME)
	rm -f $(LOCALE_PATH)*/LC_MESSAGES/$(TGT_NAME).mo

clean: uninstall
	rm -f po/*.pot~ po/*.po~ update.pot
ifeq (/usr, $(INSTALL_PATH))
else
	rm -rf $(BIN_DIR)
	rm -rf $(LOCALE_PATH)
endif
