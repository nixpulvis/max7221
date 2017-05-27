PREFIX = /usr/local/Cellar
LIBRARY = max7221
VERSION = 0.0.3

TARGET = $(PREFIX)/$(LIBRARY)/$(VERSION)
AVRM = $(PREFIX)/avrm/0.0.4

DEPENDENCIES = $(TARGET) $(AVRM)

include $(AVRM)/Makefile
