#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <ctype.h>
#include <math.h>
#include <iso646.h>

#define YELLOW  "\033[1;33m"
#define PURPLE  "\033[1;35m"
#define BLUE    "\033[1;34m"
#define RED     "\033[1;31m"
#define DEFAULT "\033[0m"

#define log(v) printf(PURPLE "\n[%s:%d] " #v " == " BLUE "%s \n" DEFAULT, __FILE__, __LINE__, v)

#include "str.h"
#include "stack.c"
//#include "context.c"

char *find_def(char *context, char *word) {
    char def[sizeof(word) + 2];
    sprintf(def, "\n%s:", word);
                   
    char *r = strstr(context, def);
    if(r == NULL) return NULL;
    else return r + strlen(def);
}       

bool seq(char s1[], char s2[]) {  // string equal
    if(strcmp(s1, s2) == 0) return true; 
    else return false;
}

bool is_definition(char w[]) {
    int l = strlen(w);     
    if((l>1) and (w[l-1]=='{' or w[l-1]==':')) return true;
    else return false;
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
    unsigned index;                                           
    if(sscanf(w, "%lf", &number) == 1) 
        {stack_push(number);}
    else 
        if(sscanf(w, "[%u]", &index) == 1) stack_push(stack_read(index));
    //else if(sscanf(w, "'%[ -~^']'", str) == 1) printf(str);
    //else if(seq(w, "")) printf("oh, hai");
    else 
        if(seq(w, "q")) exit(0);
    else if(seq(w, "#")) ;
    else if(seq(w, ":")) ;
    else if(seq(w, "context")) printf(context);
    else if(seq(w, "return")) return false;
    else if(seq(w, ".")) return false;
   // else if(seq(w, "then")) { return false;}
    else if(seq(w, "log")) stack_print();
    else if(seq(w, "c")) stack_clear();
    else if(seq(w, "swp")) stack_swap();
    else if(seq(w, "x")) stack_pop();
    else if(seq(w, "+")) stack_infix(+);
    else if(seq(w, "^")) stack_prefix(pow);
    else if(seq(w, "*")) stack_infix(*);
    else if(seq(w, "/")) stack_infix(/);
    else if(seq(w, ">")) stack_infix(>);
    //else if(seq(w, "!")) stack_prefix_1(!);
    //else if(seq(w, "==")) stack_infix(==);
    else if(p = find_def(context, w), p != NULL) eval(p, context);
    else printf(RED "%s? \n" DEFAULT, w);    
    return true;
}

void eval(char* sentence, char* context) {
    
    token t = token_next(sentence);
    if(str_eq(t.next, "")) return;
    
    if(is_definition(t.next)) 
        printf("Definitions in REPL are not available yet. \n");
    
    // Contrlo flow:
    //if(str_eq(t.next, "#")) {
    //    free(t.next);
    //    t = token_skip_until_newline(t.rest);
    //} else if (str_eq(t.next, "{")) {
    //    free(t.next);
    //    t = token_skip_until(t.rest, "}");
    //} else 
    if(str_eq(t.next, ":") and stack_pop()==0) {
        free(t.next);
        t = token_skip_until(t.rest, ".");
    }   

    if(eval_word(t.next, context)) eval(t.rest, context);
    free(t.next);
}
     
int main() {
    token t = token_next("  one \n two three ");
    printf("<%s|%s>", t.next, t.rest);

    t = token_next(" \n two three ");
    printf("<%s|%s>", t.next, t.rest);
    
    t = token_next("three ");
    printf("<%s|%s>", t.next, t.rest);
    
    t = token_next("");
    printf("<%s|%s>", t.next, t.rest);
     
    t = token_skip_until(" abc def ghi . jkl mno ", ".");
    printf("<%s|%s>", t.next, t.rest);
    

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
    
    















