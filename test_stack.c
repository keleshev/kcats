#include "stack.h"

#include "ass.h"


int main() {
    printf("===========================================\n");

    // stack_new
    stack st = stack_new();
    ass_eq(stack_size(st), 0);

    // element_float_new
    element el = element_float_new(3.14);
    ass(element_eq(el, element_float_new(3.14)));
    ass(!element_eq(el, element_float_new(1)));

    // stack_push
    st = stack_push(st, el);
    ass_eq(stack_size(st), 1);
    ass(element_eq(stack_top(st), el));
    ass(element_eq(stack_bottom(st), el));

    // stack_push
    element e2 = element_float_new(2.71);
    st = stack_push(st, e2);
    ass_eq(stack_size(st), 2);
    ass(element_eq(stack_top(st), e2));
    ass(element_eq(stack_bottom(st), el));

    stack st2 = stack_new();
    st2 = stack_push(st2, element_int_new(1));
    st2 = stack_push(st2, element_int_new(2));
    st2 = stack_push(st2, element_int_new(3));
    element elst = element_stack_new(st2);
    st = stack_push(st, elst);
    ass_eq(stack_size(st), 3);
    stack_print(st);   printf("\n");

    stack stcp = stack_copy(st2);
    st = stack_push(st, element_stack_new(stcp));

    stack_print(st);
    st = stack_pop(st);
    st = stack_pop(st);

    // stack_peek
    ass(element_eq(stack_peek(st, 0), e2));
    ass(element_eq(stack_peek(st, 1), el));

    // stack_pop
    st = stack_pop(st);
    ass_eq(stack_size(st), 1);
    ass(element_eq(stack_top(st), el));
    ass(element_eq(stack_bottom(st), el));

    // stack_pop
    st = stack_pop(st);
    ass_eq(stack_size(st), 0);

    printf("==================== ok ===================\n");
}    
