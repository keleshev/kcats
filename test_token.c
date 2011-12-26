#include <iso646.h>  // or, and, not
#include "stupid/ass.h"

#include "stupid/log.h"

#include "token.h"


void test_token_parse__index(void) {
    token tk = token_parse(" \n [0] [12] bar");
    ass(token_is_index(tk));
    ass(token_index_value(tk) == 0);
    ass(str_eq(token_rest(tk), " [12] bar"));

    token tk2 = token_parse(token_rest(tk));
    ass(token_is_index(tk2));
    ass(token_index_value(tk2) == 12);
    ass(str_eq(token_rest(tk2), " bar"));
}

void test_token_parse__float(void) {
    token tk = token_parse("3.14 2.72 foo bar");
    ass(token_is_float(tk));
    ass(token_float_value(tk) == 3.14);
    ass(str_eq(token_rest(tk), " 2.72 foo bar"));

    token tk2 = token_parse(token_rest(tk));
    ass(token_is_float(tk2));
    ass(token_float_value(tk2) == 2.72);
    ass(str_eq(token_rest(tk2), " foo bar"));
}

void test_token_parse__str(void) {
    token tk = token_parse("\n \"hello world!\" \n \" foobar \" 3 4");
    ass(token_is_str(tk));
    ass(str_eq(token_str_value(tk), "hello world!"));
    ass(str_eq(token_rest(tk), " \n \" foobar \" 3 4"));

    token tk2 = token_parse(token_rest(tk));
    ass(token_is_str(tk2));
    ass(str_eq(token_str_value(tk2), " foobar "));
    ass(str_eq(token_rest(tk2), " 3 4"));
}

void test_token_parse__symbol(void) {
    //TODO foo#comment
    token tk = token_parse("\nfoo   bar\nspam\teggs");
    ass(token_is_symbol(tk));
    ass(str_eq(token_symbol_value(tk), "foo"));
    ass(str_eq(token_rest(tk), "   bar\nspam\teggs"));
    
    token tk2 = token_parse(token_rest(tk));
    ass(token_is_symbol(tk2));
    ass(str_eq(token_symbol_value(tk2), "bar"));
    ass(str_eq(token_rest(tk2), "\nspam\teggs"));
}

void test_token_parse__def(void) {
    token tk = token_parse(" foo: bar # abc \nspam: eggs");
    ass(token_is_def(tk));
    ass(str_eq(token_def_value(tk), "foo"));

    token tk2 = token_parse(token_rest(tk));
    ass(token_is_symbol(tk2));
    ass(str_eq(token_symbol_value(tk2), "bar"));

    token tk3 = token_parse(token_rest(tk2));
    ass(token_is_def(tk3));
    ass(str_eq(token_def_value(tk3), "spam"));
}

void test_token_parse__empty(void) {
    token tk = token_parse("\n \t \r  \n\r");
    ass(token_is_empty(tk));

    token tk2 = token_parse("\n \t foo \n \r\t");
    ass(str_eq(token_symbol_value(tk2), "foo"));

    token tk3 = token_parse(token_rest(tk2));
    ass(token_is_empty(tk3));
}

void test_token_parse__comment(void) {
    token tk = token_parse("# abc def\nfoo #ghi jkl \n bar");
    ass(str_eq(token_symbol_value(tk), "foo"));

    token tk2 = token_parse(token_rest(tk));
    ass(str_eq(token_symbol_value(tk2), "bar"));
    ass(str_eq(token_rest(tk2), ""));
}

void test_token_parse__no_comment(void) {
    token tk = token_parse("\"not # a comment\" \"foo\" bar");
    ass(str_eq(token_str_value(tk), "not # a comment"));

    token tk2 = token_parse(token_rest(tk));
    ass(str_eq(token_str_value(tk2), "foo"));
}

void test_token_find_def(void) {
    token tk = token_find_def("abc def: #ghi jkl: \n foo: bar", "foo");
    ass(token_is_def(tk));
    ass(str_eq(token_def_value(tk), "foo"));
    ass(str_eq(token_rest(tk), " bar"));
}

void test_token_find_symbol(void) {
    token tk = token_find_symbol("abc # def \n ghi return foo \"bar\"", "return");
    ass(token_is_symbol(tk));
    ass(str_eq(token_symbol_value(tk), "return"));
    ass(str_eq(token_rest(tk), " foo \"bar\""));
}

int main() {
    printf("================ start ================\n");

    test_token_parse__index();
    test_token_parse__float();
    test_token_parse__str();
    test_token_parse__symbol();
    test_token_parse__def();
    test_token_parse__empty();
    test_token_parse__comment();
    test_token_parse__no_comment();
    //test_token_del
    test_token_find_def();
    test_token_find_symbol();

    printf("================= end =================\n");
}    
