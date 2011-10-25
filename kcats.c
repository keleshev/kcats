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

char *find_def(char *context, char *word) {
    char def[strlen(word) + 3];  // account for '\n', ':' and '\0'
    //char* def = malloc(sizeof(word) + 2);
    sprintf(def, "\n%s:", word);
    char *r = strstr(context, def);
    //free(def);
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
    unsigned b = 0;
    unsigned e = 0;
    while(isspace(s[b]) and s[b]) b++;
    e = b;
    while(!isspace(s[e]) and s[e]) e++;
    token t;
    t.next = str_slice_new(s, b, e);
    t.rest = &s[e];
    return t;
}

token token_skip_until(char* s, char* until) {
    token t = token_next(s);
    while(not str_eq(t.next, until)) {
        free(t.next);
        t = token_next(t.rest);    
    }
    free(t.next);
    t = token_next(t.rest); 
    return t;
}


bool eval_word(char w[], char context[]) {
    char w2[80];
    //strcpy(w, word);
    se_t number;
    se_t n2;
    //char *str[80];
    
    
    char *p; 
    
    
    p = find_def(context, w);                      
    
    
    unsigned index;                                           
    if(sscanf(w, "%lf", &number) == 1) {
            stack_push(number);
    }
    else 
        if(sscanf(w, "[%u]", &index) == 1) stack_push(stack_read(index));
    //else if(sscanf(w, "'%[ -~^']'", str) == 1) printf(str);
    //else if(str_eq(w, "")) printf("oh, hai");
    else 
        if(str_eq(w, "q")) exit(0);
    else if(str_eq(w, "#")) ;
    else if(str_eq(w, ":")) ;
    else if(str_eq(w, "then")) ;
    else if(str_eq(w, "context")) printf(context);
    else if(str_eq(w, "return")) return false;
    else if(str_eq(w, ".")) return false;
   // else if(str_eq(w, "then")) { return false;}
    else if(str_eq(w, "log")) stack_print();
    else if(str_eq(w, "c")) stack_clear();
    else if(str_eq(w, "swp")) stack_swap();
    else if(str_eq(w, "x")) stack_pop();
    else if(str_eq(w, "+")) stack_infix(+);
    else if(str_eq(w, "^")) stack_prefix(pow);
    else if(str_eq(w, "*")) stack_infix(*);
    else if(str_eq(w, "/")) stack_infix(/);
    else if(str_eq(w, ">")) stack_infix(>);
    //else if(str_eq(w, "!")) stack_prefix_1(!);
    //else if(str_eq(w, "==")) stack_infix(==);
    else if(p != NULL) eval(p, context);
    else printf(RED "%s? \n" DEFAULT, w);    
    return true;
}

void eval(char* sentence, char* context) {
    
    token t = token_next(sentence);
    if(str_eq(t.next, "")) return;
    
    if(is_def(t.next)) 
        printf("Definitions in REPL are not available yet. \n");
    
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
        t = token_skip_until(t.rest, ".");
    }   

    if(eval_word(t.next, context)) {
        eval(t.rest, context);
    }
    free(t.next);
}
     
int main() {
    /*char* b = str_input_new();
    token t = token_next(b);
    printf("<%s|%s>", t.next, t.rest);

    /*t = token_next(" \n two three ");
    printf("<%s|%s>", t.next, t.rest);
    
    t = token_next("three ");
    printf("<%s|%s>", t.next, t.rest);
    
    t = token_next("");
    printf("<%s|%s>", t.next, t.rest);
     
    t = token_skip_until(" abc def ghi . jkl mno ", ".");
    printf("<%s|%s>", t.next, t.rest);*/

    char* buffer;
    char* context; 


    while(1) {
        stack_print();
        printf(YELLOW "<> " DEFAULT);  // ➤

        buffer = str_input_new();
        context = str_from_file_new("std.kc");
        
        token t = token_next(buffer);
        eval(buffer, context);
        
        free(buffer);
        free(context);

    }                        
}
    
    















