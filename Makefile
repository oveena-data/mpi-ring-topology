numbers1: numbers1.c
	mpicc -o numbers1 numbers1.c

numbers2: numbers2.c
	mpicc -o numbers2 numbers2.c

run1: numbers1
	mpiexec -n 5 ./numbers1

run2: numbers2
	mpiexec -n 5 ./numbers2

clean:
	rm -f numbers1 numbers2
