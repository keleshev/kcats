#include <stdio.h>
#include <stdlib.h>

//typedef unsigned long long int se_t;  // stack element type
typedef float se_t;

int stack_size = 0;
se_t *bottom_of_stack = NULL;
#define top_of_stack (bottom_of_stack + (stack_size - 1))

#define stack_infix(op) stack_push(stack_pop() op stack_pop())

#define do_times(x) for(int _i=0; _i<x; _i++)

#define push(v) stack_push(v)
void stack_push(se_t v) {
    bottom_of_stack = realloc(bottom_of_stack, 
                              ++stack_size);// * sizeof(se_t));
    *top_of_stack = v;
}

#define pop() stack_pop() 
se_t stack_pop(void) {
    se_t pop = *top_of_stack;
    bottom_of_stack = realloc(bottom_of_stack,
                              --stack_size);
    return pop;
}
    
#define pr() stack_print() 
void stack_print() {
    printf("stack(%d): \n", (int)stack_size);
    for(se_t *i = bottom_of_stack;
             i <= top_of_stack;
             i++) { //+= sizeof(se_t))  
        printf("%p: %f \n", (void*)i, (float)*i);
    }
}

int main() {
    push(123.5); 
    push(456);
    push(2343.234);
    pr();
    stack_infix(+);
    pr();
    pop();
    pr();

}
    
    















