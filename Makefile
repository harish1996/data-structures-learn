stack_DEPS= stack.o
s_queue_DEPS= s_queue.o stack.o
input_DEPS= input.o
min_heap_DEPS= min_heap.o
min_max_heap_DEPS= min_max_heap.o
llist_DEPS= llist.o

all : stack.a input.a s_queue.a min_heap.a min_max_heap.a llist.a

stack.a : ${stack_DEPS}
	ar cr $@ $^

input.a : ${input_DEPS}
	ar cr $@ $^

s_queue.a : ${s_queue_DEPS}
	ar cr $@ $^

min_max_heap.a: ${min_max_heap_DEPS}
	ar cr $@ $^

llist.a: ${llist_DEPS}
	ar cr $@ $^

min_heap.a: ${min_heap_DEPS}
	ar cr $@ $^

%.o : %.c
	gcc $^ -c -o $@ -g3 
