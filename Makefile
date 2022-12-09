default: test0 test1 test2 test3 test4 test5

test0: 
	gcc migratory0.c -o test_0 -lpthread

test1: 
	gcc producer_consumer0.c -o test_1 -lpthread

test2: 
	gcc migratory1.c -o test_2 -lpthread

test3: 
	gcc migratory2.c -o test_3 -lpthread

test4: 
	gcc edge_case0.c -o test_4 -lpthread

test5: 
	gcc edge_case1.c -o test_5 -lpthread

clean: 
	rm -f test_*