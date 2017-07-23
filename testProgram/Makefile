defaul/: test_memstats

test_memstats: test_memstats.o
	gcc -o test_memstats test_memstats.o

test_memstats.o: test_memstats.c
	gcc -c test_memstats.c

clean:
	rm test_memstats *.o
