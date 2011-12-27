#include <iso646.h>  // or, and, not
#include "stupid/ass.h"

#include "eval.h"

stack arg_st(void) {
    stack st = stack_new();
    st = stack_push(st, element_float_new(3.14));
    st = stack_push(st, element_float_new(10));
    st = stack_push(st, element_float_new(0.1));
    return st;
}

//
// eval_builtin
//

void test_eval_builtin__stack_clear(stack st) {
    st = eval_builtin("built-in.stack.clear", st);
    ass(stack_eq(st, stack_new())); 
}

void test_eval_builtin__stack_swap(stack st) {
    st = eval_builtin("built-in.stack.swap", st);
    ass(element_eq(stack_top(st), element_float_new(10)));
    ass(element_eq(stack_peek(st, 1), element_float_new(0.1)));
}

void test_eval_builtin__stack_pop(stack st) {
    st = eval_builtin("built-in.stack.pop", st);
    ass(stack_size(st) == 2);
    ass(element_eq(stack_top(st), element_float_new(10)));
    ass(element_eq(stack_bottom(st), element_float_new(3.14)));
}

void test_eval_builtin__float_sum(stack st) {
    st = eval_builtin("built-in.float.+", st);
    ass(stack_size(st) == 2);
    ass(element_float_value(stack_top(st)) == 10 + 0.1);
}

void test_eval_builtin__float_pow(stack st) {
    st = eval_builtin("built-in.float.^", st);
    ass(stack_size(st) == 2);
    ass(element_float_value(stack_top(st)) == pow(10, 0.1));
}

void test_eval_builtin__float_mul(stack st) {
    st = eval_builtin("built-in.float.*", st);
    ass(stack_size(st) == 2);
    ass(element_float_value(stack_top(st)) == 10 * 0.1);
}

void test_eval_builtin__float_div(stack st) {
    st = eval_builtin("built-in.float./", st);
    ass(stack_size(st) == 2);
    ass(element_float_value(stack_top(st)) == 10 / 0.1);
}

void test_eval_builtin__float_gt(stack st) {
    st = eval_builtin("built-in.float.>", st);
    ass(stack_size(st) == 2);
    ass(element_float_value(stack_top(st)) == 10 > 0.1);
}

//
// eval_token
//

void test_eval_token__index_0(stack st) {
    st = eval_token(token_parse("[0]"), "", st);
    ass(stack_size(st) == 4);
    ass(element_eq(stack_top(st), stack_peek(st, 1)));
    ass(element_eq(stack_top(st), element_float_new(0.1)));
}

void test_eval_token__index_1(stack st) {
    st = eval_token(token_parse("[1]"), "", st);
    ass(stack_size(st) == 4);
    ass(element_eq(stack_top(st), stack_peek(st, 2)));
    ass(element_eq(stack_top(st), element_float_new(10)));
}

void test_eval_token__index_2(stack st) {
    st = eval_token(token_parse("[2]"), "", st);
    ass(stack_size(st) == 4);
    ass(element_eq(stack_top(st), stack_peek(st, 3)));
    ass(element_eq(stack_top(st), element_float_new(3.14)));
}

void test_eval_token__float_0(stack st) {
    st = eval_token(token_parse("0"), "", st);
    ass(stack_size(st) == 4);
    ass(element_float_value(stack_top(st)) == 0);
}

void test_eval_token__float_1(stack st) {
    st = eval_token(token_parse("11.11"), "", st);
    ass(stack_size(st) == 4);
    ass(element_float_value(stack_top(st)) == 11.11);
}

void test_eval_token__str_0(stack st) {
    st = eval_token(token_parse("\"hello, world\""), "", st);
    ass(stack_size(st) == 4);
    ass(str_eq(element_str_value(stack_top(st)), "hello, world"));
}

void test_eval_token__str_1(stack st) {
    st = eval_token(token_parse("\"11.11\""), "", st);
    ass(stack_size(st) == 4);
    ass(str_eq(element_str_value(stack_top(st)), "11.11"));
}

void test_eval_token__builtin_swap(stack st) {
    st = eval_token(token_parse("built-in.stack.swap"), "", st);
    ass(stack_size(st) == 3);
    ass(element_float_value(stack_top(st)) == 10);
    ass(element_float_value(stack_peek(st, 1)) == 0.1);
}

void test_eval_token__builtin_mul(stack st) {
    st = eval_token(token_parse("built-in.float.*"), "", st);
    ass(stack_size(st) == 2);
    ass(element_float_value(stack_top(st)) == 10 * 0.1);
    ass(element_float_value(stack_peek(st, 1)) == 3.14);
}

void test_eval_token__def(stack st) {
    st = eval_token(token_parse("s"), " s: built-in.stack.swap .", st);
    ass(stack_size(st) == 3);
    ass(element_float_value(stack_top(st)) == 10);
    ass(element_float_value(stack_peek(st, 1)) == 0.1);
}

//
// eval
//

void test_eval__empty(stack st) {
    stack st_new = eval("", "", st);
    ass(stack_eq(st_new, st));
}

void test_eval__empty_whitespace(stack st) {
    stack st_new = eval("  ###\n   \t\r", " \r\n \t", st);
    ass(stack_eq(st_new, st));
}

void test_eval__return(stack st) {
    stack st_new = eval(" . foo bar ", "", st);
    ass(stack_eq(st_new, st));
}

void test_eval__0_then(stack st) {
    st = eval("0 -> 3.14 . 2.72", "", st);
    ass(stack_size(st) == 4);
    ass(element_float_value(stack_top(st)) == 2.72);
}

void test_eval__0_then_empty(stack st) {
    st = eval("0 -> . 2.72", "", st);
    ass(stack_size(st) == 4);
    ass(element_float_value(stack_top(st)) == 2.72);
}

void test_eval__1_then(stack st) {
    st = eval("1 -> 3.14 . 2.72", "", st);
    ass(stack_size(st) == 4);
    ass(element_float_value(stack_top(st)) == 3.14);
}

void test_eval__1_then_empty(stack st) {
    st = eval("1 -> 3.14 .", "", st);
    ass(stack_size(st) == 4);
    ass(element_float_value(stack_top(st)) == 3.14);
}


int main() {
    printf("================ start ================\n");

    test_eval_builtin__stack_clear(arg_st());
    test_eval_builtin__stack_swap(arg_st());
    test_eval_builtin__stack_pop(arg_st());
    test_eval_builtin__float_sum(arg_st());
    test_eval_builtin__float_pow(arg_st());
    test_eval_builtin__float_mul(arg_st());
    test_eval_builtin__float_div(arg_st());
    test_eval_builtin__float_gt(arg_st());

    test_eval_token__index_0(arg_st());
    test_eval_token__index_1(arg_st());
    test_eval_token__index_2(arg_st());
    test_eval_token__float_0(arg_st());
    test_eval_token__float_1(arg_st());
    test_eval_token__str_0(arg_st());
    test_eval_token__builtin_swap(arg_st());
    test_eval_token__builtin_mul(arg_st());
    test_eval_token__def(arg_st());
    //test_eval_token__context

    test_eval__empty(arg_st());
    test_eval__empty_whitespace(arg_st());
    test_eval__return(arg_st());
    test_eval__0_then(arg_st());
    test_eval__0_then_empty(arg_st());
    test_eval__1_then(arg_st());
    test_eval__1_then_empty(arg_st());
    //test_eval__builtin
    //test_eval__def
    //test_eval__context

    printf("================= end =================\n");
}    
