# -----------------------------------------------------------------------------
# CMake project wrapper Makefile ----------------------------------------------
# -----------------------------------------------------------------------------

RM    := rm -rf
MKDIR := mkdir -p
MAKE = gmake --no-print-directory

.PHONY: all compile clean test reload

all: compile test


compile: ./build/Makefile
	@ $(MAKE) -C build/

./build/Makefile:
	  ($(MKDIR) build)
	  (cd build && cmake3 .. )

test:
	@ cd ./build && ctest3

reload:	all test

clean:
	-@ $(RM) ./build
