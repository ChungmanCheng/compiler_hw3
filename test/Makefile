EXE     := ../parser
SRCS    := $(wildcard *.p)
OBJS    := $(patsubst %.p,output/%,$(SRCS))
SHELL   := /bin/bash

all: output $(OBJS)

output/%: %.p
	@-./$(EXE) $^ > $@.tab 2> >(sort -V >$@.info)

test: all
	@bash test.sh

check: all
	@bash check.sh

output:
	mkdir -p $@

clean:
	$(RM) -rf output
