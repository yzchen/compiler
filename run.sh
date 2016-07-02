./bin/parser ./test/heapsort.c1 2> './test/heapsort.ll'

llc ./test/heapsort.ll  -o ./test/heapsort.s

clang++ ./test/heapsort.s -c -o ./test/heapsort.o

clang++ -o ./test/heapsort ./test/heapsort.o ./test/libprint.o

echo "test case. heapsort : "
./test/heapsort

