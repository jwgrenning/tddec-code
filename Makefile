# Prerequisites:
#	CppUTest built with extensions
#	CPPUTEST_HOME defined
	
all: 
	make -i -C code
	make -i -C code-t0
	make -i -C code-t1
	make -i -C code-t2
	make -i -C code-t3

clean:
	make -i -C code clean
	make -i -C code-t0 clean
	make -i -C code-t1 clean
	make -i -C code-t2 clean
	make -i -C code-t3 clean

