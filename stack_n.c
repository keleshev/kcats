#include "ass.h"


typedef struct {
    //size_t size;
    element* top;
    element* bottom;
} stack;

typedef struct {
    type* type;
    void* data;
} element;  

typedef struct {
    type* parrent;
    char* name;
} type;



stack stack_auto() {
    stack s;
    s.bottom = NULL;
    s.top = NULL;
    return s;
}

size_t stack_size(stack s) {
    if (s.top == NULL && s.bottom == NULL) return 0;
    ass(s.top != NULL);
    ass(s.bottom != NULL);
    return s.top - s.bottom + 1;
}

element stack_top(stack s) {
    return s.*top;
}

stack stack_push(stack s, element e) {
    size_t size_new = stack_size(s) + 1;
    s.bottom = realloc(s.bottom, size_new * sizeof(e));
    ass(s.bottom != NULL);
    s.top = s.bottom - 1 + size_new;
    ass(s.top == s.bottom ? size_new == 1 : true);
    s.*top = e;
    ass(s.top->type != NULL);
    ass(s.top->data != NULL);
    return s; 
}





int main() {

    type cstr = { .parrent=NULL, .name="cstr" };
    type cint = { .parrent=NULL, .name="cint" };

    element e1 = { .type=&cstr, .data="hello,world!" };
    element e2 = { .type=&cint, .data="hello,world!" };

    stack s = stack_auto();

    s = stack_push(s, e1);
    s = stack_push(s, e2);

    ass(stack_size(s) == 2);






}    
