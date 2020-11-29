#include <stdio.h>
#include <glib.h>

#define MAX_STR_LEN 80

gboolean strCMP(gpointer key, gpointer value, gpointer data) {
    return !g_strcmp0(key, data);
}

void print_word_count(gpointer key, gpointer dict) {
    int w_count = GPOINTER_TO_INT(g_hash_table_find(dict, (GHRFunc)strCMP, key));
    printf("%s: %d\n", (char*) key, w_count);
}

gint int_compare(gpointer x, gpointer y, gpointer dict) {
    int _x = GPOINTER_TO_INT(g_hash_table_find(dict, strCMP, x));
    int _y = GPOINTER_TO_INT(g_hash_table_find(dict, strCMP, y));
    return _y - _x;
}

int read_to_buf(char buf[], FILE *f) {
    int i = 0;
    static int c = ' ';
    if (c == EOF) {
        return EOF;
    }

    c = fgetc(f);
    while (i < MAX_STR_LEN && c != '\n' && c != EOF) {
        buf[i] = c;
        
        ++i;
        c = fgetc(f);
    }

    buf[i] = '\0';
    while(c != '\n' && c != EOF) {
        c = fgetc(f);
    }

    return 0;
}

int main(int argc, const char **argv) {
    if (argc < 1) {
        printf("pass filename in 1st argument\n");
        return -1;
    }


    FILE *f = fopen(argv[1], "r");
    if (!f) {
        printf("Can't to open file %s\n", argv[1]);
        return -1;
    }

    char line[MAX_STR_LEN+1];

    GHashTable *dict = g_hash_table_new(g_str_hash, g_str_equal);
    while (read_to_buf(line, f) != EOF) {
        gchar **tokens = g_strsplit_set(line, " ,.!:/|", 0); //TODO check -1
        int num_tokens = g_strv_length(tokens);
        
        for (int i = 0; i < num_tokens; ++i) {
            gchar *word = g_strdup(tokens[i]);
            if (!g_strcmp0(word, ""))
                continue;

            int *count = g_hash_table_lookup(dict, word);
            if (!count) { 
                g_hash_table_insert(dict, word, GINT_TO_POINTER(1));
            } else {
                g_hash_table_replace(dict, word, GINT_TO_POINTER(GPOINTER_TO_INT(count) + 1));
            }
        }
        g_strfreev(tokens);
    }

    GSList *keys = g_hash_table_get_keys(dict);
    keys = g_slist_sort_with_data(keys, (GCompareDataFunc)int_compare, dict);

    g_slist_foreach(keys, print_word_count, dict);

    g_slist_free(keys);
    g_hash_table_destroy(dict);
    fclose(f);

    return 0;
}