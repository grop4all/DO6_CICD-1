#include "s21_cat.h"


int main(int argc, char **argv) {
    s21_cat(argc, argv);
    return 0;
}

void s21_cat(int argc, char **argv) {
    list_flag flag;
    int len_file_list = 0;
    char ** file_list = malloc(sizeof(char *) * (argc));
    if (parser(argc, argv, &flag, file_list, &len_file_list)) {
        for (int i = 0; i < len_file_list; ++i) {
            FILE *file = fopen(file_list[i], "r");
            if (errno) {
                perror("Error: ");
                return;
            }
            if (file) {
                write_file(file, &flag, 0);
                write_file(file, &flag, 1);
                fclose(file);
            }
        }
    }
    free(file_list);
}

int parser(int argc, char ** argv, list_flag *flag, char** file_list, int *len_file_list) {
    init(flag);
    int err = 0;
    if (check_file(argc, argv, file_list, len_file_list) && check_flag(argc, argv, flag))
        err = 1;
#ifdef DEBAG
    wr_flag_debag(flag);
#endif
    return err;
}

void init(list_flag *flag) {
    flag->MARK_END_LINES = 0;
    flag->NUMBER_LINE = 0;
    flag->NUMBER_NOBLANK_LINES = 0;
    flag->REMOVE_BLANK_LINES = 0;
    flag->REPLACE_TAB = 0;
}

void wr_flag_debag(list_flag *flag) {
    printf("MARK_END_LINES %i\n", flag->MARK_END_LINES);
    printf("REMOVE_BLANK_LINES %i\n", flag->REMOVE_BLANK_LINES);
    printf("NUMBER_NOBLANK_LINES %i\n", flag->NUMBER_NOBLANK_LINES);
    printf("NUMBER_LINE %i\n", flag->NUMBER_LINE);
    printf("REPLACE_TAB %i\n", flag->REPLACE_TAB);
}

int check_flag(int argc, char ** argv, list_flag *flag) {
    char c;
    int ind = 0;
    int err = 0;
    while ((c = getopt_long(argc, argv, "enbstv", long_options, &ind)) != -1) {
        err = 1;
        if (c == 'n')
            flag->NUMBER_LINE = 1;
        else if (c == 'b')
            flag->NUMBER_NOBLANK_LINES = 1;
        else if (c == 's')
            flag->REMOVE_BLANK_LINES = 1;
        else if (c == 't' || c == 'T' || c == 'v')
            flag->REPLACE_TAB = 1;
        else if (c == 'e')
            flag->MARK_END_LINES = 1;
        else if (c == '?')
            err = 0;
        else
            err = 0;
    }
    flag->NUMBER_LINE = !flag->NUMBER_NOBLANK_LINES * flag->NUMBER_LINE;
    return err;
}

int check_file(int argc, char ** argv, char ** file_list, int *len_file_list) {
    int err = 0;
    for (int i = 1; i < argc; ++i)
        if (strspn(argv[i], "-") != 1 && strspn(argv[i], "--") != 2) {
            file_list[*len_file_list] = argv[i];
            *len_file_list +=1;
        }
#ifdef DEBAG
    for (int i = 0; i < *len_file_list; ++i)
        printf("%s \n", file_list[i]);
#endif
    return (err == *len_file_list) ? -1 : 1;
}


void write_file(FILE * file, list_flag *flag, int reset) {
    static cat_struct c = {
        .buffer = {},
        .line = 1,
        .nl = 1,
        .prev_prev = 0,
        .prev = 0,
    };
    if (reset) {
#if defined(__MACH__) || defined(__APPLE__)
    c.line = 1;
#endif
    }
    while (feof(file) != EOF && file) {
        int ch = getc(file);
        if (ch == EOF)
            break;
        if (remove_blank_lines(ch, &c, flag))
            continue;
        c.prev_prev = c.prev;
        c.prev = ch;
        number_lines(ch, &c, flag);
        c.buffer[0] = ch;
        mark_end_lines(ch, &c, flag);
        replace_tabs(ch, &c, flag);
        fprintf(stdout, "%s", c.buffer);
        memset(c.buffer, '\0', MAX_CHAR_LEN);
    }
    if (errno)
        perror("Error: ");
}

int remove_blank_lines(char ch, cat_struct *c, list_flag *flag) {
    int ans = 0;
    if (ch == '\n' && c->prev_prev == '\n' && c->prev == '\n' &&
        flag->REMOVE_BLANK_LINES)
        ans = 1;
    return ans;
}

void mark_end_lines(char ch, cat_struct *c, list_flag *flag) {
    if (flag->MARK_END_LINES && ch == '\0') {
        c->buffer[0] = '$';
        c->buffer[1] = '\n';
    }
    if (flag->MARK_END_LINES && ch == '\n' && c->nl) {
        c->buffer[0] = '$';
        c->buffer[1] = '\n';
    }
}

void replace_tabs(char ch, cat_struct *c, list_flag *flag) {
    if (flag->REPLACE_TAB && ch == '\t') {
        c->buffer[0] = '^';
        c->buffer[1] = 'I';
    }
}

void number_lines(char ch, cat_struct *c, list_flag *flag) {
    if (flag->NUMBER_LINE && c->nl) {
        fprintf(stdout, "%6d\t", c->line);
        c->line++;
        c->nl = 0;
    }
    if (ch == '\n')
        c->nl = 1;
    if (flag->NUMBER_NOBLANK_LINES && c->nl && ch != '\n') {
        fprintf(stdout, "%6d\t", c->line);
        c->line++;
        c->nl = 0;
    }
}



