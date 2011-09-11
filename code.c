

char code[] = "\n"
"max: [2] [2] > [3] [3] swp > [3] * swp [4] * + swp x swp x return \n"
"e: 2.71822 return \n"
"!=: == ! return \n"
"<: swp >"

;


char *find_def(char *word, char *code) {
    char def[sizeof(word) + 2];
    sprintf(def, "\n%s:", word);
       // printf();
    return strstr(code, def) + strlen(def);
}       


//char code[] = "e: 2.71822 ";
//char code[] = "!=: == !":
