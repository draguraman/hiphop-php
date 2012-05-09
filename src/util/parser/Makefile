
PROJECT_ROOT = ../../..

export \
BISON_PKGDATADIR=/usr/share/bison

all: lex.yy.cpp
	$(MAKE) -C $(PROJECT_ROOT)/src/compiler/parser
	$(MAKE) -C $(PROJECT_ROOT)/src/runtime/eval/parser
	@php $(PROJECT_ROOT)/bin/license.php

.PHONY: lex.yy.cpp
lex.yy.cpp: hphp.x
	@echo "Generating scanner code..."
	/usr/bin/flex -i -f -Phphp -R -8 --bison-locations \
		-o$@ $<

include $(PROJECT_ROOT)/src/rules.mk
