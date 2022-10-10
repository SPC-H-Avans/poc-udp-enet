BIN := $(shell basename $$(pwd))

MANSECTION := 1
MANPAGE := $(BIN).$(MANSECTION)

SRCS := $(wildcard *.cpp)
OBJS := $(subst .cpp,.o,$(SRCS))
DEPS := $(subst .cpp,.d,$(SRCS))

CXX ?= g++
PKG_CONFIG ?= pkg-config

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
CONFIGDIR ?= $(PREFIX)/etc
DATADIR ?= $(PREFIX)/share
MANDIR ?= $(DATADIR)/man/man
DOCDIR ?= $(DATADIR)/$(BIN)/doc

RM := /bin/rm -f
INSTALL := /usr/bin/install -c

CXXFLAGS := $(CXXFLAGS) -Wshadow -Wall -Wpedantic -Wextra \
	-g -fno-strict-aliasing -std=c++17 -pthread
ifeq ($(DEBUG),1)
	CXXFLAGS += -D DEBUG -O0
else
	CXXFLAGS += -D NDEBUG -O3
endif

LDLIBS := -lm -lpthread

.PHONY: all clean install

all: $(BIN)

$(BIN): $(OBJS) $(DEPS)
	$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(BIN)

%.o: %.cpp %.d Makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -MT $@ -MF $*.d -c $<

-include *.d

%.d: ;

clean:
	$(RM) $(OBJS) $(DEPS) $(BIN)

install: $(BIN)
	$(INSTALL) -d $(BINDIR)
	$(INSTALL) $(BIN) $(BINDIR)
	# uncomment next 2 lines if you have a man page
	#$(INSTALL) -d $(MANDIR)$(MANSECTION)
	#$(INSTALL) $(MANPAGE) $(MANDIR)$(MANSECTION)
