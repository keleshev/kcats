#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
//#include <string.h> 

#include "ass.h"
#include "del.h"
#include "str.h"          
#include "log.h"

//
// Types
// 

typedef struct _element element;
typedef struct _stack stack;

struct _stack {
    element* _top;
    element* _bottom;
};

struct _element {
    char* _type;
    union {
        double _float;
        int    _int;
        char*  _str;
        stack  _stack;
    } _data;
};  

//
// Element functions
//

element element_float_new(double f) {
    element el;
    el._type = str_new("float");
    el._data._float = f;
    return el;
}

element element_int_new(int i) {
    element el;
    el._type = str_new("int");
    el._data._int = i;
    return el;
}

element element_str_new(char* s) {
    element el;
    el._type = str_new("str");
    el._data._str = str_new(s);
    return el;
}

stack stack_copy(stack);

element element_stack_new(stack st) {
    element el;
    el._type = str_new("stack");
    el._data._stack = st;
    return el;
}

bool element_eq(element e1, element e2) {
    if (!str_eq(e1._type, e2._type)) return false;
    // TODO not only floats
    if (e1._data._float != e2._data._float) return false;
    return true;
}

char* element_type(element el) {
    return el._type;
}

void element_print(element el) {
    if (str_endswith(el._type, " float") || str_eq(el._type, "float")) {
        printf("%g", el._data._float);
    } else if (str_endswith(el._type, " int") || str_eq(el._type, "int")) {
        printf("%i", el._data._int);
    } else if (str_endswith(el._type, " str") || str_eq(el._type, "str")) {
        printf("%s", el._data._str);
    } else if (str_endswith(el._type, " stack") || str_eq(el._type, "stack")) {
        stack_print(el._data._stack);
    }
}

void element_del(element el) {
    if (str_endswith(el._type, " str") || str_eq(el._type, "str")) {
        del(el._data._str);
    } else if (str_endswith(el._type, " stack") || str_eq(el._type, "stack")) {
        stack_del(el._data._stack);
    }
    del(el._type);
}

//
// Stack functions
//

stack stack_new() {
    stack st;
    st._bottom = NULL;
    st._top = NULL;
    return st;
}

signed stack_size(stack st) {
    if (st._top == NULL && st._bottom == NULL) {
        return 0;
    } else {
        ass(st._top != NULL);      
        ass(st._bottom != NULL);   
        return st._top - st._bottom + 1;
    }
}

element stack_top(stack st) {
    ass(stack_size(st) != 0);
    ass(st._top != NULL);
    return *st._top;
}

element stack_bottom(stack st) {
    ass(stack_size(st) != 0);
    ass(st._bottom != NULL);
    return *st._bottom;
}


stack stack_push(stack st, element el) {
    signed new_size = stack_size(st) + 1;  
    st._bottom = realloc(st._bottom, new_size * sizeof(element)); 
    ass(st._bottom != NULL);
    st._top = st._bottom + new_size - 1;
    if (new_size == 1) ass_eq(st._top, st._bottom);
    ass(st._top != NULL);
    *st._top = el;
    return st; 
}

stack stack_pop(stack st) {
    signed new_size = stack_size(st) - 1;  
    element_del(stack_top(st));
    st._bottom = realloc(st._bottom, new_size * sizeof(element)); 
    if (new_size == 0) return stack_new();
    st._top = st._bottom + new_size - 1;
    return st;
}

element stack_peek(stack st, signed n) {
    ass(n <= stack_size(st));
    return *(st._top - n);
}

#define for_element_in_stack(el, st) \
    element el=stack_top(st);                                      \
    for (int _i=1; _i <= stack_size(st); el=stack_peek(st, _i++))

void stack_print(stack st) {
    printf("< ");
    for_element_in_stack(el, st) {
        element_print(el);
        printf(" ");
    }
    printf(">");
}

stack stack_copy(stack st) {
    stack new_st = stack_new();
    for_element_in_stack(el, st) {
        new_st = stack_push(new_st, el);
    }
    return new_st;
}

void stack_del(stack st) {
    // TODO
}


