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

#include "stack.c"
#include "context.c"


bool seq(char s1[], char s2[]) {  // string equal
    if(strcmp(s1, s2) == 0) return true; 
    else return false;
}

bool is_definition(char w[]) {
    int l = strlen(w);     
    if((l>1) and (w[l-1]=='{' or w[l-1]==':')) return true;
    else return false;
}

char *token_next(char n[], char s[]) {
    int i = 0, j = 0;
    while(s[i] != '\0') {
        if(not isspace(s[i])) n[j++] = s[i];
        else if(j > 0) break;
        i++;
    }
    n[j] = '\0';           
    return &s[i];
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
    else if(p = context_find_def(context, w), p != NULL) eval(p, context);
    else printf(RED "%s? \n" DEFAULT, w);    
    return true;
}

void eval(char sentence[], char context[]) {
    
    char next[80]; //, rest[80];
    char *rest, *dot, *ret;
    rest = token_next(next, sentence);
                       // printf("[[[%s|||%s]]]",next,rest);
    if(*next=='\0' or *next=='\n') return;
    
    if(is_definition(next)) {
        printf("Unimplemented \n");
    } else {
        if(seq(next, "#")) {
            rest = strstr(rest, "\n");
        }
        if(seq(next, "then") or seq(next, ":")) {
            rest = token_next(next, rest);
            if(stack_pop()==0) { 
                dot = strstr(rest, ".");
                ret = strstr(rest, "return");
                if (dot != NULL and ret != NULL) {    
                    // this gotta be slow:
                    rest = strlen(dot) > strlen(ret) ? dot : ret;
                } else if(dot == NULL and ret != NULL) {
                    rest = ret;
                } else if(dot != NULL and ret == NULL) {
                    rest = dot;
                } else {
                    printf("then/: does not have a return/.");
                }
                rest = token_next(next, rest);
                rest = token_next(next, rest);
            }
            //stack_pop();
        }                   
        if(eval_word(next, context)) eval(rest, context);
    }
}
     
int main() {
    
    char buffer[80];
    char *con; 

    con = context_new();         
    con = context_add(con, ""); // HACK  
    con = context_add_file(con, "std.kc"); 

    while(1) {
        stack_print();
        printf(YELLOW "<> " DEFAULT);  // ➤
        fgets(buffer, 80, stdin); 

        
        eval(buffer, con);

    }                        
    context_del(con);   //   log(con);
}
    
    















