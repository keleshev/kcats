#include <stdbool.h>  // true, flase
#include <iso646.h>  // or, and, not

#include "stupid/str.h"

typedef enum { _index, _float, _str, _symbol, _def, _empty } _token_kind;

typedef struct {
    _token_kind _kind;
    double _float;
    int _int;
    char* _str;
    char* _rest;
} token;

bool token_is_float(token tk) {
    return tk._kind == _float;
}

double token_float_value(token tk) {
    ass(token_is_float(tk));
    return tk._float;
}

bool token_is_index(token tk) {
    return tk._kind == _index;
}

int token_index_value(token tk) {
    ass(token_is_index(tk));
    return tk._int;
}

bool token_is_str(token tk) {
    return tk._kind == _str;
}

char* token_str_value(token tk) {
    ass(token_is_str(tk));
    return tk._str;
}

bool token_is_symbol(token tk) {
    return tk._kind == _symbol;
}

char* token_symbol_value(token tk) {
    ass(token_is_symbol(tk));
    return tk._str;
}

bool token_is_empty(token tk) {
    return tk._kind == _empty;
}

bool token_is_def(token tk) {
    return tk._kind == _def;
}

char* token_def_value(token tk) {
    ass(token_is_def(tk));
    return tk._str;
}

char* token_rest(token tk) {
    return tk._rest;
}

token token_parse(char* s) {
    token tk;
    unsigned b = 0;  // begin
    unsigned e = 0;  // end
    while (isspace(s[b]) and s[b]) b++;
    e = b;
    if (s[e] == '#') {  // #comment
        while (s[e] != '\n' and s[e]) e++;
        return token_parse(&s[e]);
    }
    if (s[e] == '[') {  // [index]
        e++;
        while ((not isspace(s[e])) and s[e]) e++;
        tk._kind = _index;
        ass(sscanf(str_sub_auto(s, b, e), "[%i]", &tk._int));
        tk._rest = &s[e];
        return tk;
    }
    if ((isdigit(s[e]) or ((s[e] == '-' or s[e] == '+') and isdigit(s[e + 1]))) and s[e]) {  // number
        e++;
        while ((not isspace(s[e])) and s[e]) e++;
        tk._kind = _float;
        ass(sscanf(str_sub_auto(s, b, e), "%lf", &tk._float));
        tk._rest = &s[e];
        return tk;
    }
    if (s[e] == '"') {  // "string"
        e++;
        while (s[e] != '"' and s[e]) e++;
        tk._kind = _str;
        tk._str = str_sub_new(s, b + 1, e);
        tk._rest = &s[++e];
        return tk;
    }
    if (str_len(&s[e]) != 0) {  // symbol/def
        while ((not isspace(s[e])) and s[e]) e++;
        char* tmp = str_sub_auto(s, b, e);
        if (str_endswith(tmp, ":")) {  // def
            tk._kind = _def;
            tk._str = str_sub_new(s, b, e-1);
        } else {  // symbol
            tk._kind = _symbol;
            tk._str = str_sub_new(s, b, e);
        }
        tk._rest = &s[e];
        return tk;
    }
    tk._kind = _empty;
    return tk;
}

void token_del(token tk) {
    if (token_is_str(tk) or token_is_symbol(tk) or token_is_def(tk)) {
        free(tk._str);
    }
}

token token_find_def(char* context, char* def) {
    // TODO maybe change oreder (def, context)?
    ass(str_len(context) > str_len(def));
    token tk = token_parse(context);
    while (true) {
        if (token_is_def(tk) and str_eq(token_def_value(tk), def)) 
            break;
        if (token_is_empty(tk))
            break;
        token_del(tk);
        tk = token_parse(tk._rest);
    }
    return tk;
}

token token_find_symbol(char* context, char* symbol) {
    // TODO maybe change oreder (symbol, context)?
    ass(str_len(context) > str_len(symbol));
    token tk = token_parse(context);
    while (true) {
        if (token_is_symbol(tk) and str_eq(token_symbol_value(tk), symbol))
            break;
        if (token_is_empty(tk))
            break;
        token_del(tk);
        tk = token_parse(tk._rest);
    }
    return tk;
}




