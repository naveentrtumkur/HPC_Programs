flags = -O3 -lrt
DEPS = simple_amr.h simple_amr.c
5441: ${DEPS}
	gcc -o 5441 simple_amr.c ${flags}

.PHONY : clean
clean :
	 rm -f 5441
