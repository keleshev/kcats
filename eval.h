#include <stdbool.h>  // true, flase
#include <iso646.h>  // or, and, not

#include "stupid/str.h"
#include "stack.h"
#include "token.h"

stack eval(char* source, char* context, stack st);

stack eval_token(token tk, char* context, stack st) {
    if (tk.is_index) {
        //(sscanf(w, "[%u]", &index) == 1) { 
        st = stack_push(st, stack_peek(st, tk.index));
    } else if (tk.is_float) {
        //sscanf(w, "%lf", &number) == 1) {
        st = stack_push(st, element_float_new(tk.float));
    } else if (tk.is_str) {
        st = stack_push(st, element_str_new(tk.str));
    } else if (tk.is_symbol) {
    } else if(str_eq(w, "q")) {
        exit(0);
    //} else if(str_eq(w, "#")) {
       // ;
    //} else if(str_eq(w, ":")) {
        //;
    //} else if(str_eq(w, "then")) { 
        //;
    } else if(str_eq(w, "context")) {
        printf("%s", context);
    //} else if(str_eq(w, "return")) {
        //return false;
    //} else if(str_eq(w, ".")) {
        //return false;
    //} else if(str_eq(w, "log")) {
        //stack_print(st);
    //} else if(str_eq(w, "top")) {
    //    printf("<<<%g>>>", stack_top(st)._data._float);
    } else if(str_eq(w, "c")) { 
        stack_del(st);
        st = stack_new();
    } else if(str_eq(w, "swp")) {
        element el0 = stack_top(st);
        st = stack_pop(st);
        element el1 = stack_top(st);
        st = stack_pop(st);
        st = stack_push(st, element_float_new(el0._data._float));
        st = stack_push(st, element_float_new(el1._data._float));
    } else if(str_eq(w, "x")) {
        st = stack_pop(st);
    } else if(str_eq(w, "+")) { 
        element el0 = stack_top(st);
        st = stack_pop(st);
        element el1 = stack_top(st);
        st = stack_pop(st);
        element el_new = element_float_new(el1._data._float + el0._data._float);
        st = stack_push(st, el_new);
    } else if(str_eq(w, "^")) {
        element el0 = stack_top(st);
        st = stack_pop(st);
        element el1 = stack_top(st);
        st = stack_pop(st);
        element el_new = element_float_new(pow(el1._data._float, el0._data._float));
        st = stack_push(st, el_new);
    } else if(str_eq(w, "*")) {
        element el0 = stack_top(st);
        st = stack_pop(st);
        element el1 = stack_top(st);
        st = stack_pop(st);
        element el_new = element_float_new(el1._data._float * el0._data._float);
        st = stack_push(st, el_new);
    } else if(str_eq(w, "/")) {
        element el0 = stack_top(st);
        st = stack_pop(st);
        element el1 = stack_top(st);
        st = stack_pop(st);
        element el_new = element_float_new(el1._data._float / el0._data._float);
        st = stack_push(st, el_new);
    } else if(str_eq(w, ">")) {
        element el0 = stack_top(st);
        st = stack_pop(st);
        element el1 = stack_top(st);
        st = stack_pop(st);
        element el_new = element_float_new(el1._data._float > el0._data._float);
        st = stack_push(st, el_new);
    } else if(p = find_def(context, w), p != NULL) {
        eval(p, context, st);
    } else {
        err("%s? \n", w);    
    }
    //return true;
    return st;
}

stack eval(char* source, char* context, stack st) {
    
    token t = token_next(source);
    while (true) {
        if (str_eq(t.next, "") or str_is_space(t.next) or 
            str_eq(t.next, ".") or str_eq(t.next, "return")) { 
            //free(t.next);
            break;
        } else if ((str_eq(t.next, ":") or str_eq(t.next, "then")) and 
                                        stack_top(st)._data._float==0) {
            st = stack_pop(st);
            free(t.next);
            t = token_skip_until_either(t.rest, ".", "return");
            continue;
        } else if (is_def(t.next)) {
            //err("Definitions in REPL are not available yet. \n");
        } else {   
            st = eval_token(t.next, context, st);
        }
        free(t.next);
        t = token_next(t.rest);
    }
    free(t.next);
    return st;
}
