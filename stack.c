#include <stdio.h>
#include <stdlib.h>
#include <string.h>            
#include <math.h>

typedef double se_t; // stack element type

int stack_size = 0;
se_t *bottom_of_stack = NULL;
#define top_of_stack (bottom_of_stack + (stack_size - 1))

#define stack_infix(op) do {se_t _t=stack_pop(); \
                            stack_push(stack_pop() op _t);} while(0)
#define stack_prefix(op) do {se_t _t=stack_pop(); \
                            stack_push(op(stack_pop(), _t));} while(0)
#define stack_prefix_1(op) stack_push(op(stack_pop()))

void stack_push(se_t value) {
    bottom_of_stack = realloc(bottom_of_stack, ++stack_size*sizeof(se_t));
    *top_of_stack = value;
}

se_t stack_pop(void) {
    se_t pop = *top_of_stack;
    bottom_of_stack = realloc(bottom_of_stack, --stack_size*sizeof(se_t));
    return pop;
}

se_t stack_peek(void) { return *top_of_stack; }

void stack_clear(void) {
    bottom_of_stack = realloc(bottom_of_stack, 0);
    stack_size = 0;
    printf("[%p]", bottom_of_stack);
}

void stack_print() {
    if (bottom_of_stack != NULL) 
        for(se_t *i = bottom_of_stack;
                 i <= top_of_stack;
                 i++) { 
            printf("%g ", (double)*i);
        }
}

#define tt(s,e) else if(strcmp(buffer,s) == 0) e
int main() {
    se_t number;
    char buffer[20];
    while(1) {
        stack_print();
        printf("> ");
        scanf("%s", buffer);
        if(sscanf(buffer, "%lf", &number) == 1)
            stack_push(number);
        else if(strcmp(buffer,"") == 0) continue;
        else if(strcmp(buffer,"q") == 0) return 0;
        tt("clr",  stack_clear());
        tt("dup",  stack_push(stack_peek()));
        tt("x",    stack_pop());
        tt("+",    stack_infix(+));
        tt("-",    stack_infix(-));
        tt("*",    stack_infix(*));
        tt("/",    stack_infix(/));
        tt("or",   stack_infix(||));
        tt("and",  stack_infix(&&));
        tt("min",  stack_prefix(fmin));
        tt("max",  stack_prefix(fmax));
        tt("pi",   stack_push((se_t)M_PI));
        tt("e",    stack_push((se_t)M_E));
        tt("^",    stack_prefix(pow));
        tt("abs",  stack_prefix_1(abs));
        else printf("? \n");
    }
}
    
    















