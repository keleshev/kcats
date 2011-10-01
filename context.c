


char *context_new(void) {
    char *c = malloc(strlen("# Context \n"));
    return strcat(c, "# Context \n");
}

// context_add
char *context_add(char *context, char *string) {
    context = realloc(context, strlen(context) + strlen(string) + 1);
    return strcat(context, string);
    //return strcpy(old, new);
    //strcpy(new, old);
    //return new;
}

// context_add_file
char *context_add_file(char *context, char *filename) {
    FILE* f = fopen(filename, "r");
    if(f == NULL) printf("\nCan't open %s!\n", filename);
    
    // quick & dirty filesize calculation
    fseek(f, 0, SEEK_END);
    size_t filesize = ftell(f);      
    fseek(f, 0, SEEK_SET);

    //char buffer[filesize];
    char* buffer = malloc(filesize);
    fread(buffer, filesize, 1, f);

    if(fclose(f) != 0) printf("\nCan't close %s!\n", filename);

    context = context_add(context, buffer);
    free(buffer);
    return context;
}


// context_find_def
char *find_def(char *word, const char *context) {
    char def[sizeof(word) + 2];
    sprintf(def, "\n%s:", word);
                   
    char *r = strstr(context, def);
    if(r == NULL) return NULL;
    else return r + strlen(def);
}       


void context_destroy(char *context) {
    free(context);
}


