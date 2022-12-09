default: test0 test1

test0: 
	gcc migratory0.c -o test_0 -lpthread

test1: 
	gcc producer_consumer0.c -o test_1 -lpthread

clean: 
	rm -f test_*