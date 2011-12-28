#include <stdbool.h>  // true, flase
#include <iso646.h>  // or, and, not
#include <math.h>  // pow

#include "stupid/str.h"
#include "stack.h"
#include "token.h"

stack eval(char* source, char* context, stack st);

stack eval_builtin(char* symbol, char* context, stack st) {
    if (str_eq(symbol, "built-in.quit")) {
        exit(0);
    } else if(str_eq(symbol, "built-in.eval")) {
        char* tmp = str_auto(element_str_value(stack_top(st)));
        st = stack_pop(st);
        st = eval(tmp, context, st);
    } else if(str_eq(symbol, "built-in.meta")) {
        st = stack_push(st, element_str_new(element_meta(stack_top(st))));
    } else if(str_eq(symbol, "built-in.stack.clear")) { 
        stack_del(st);
        st = stack_new();
    } else if(str_eq(symbol, "built-in.stack.pop")) {
        st = stack_pop(st);
    } else if(str_eq(symbol, "built-in.stack.swap")) {
        element el0 = element_copy(stack_top(st));
        st = stack_pop(st);
        element el1 = element_copy(stack_top(st));
        st = stack_pop(st);
        st = stack_push(st, el0);
        st = stack_push(st, el1);
    } else if(str_eq(symbol, "built-in.str.print")) {
        printf("%s\n", element_str_value(stack_top(st)));
        st = stack_pop(st);
    } else if(str_eq(symbol, "built-in.str.input")) {
        // FIXME, str_input_auto does not work here
        st = stack_push(st, element_str_new(str_input_new()));
    } else if(str_eq(symbol, "built-in.str.concat")) {
        char* tmp = str_cat_auto(element_str_value(stack_peek(st, 1)),
                                 element_str_value(stack_peek(st, 0)));
        st = stack_pop(st);
        st = stack_pop(st);
        st = stack_push(st, element_str_new(tmp));
    } else if(str_eq(symbol, "built-in.float.+")) { 
        // This reading after popping is wrong...
        element el0 = stack_top(st);
        st = stack_pop(st);
        element el1 = stack_top(st);
        st = stack_pop(st);
        element el_new = element_float_new(el1._data._float + el0._data._float);
        st = stack_push(st, el_new);
    } else if(str_eq(symbol, "built-in.float.^")) {
        element el0 = stack_top(st);
        st = stack_pop(st);
        element el1 = stack_top(st);
        st = stack_pop(st);
        element el_new = element_float_new(pow(el1._data._float, el0._data._float));
        st = stack_push(st, el_new);
    } else if(str_eq(symbol, "built-in.float.*")) {
        element el0 = stack_top(st);
        st = stack_pop(st);
        element el1 = stack_top(st);
        st = stack_pop(st);
        element el_new = element_float_new(el1._data._float * el0._data._float);
        st = stack_push(st, el_new);
    } else if(str_eq(symbol, "built-in.float./")) {
        element el0 = stack_top(st);
        st = stack_pop(st);
        element el1 = stack_top(st);
        st = stack_pop(st);
        element el_new = element_float_new(el1._data._float / el0._data._float);
        st = stack_push(st, el_new);
    } else if(str_eq(symbol, "built-in.float.>")) {
        element el0 = stack_top(st);
        st = stack_pop(st);
        element el1 = stack_top(st);
        st = stack_pop(st);
        element el_new = element_float_new(el1._data._float > el0._data._float);
        st = stack_push(st, el_new);
    } else {
        printf("built-in.what???\n");
    }
    return st;
}

stack eval_token(token tk, char* context, stack st) {
    if (token_is_index(tk)) {
        st = stack_push(st, element_copy(stack_peek(st, token_index_value(tk))));
    } else if (token_is_float(tk)) {
        st = stack_push(st, element_float_new(token_float_value(tk)));
    } else if (token_is_str(tk)) {
        st = stack_push(st, element_str_new(token_str_value(tk)));
    } else if (token_is_symbol(tk)) {
        if (str_startswith(token_symbol_value(tk), "built-in.")) {
            st = eval_builtin(token_symbol_value(tk), context, st);
        } else {
            token tkdef = token_find_def(context, token_symbol_value(tk));
            if (not token_is_empty(tkdef)) {
                st = eval(token_rest(tkdef), context, st);
                token_del(tkdef);
            } else {
                printf("%s???\n", token_symbol_value(tk));
            }
        }
    }
    return st;
}

stack eval(char* source, char* context, stack st) {
    token tk = token_parse(source);
    while (true) {
        if (token_is_empty(tk)) break;
        if (token_is_symbol(tk)) {
            if (str_eq(token_symbol_value(tk), ".")) break;
            if (str_eq(token_symbol_value(tk), "->")) {
                if (element_float_value(stack_top(st)) == 0) {
                    st = stack_pop(st);
                    token_del(tk);
                    tk = token_find_symbol(token_rest(tk), ".");
                    token_del(tk);
                    tk = token_parse(token_rest(tk));
                    if (token_is_empty(tk)) break;
                    else continue;
                } else {
                    st = stack_pop(st);
                    token_del(tk);
                    tk = token_parse(token_rest(tk));
                    continue;
                }
            }
        }
        st = eval_token(tk, context, st);
        token_del(tk);
        tk = token_parse(token_rest(tk));
    }
    token_del(tk);
    return st;
}

