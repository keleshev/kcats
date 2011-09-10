#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>            
#include <math.h>
#include "stack.c"
#include "code.c"

#define YELLOW  "\e[1;33m"
#define RED     "\e[1;31m"
#define DEFAULT "\e[0m"

bool seq(char s1[], char s2[]) {  // string equal
    if(strcmp(s1, s2) == 0) return true; 
    else return false;
}

bool is_definition(char w[]) {
    int len = strlen(w);     
    if((len > 1) && (w[len-1] == ':')) return true;
    else return false;
}

void eval_word(char word[]) {
    char w[80]; strcpy(w, word);
    se_t number;
    unsigned int index; 
    if(sscanf(w, "%lf", &number) == 1) stack_push(number);
    else if(sscanf(w, "[%u]", &index) == 1) stack_push(stack_read(index));
    else if(seq(w, "")) printf("oh, hai");
    else if(seq(w, "q")) exit(0);
    else if(seq(w, "c")) stack_clear();
    else if(seq(w, "swp")) stack_swap();
    else if(seq(w, "x")) stack_pop();
    else if(seq(w, "+")) stack_infix(+);
    else if(seq(w, "^")) stack_prefix(pow);
    else if(seq(w, "*")) stack_infix(*);
    else if(seq(w, "/")) stack_infix(/);
    else if(seq(w, ">")) stack_infix(>);
    else if(seq(w, "!")) stack_prefix_1(!);
    else if(seq(w, "and")) stack_infix(&&);
    else printf(RED "%s? \n" DEFAULT, w); 
}

void eval(char s[]) {
    char tmp[80]; 
    strcpy(tmp, s);
    char *word = strtok(tmp, " \t\n");
                //printf("<%s,%c>",tmp);
//    strlen(word);
    //printf("{%s}{%s}{%c}", word, s, word[strlen(word)-1]);
    if(is_definition(tmp)) printf("Unimplemented\n");
    else {
        eval_word(tmp);
        //eval(rest);
    }
}

int main() {
    char buffer[80];
    while(1) {
        stack_print();
        printf(YELLOW "> " DEFAULT);  // ➤
        fgets(buffer, 80, stdin); 
        //if(seq(buffer, "\n")) {printf("cont"); continue;}
        //printf("{%c|%c|%s}", buffer[0], buffer[1], buffer);
        eval(buffer);
    }
}
    
    















