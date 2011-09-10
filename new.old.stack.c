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

void stack_push(se_t value) {
    bottom_of_stack = realloc(bottom_of_stack, ++stack_size*sizeof(se_t));
    *top_of_stack = value;
}

se_t stack_pop(void) {
    se_t pop = *top_of_stack;
    bottom_of_stack = realloc(bottom_of_stack, --stack_size*sizeof(se_t));
    return pop;
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
        else if(strcmp(buffer,"x") == 0) stack_pop();
        else if(strcmp(buffer,"+") == 0) stack_infix(+);
        else if(strcmp(buffer,"-") == 0) stack_infix(-);
        else if(strcmp(buffer,"*") == 0) stack_infix(*);
        else if(strcmp(buffer,"/") == 0) stack_infix(/);
        else if(strcmp(buffer,"or") == 0) stack_infix(||);
        else if(strcmp(buffer,"and") == 0) stack_infix(&&);
        else if(strcmp(buffer,"min") == 0) stack_prefix(fmin);
        else if(strcmp(buffer,"max") == 0) stack_prefix(fmax);
        else if(strcmp(buffer,"pi") == 0) stack_push((se_t)M_PI);
        else if(strcmp(buffer,"e") == 0) stack_push((se_t)M_E);
        else if(strcmp(buffer,"^") == 0) stack_prefix(pow);
        tt("pow", stack_prefix(pow));
        else printf("? \n");
    }
}
    
    















