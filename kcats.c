#include <stdbool.h>  // true, flase
#include <iso646.h>  // or, and, not
#include <stdio.h>  

#include "stupid/colors.h"
#include "stupid/str.h"

#include "eval.h"

//#define err(...) do { printf(RED); printf(__VA_ARGS__); printf(DEFAULT); } while (0)
     
int main(int argc, char *argv[]) {

    stack st = stack_new();
    char* input;
    char* context; 
    
    if (argc == 2) {
        input = str_from_file_new(argv[1]);
        context = str_from_file_new("std.kc");
        
        st = eval(input, context, st);

        free(input);
        free(context);
    }

    while (true) {
        printf(YELLOW);
        stack_print(st);
        printf(DEFAULT);

        input = str_input_new();
        context = str_from_file_new("std.kc");
        
        st = eval(input, context, st);

        free(input);
        free(context);
    }                        
}
    
    

