#include <stdio.h>
#include <stdlib.h>
#include <string.h>            
#include <math.h>
#include "stack.c"
#include "code.c"

#define YELLOW  "\e[1;33m"
#define RED     "\e[1;31m"
#define DEFAULT "\e[0m"

void eval(char s[]) {

}

#define tt(s,e) else if(strcmp(buffer,s) == 0) e
int main() {
    se_t number;
    unsigned int index;
    char buffer[20];
    while(1) {
        stack_print();
        printf(YELLOW "> " DEFAULT); // ➤
        scanf("%s", buffer);
        if(sscanf(buffer, "%lf", &number) == 1)
            stack_push(number);
        else if(sscanf(buffer, "[%u]", &index) == 1)
            stack_push(stack_read(index));
        else if(strcmp(buffer,"") == 0) continue;
        else if(strcmp(buffer,"q") == 0) return 0;
        tt("c",  stack_clear());
        tt("dup",  stack_push(stack_peek()));
        tt("swp",  stack_swap());
        tt("x",    stack_pop());
        tt("+",    stack_infix(+));
        tt("-",    stack_infix(-));
        tt("*",    stack_infix(*));
        tt("/",    stack_infix(/));
        tt("<",    stack_infix(<));
        tt("!",    stack_prefix_1(!));
        tt("<=",   stack_infix(<=));
        tt(">",    stack_infix(>));
        tt(">=",   stack_infix(>=));
        tt("==",   stack_infix(==));
        //tt("!=",   stack_infix(!=));
        tt("or",   stack_infix(||));
        tt("and",  stack_infix(&&));
        tt("min",  stack_prefix(fmin));
        tt("max",  stack_prefix(fmax));
        tt("pi",   stack_push((se_t)M_PI));
        tt("e",    stack_push((se_t)M_E));
        tt("^",    stack_prefix(pow));
        tt("abs",  stack_prefix_1(abs));
        else printf(RED "%s? \n" DEFAULT, buffer);
    }
}
    
    















