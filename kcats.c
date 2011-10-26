#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <ctype.h>
#include <math.h>
#include <iso646.h>

#include "colors.h"
#include "str.h"
#include "stack.c"

#define err(...) do { printf(RED); printf(__VA_ARGS__); printf(DEFAULT); } while (0)

void eval(char* sentence, char* context);

    
    
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


bool eval_word(char w[], char context[]) {
    se_t number;
    char *p; 
    unsigned index;                                           
    if(sscanf(w, "%lf", &number) == 1) stack_push(number);
    else if(sscanf(w, "[%u]", &index) == 1) stack_push(stack_read(index));
    //else if(sscanf(w, "'%[ -~^']'", str) == 1) printf(str);
    //else if(str_eq(w, "")) printf("oh, hai");
    else if(str_eq(w, "q")) exit(0);
    else if(str_eq(w, "#")) ;
    else if(str_eq(w, ":")) ;
    else if(str_eq(w, "then")) ;
    else if(str_eq(w, "context")) printf("%s", context);
    else if(str_eq(w, "return")) return false;
    else if(str_eq(w, ".")) return false;
    else if(str_eq(w, "log")) stack_print();
    else if(str_eq(w, "c")) stack_clear();
    else if(str_eq(w, "swp")) stack_swap();
    else if(str_eq(w, "x")) stack_pop();
    else if(str_eq(w, "+")) stack_infix(+);
    else if(str_eq(w, "^")) stack_prefix(pow);
    else if(str_eq(w, "*")) stack_infix(*);
    else if(str_eq(w, "/")) stack_infix(/);
    else if(str_eq(w, ">")) stack_infix(>);
    else if(p = find_def(context, w), p != NULL) eval(p, context);
    else err("%s? \n", w);    
    return true;
}

void eval(char* sentence, char* context) {
    
    token t = token_next(sentence);
    if(str_eq(t.next, "")) return;
    
    if(is_def(t.next)) 
        err("Definitions in REPL are not available yet. \n");
    
    // Contrlo flow:
    //if(str_eq(t.next, "#")) {
    //    free(t.next);
    //    t = token_skip_until_newline(t.rest);
    //} else if (str_eq(t.next, "{")) {
    //    free(t.next);
    //    t = token_skip_until(t.rest, "}");
    //} else 
    if((str_eq(t.next, ":") or str_eq(t.next, "then")) and stack_pop()==0) {
        free(t.next);
        t = token_skip_until_either(t.rest, ".", "return");
    }   

    if(eval_word(t.next, context)) eval(t.rest, context);
    free(t.next);
}
     
int main() {
    char* buffer;
    char* context; 

    while(1) {
        stack_print();
        printf(YELLOW "<> " DEFAULT);  // ➤

        buffer = str_input_new();
        context = str_from_file_new("std.kc");
        
        eval(buffer, context);
        
        free(buffer);
        free(context);
    }                        
}
    
    















