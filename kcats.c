#include <stdbool.h>  // true, flase
#include <iso646.h>  // or, and, not
#include <stdio.h>  

#include "stupid/colors.h"
#include "stupid/str.h"

#include "eval.h"

//#define err(...) do { printf(RED); printf(__VA_ARGS__); printf(DEFAULT); } while (0)
     
int main() {
    stack st = stack_new();
    st = stack_push(st, element_float_new(2));
    char* input;
    char* context; 

    while (true) {
        printf(YELLOW);  // ➤
        //stack_print(st);
        printf(DEFAULT);

        input = str_input_new();
        context = str_from_file_new("std.kc");
        
        st = eval(input, context, st);
        
        free(input);
        free(context);
    }                        
}
    
    

