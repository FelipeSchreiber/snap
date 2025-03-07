#
# Makefile for non-Microsoft compilers
#

all: MakeAll

test: TestAll

core: MakeCore

agmgen2: MakeAgm

bigclam: MakeBigClam

MakeAll:
	$(MAKE) -C snap-core
	$(MAKE) -C examples

TestAll:
	$(MAKE) run -C test

MakeCore:
	$(MAKE) -C snap-core

MakeAgm:
	$(MAKE) -C snap-core
	$(MAKE) -C examples/agmgen2

MakeBigClam:
	$(MAKE) -C snap-core
	$(MAKE) -C examples/bigclam

clean:
	$(MAKE) clean -C snap-core
	$(MAKE) clean -C examples
	$(MAKE) clean -C test
	$(MAKE) clean -C tutorials
