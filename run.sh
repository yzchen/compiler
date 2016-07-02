g++ ./test/libprint.c -S -o ./test/libprint.s

sed -i 's/_Z8printintv/printint/g' ./test/libprint.s
sed -i 's/_Z10printfloatv/printfloat/g' ./test/libprint.s
sed -i 's/_Z6printai/printa/g' ./test/libprint.s

clang++ -c -o ./test/libprint.o ./test/libprint.s

# ./bin/parser ./test/t1.c1
#  2> './test/t1.ll'

# llc ./test/t1.ll  -o ./test/t1.s

# clang++ ./test/t1.s -c -o ./test/t1.o

# clang++ -o ./test/t1 ./test/t1.o ./test/libprint.o

# ./test/t1


./bin/parser ./test/heapsort.c1 2> './test/heapsort.ll'

llc ./test/heapsort.ll  -o ./test/heapsort.s

clang++ ./test/heapsort.s -c -o ./test/heapsort.o

clang++ -o ./test/heapsort ./test/heapsort.o ./test/libprint.o

echo "heapsort : "
./test/heapsort

./bin/parser ./test/linklist.c1  2> './test/linklist.ll'

llc ./test/linklist.ll  -o ./test/linklist.s

clang++ ./test/linklist.s -c -o ./test/linklist.o

clang++ -o ./test/linklist ./test/linklist.o ./test/libprint.o

echo "linklist : "
./test/linklist
