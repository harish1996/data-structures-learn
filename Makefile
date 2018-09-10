stack_DEPS= stack.o
s_queue_DEPS= s_queue.o stack.o
input_DEPS= input.o

all : stack.a input.a s_queue.a

stack.a : ${stack_DEPS}
	ar cr $@ $^

input.a : ${input_DEPS}
	ar cr $@ $^

s_queue.a : ${s_queue_DEPS}
	ar cr $@ $^

%.o : %.c
	gcc $^ -c -o $@ -g3 
