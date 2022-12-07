default: test0

test0: 
	gcc migratory0.c -o test_0 -lpthread

clean: 
	rm -f test_*