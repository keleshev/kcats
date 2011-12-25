#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <ctype.h>
#include <math.h>
#include <iso646.h>

#include "stupid/colors.h"
#include "stupid/str.h"
#include "stack.h"

#define err(...) do { printf(RED); printf(__VA_ARGS__); printf(DEFAULT); } while (0)

stack eval(char* sentence, char* context, stack st);

    
    
char* find_def(char *context, char *word) {
    char def[strlen(word) + 3];  // account for '\n', ':' and '\0'
    sprintf(def, "\n%s:", word);
    char *r = strstr(context, def);
    if(r == NULL) return NULL;
    else return r + strlen(def);
}       

bool is_def(char w[]) {
    int l = strlen(w);     
    return ((l>1) and w[l-1]==':');
}

typedef struct {
    char* next;
    char* rest;
} token;

token token_next(char* s) {
    unsigned b = 0;  // begin
    unsigned e = 0;  // end
    while(isspace(s[b]) and s[b]) b++;
    e = b;
    while(!isspace(s[e]) and s[e]) e++;
    token t;
    t.next = str_sub_new(s, b, e);
    t.rest = &s[e];
    return t;
}

token token_skip_until_either(char* s, char* ei1, char* ei2) {
    token t = token_next(s);
    while(!str_eq(t.next, ei1) and !str_eq(t.next, ei2)) {
        free(t.next);
        t = token_next(t.rest);    
    }
    free(t.next);
    t = token_next(t.rest); 
    return t;
}


stack eval_word(char w[], char context[], stack st) {
    double number;
    char *p; 
    unsigned index;                                           
    if(sscanf(w, "%lf", &number) == 1) {
        st = stack_push(st, element_float_new(number));
    } else if(sscanf(w, "[%u]", &index) == 1) { 
        st = stack_push(st, stack_peek(st, index));
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

stack eval(char* sentence, char* context, stack st) {
    
    token t = token_next(sentence);
    while (true) {
        //printf("<%s|%s>", t.next, t.rest);
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
            err("Definitions in REPL are not available yet. \n");
        } else {   
            st = eval_word(t.next, context, st);
        }
        free(t.next);
        t = token_next(t.rest);
    }
    free(t.next);
    return st;
}
     
int main() {
    stack st = stack_new();
    st = stack_push(st, element_float_new(2));
    char* buffer;
    char* context; 

    while(1) {
        printf(YELLOW);  // ➤
        stack_print(st);
        printf(DEFAULT);

        buffer = str_input_new();
        context = str_from_file_new("std.kc");
        
        st = eval(buffer, context, st);
        
        free(buffer);
        free(context);
    }                        
}
    
    

