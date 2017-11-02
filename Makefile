# Prerequisites:
#	CppUTest built with extensions
export CPPUTEST_HOME = $(PWD)/cpputest
	
all: cpputest
	@echo CPPUTEST_HOME is $(CPPUTEST_HOME)
	make -i -C code
	make -i -C code-t0
	make -i -C code-t1
	make -i -C code-t2
	make -i -C code-t3

clean:
	make -i -C cpputest clean
	make -i -C code clean
	make -i -C code-t0 clean
	make -i -C code-t1 clean
	make -i -C code-t2 clean
	make -i -C code-t3 clean

.PHONY: cpputest
cpputest: cpputest/lib/libCppUTest.a

cpputest/lib/libCppUTest.a:
	cd cpputest; autoreconf . -i && ./configure && make tdd
