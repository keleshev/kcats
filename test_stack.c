#include <iso646.h>  // or, and, not
#include "stupid/ass.h"

#include "stack.h"


stack arg_st(void) {
    stack inner = stack_new();
    inner = stack_push(inner, element_float_new(1.1));
    inner = stack_push(inner, element_float_new(2e2));
    inner = stack_push(inner, element_float_new(3.33));

    stack st = stack_new();
    st = stack_push(st, element_float_new(3.14));
    st = stack_push(st, element_int_new(30));
    st = stack_push(st, element_str_new("foo"));
    st = stack_push(st, element_stack_new(inner));
    st = stack_push(st, element_float_new(4.14));
    st = stack_push(st, element_float_new(5.14));
    return st;
}

stack arg_st2(void) {
    stack st = stack_new();
    st = stack_push(st, element_int_new(100));
    st = stack_push(st, element_str_new("bar"));
    st = stack_push(st, element_float_new(14.14));
    st = stack_push(st, element_float_new(15.14));
    st = stack_push(st, element_float_new(24.14));
    st = stack_push(st, element_float_new(35.14));
    return st;
}

//
// element_*
//

void test_element_eq__floats(void) {
    element epi = element_float_new(3.14);
    ass(element_eq(epi, epi));
    ass(element_eq(epi, element_float_new(3.14)));
    ass(element_eq(element_float_new(3.14), element_float_new(3.14)));
    
    ass(not element_eq(epi, element_float_new(2.72)));
    ass(not element_eq(element_int_new(0), element_float_new(0)));
}

void test_element_eq__int(void) {
    element e30 = element_int_new(30);
    ass(element_eq(e30, e30));
    ass(element_eq(e30, element_int_new(30)));
    ass(element_eq(element_int_new(30), element_int_new(30)));
    
    ass(not element_eq(e30, element_int_new(20)));
    ass(not element_eq(element_int_new(10), element_float_new(10)));
}

void test_element_eq__str(void) {
    element efoo = element_str_new("foo");
    ass(element_eq(efoo, efoo));
    ass(element_eq(efoo, element_str_new("foo")));
    ass(element_eq(element_str_new("foo"), element_str_new("foo")));

    element ebar = element_str_new("bar");
    ass(not element_eq(efoo, ebar));
    ass(not element_eq(element_str_new("\0"), element_int_new(0)));
}

void test_element_eq__stack(stack st, stack st2) {
    element est = element_stack_new(st);
    ass(element_eq(est, est));
    ass(element_eq(est, element_stack_new(st)));
    ass(element_eq(element_stack_new(st), element_stack_new(st)));
    
    element est2 = element_stack_new(st2);
    ass(not element_eq(est, est2));
    ass(not element_eq(est, element_str_new("foo")));

    ass(element_eq(element_stack_new(stack_new()), element_stack_new(stack_new())));
}
 
//
// stack_*
//

void test_stack_new(void) {
    stack st = stack_new();
    ass(stack_size(st) == 0);
}

void test_stack_push(stack st) {
    stack stk = stack_new();

    stk = stack_push(stk, element_float_new(3.14));
    ass(stack_size(stk) == 1);
    ass(element_eq(stack_top(stk), element_float_new(3.14)));

    stk = stack_push(stk, element_int_new(3));
    ass(stack_size(stk) == 2);
    ass(element_eq(stack_top(stk), element_int_new(3)));
    ass(element_eq(stack_bottom(stk), element_float_new(3.14)));

    stk = stack_push(stk, element_str_new("foo"));
    ass(stack_size(stk) == 3);
    ass(element_eq(stack_top(stk), element_str_new("foo")));
    ass(element_eq(stack_peek(stk, 1), element_int_new(3)));
    ass(element_eq(stack_bottom(stk), element_float_new(3.14)));

    stk = stack_push(stk, element_stack_new(st));
    ass(stack_size(stk) == 4);
    ass(element_eq(stack_top(stk), element_stack_new(st)));
    ass(element_eq(stack_peek(stk, 1), element_str_new("foo")));
    ass(element_eq(stack_peek(stk, 2), element_int_new(3)));
    ass(element_eq(stack_bottom(stk), element_float_new(3.14)));
}

void test_stack_pop(stack st) {
    ass(stack_size(st) == 6);
    st = stack_pop(st);
    ass(stack_size(st) == 5);
    st = stack_pop(st);
    ass(stack_size(st) == 4);
    st = stack_pop(st);
    ass(stack_size(st) == 3);
    st = stack_pop(st);
    ass(stack_size(st) == 2);
    st = stack_pop(st);
    ass(stack_size(st) == 1);
    st = stack_pop(st);
    ass(stack_size(st) == 0);
}

void test_stack_peek(stack st) {
    // st = < 3.14 30 "foo" <inner> 4.14 5.14 >
    ass(element_eq(stack_peek(st, 0), stack_top(st)));
    ass(element_eq(stack_peek(st, 0), element_float_new(5.14)));
    ass(element_eq(stack_peek(st, 1), element_float_new(4.14)));
    ass(element_eq(stack_peek(st, 3), element_str_new("foo")));
    ass(element_eq(stack_peek(st, 4), element_int_new(30)));
    ass(element_eq(stack_peek(st, 5), element_float_new(3.14)));
    ass(element_eq(stack_peek(st, 5), stack_bottom(st)));
}

void test_stack_eq(stack st, stack st2) {
    ass(stack_eq(st, st));
    ass(stack_eq(st2, st2));
    ass(not stack_eq(st, st2));
    ass(stack_eq(stack_new(), stack_new()));
}

int main() {
    printf("================ start ================\n");

    test_element_eq__floats();
    test_element_eq__int();
    test_element_eq__str();
    test_element_eq__stack(arg_st(), arg_st2());

    test_stack_new();
    test_stack_push(arg_st());
    test_stack_pop(arg_st());
    test_stack_peek(arg_st());
    test_stack_eq(arg_st(), arg_st2());

    printf("================= end =================\n");
}    
