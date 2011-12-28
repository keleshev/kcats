#include "str.h"
#include "log.h"
#include "ass.h"


int main() {
    printf("=============================================\n");

 /* * * * * * * *       
  * str.h tests
  */
    
    char* s = "test string";
    
    // str_new()
    char* str_new_ = str_new(s);
    ass(str_new_ != s, "defferent ptr");
    ass_eq(str_new_, s);
    
    // str_auto()
    char* str_auto_ = str_auto(str_new_);
    ass(str_auto_ != str_new_, "different ptr");
    ass_eq(str_auto_, str_new_);

    // str_cat_new()
    char* str_cat_new_ = str_cat_new(s, " gnirts tset");
    ass(str_cat_new_ != s, "different ptr");
    ass_eq(str_cat_new_, "test string gnirts tset");

    // str_cat_auto()
    char* str_cat_auto_ = str_cat_auto(str_cat_new_, "!!");
    ass(str_cat_auto_ != str_cat_new_, "dif ptr");
    ass_eq(str_cat_auto_, "test string gnirts tset!!");

    // str_sub_new()
    char* str_sub_new_ = str_sub_new(s, 0, 4);
    ass_eq(str_sub_new_, "test");

    // str_sub_auto()
    char* str_sub_auto_ = str_sub_auto(s, 5, 200); // overalocated?
    ass_eq(str_sub_auto_, "string");
    ass_eq(str_sub_auto(s, 5, 5), "");
    ass_eq(str_sub_auto(s, 9, 1), "");

    // str_slice_new()
    char* str_slice_new_ = str_slice_new(s, 0, 4);
    ass_eq(str_slice_new_, "test");
    ass_eq(str_slice_new(s, 0, 0), "test string");
    ass_eq(str_slice_new(s, 5, 0), "string");
    ass_eq(str_slice_new(s,-6, 0), "string");

    // str_slice_auto()  
    ass_eq(str_slice_auto(s,-6,-3), "str");
    ass_eq(str_slice_auto(s,-1,-2), "");
    ass_eq(str_slice_auto(s, 2, 1), "");
    ass_eq(str_slice_auto(s, 5, 200), "string"); // overallocated?

    // str_input_dest()
    // str_input_new()
    // str_input_auto()

    // str_format_dest()  // sprintf
    // str_format_new()  // asprintf
    // str_format_auto()

    // str_len()  // strlen
    
    // str_is_alnum()
    ass(str_is_alnum("abc123"));
    ass(! str_is_alnum("(@^*^&"));

    // str_is_alpha()
    ass(str_is_alpha("abcdEFG"));
    ass(! str_is_alpha("!@#$@#$"));

    // str_from_file_new()
    char* str_from_file_new_ = str_from_file_new("file.test");
    ass_eq(str_from_file_new_, "file.test:test\n");

    // str_eq()
    ass(str_eq("abc", "abc"));
    ass(str_eq("", ""));

    // str_endswith()
    ass(str_endswith(s, "string"));
    ass(str_endswith(s, "ing"));
    ass(str_endswith(s, "test string"));
    //ass(str_endswith(s, "")); //hm...
    //logs(str_slice_auto(s, -1 * strlen(""), 0));
    ass(!str_endswith(s, "swing"));
    ass(!str_endswith(s, " test string"));

    // str_startswith()
    ass(str_startswith(s, "test"));
    ass(str_startswith(s, "test string"));
    ass(str_startswith(s, ""));

}
