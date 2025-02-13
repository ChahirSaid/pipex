#include <stdio.h>
#include <stdlib.h>

size_t ft_strlen(const char *str) {
    size_t i = 0;
    while (str[i])
        i++;
    return i;
}

size_t ft_strlcpy(char *dest, const char *src, size_t size) {
    size_t len = ft_strlen(src);
    if (size == 0)
        return len;
    size_t i = 0;
    while (src[i] && i < (size - 1)) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
    return len;
}

int ft_countwords(const char *str) {
    int count = 0;
    int inWord = 0;
    while (*str) {
        if (*str == ' ') {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            count++;
        }
        str++;
    }
    return count;
}

static int ft_wordlen(const char *str) {
    int len = 0;
    while (str[len] && str[len] != ' ' && str[len] != '\'') 
        len++;
    return len;
}

static char *ft_worddup(const char *str, int len) {
    char *copy = malloc(len + 1);
    if (!copy)
        return NULL;
    ft_strlcpy(copy, str, len + 1);
    return copy;
}

static char **ft_free_split(char **strs, int count) {
    for (int i = 0; i < count; i++) {
        free(strs[i]);
    }
    free(strs);
    return NULL;
}

char **cmd_split(char const *s) {
    if (!s)
        return NULL;

    int wordCount = ft_countwords(s);
    char **strs = malloc(sizeof(char *) * (wordCount + 1));
    if (!strs)
        return NULL;

    int i = 0;
    while (*s) {
        while (*s == ' ')
            s++;

        if (*s == '\0')
            break;

        if (*s == '\'') {
            s++;  
            const char *start = s;
            while (*s && *s != '\'')  
                s++;
            int len = s - start;
            strs[i] = ft_worddup(start, len);
            if (!strs[i]) {
                return ft_free_split(strs, i);
            }
            i++;
            if (*s) s++;   
        } else {  
            const char *start = s;
            while (*s && *s != ' ' && *s != '\'')  
                s++;
            int len = s - start;
            strs[i] = ft_worddup(start, len);
            if (!strs[i]) {
                return ft_free_split(strs, i);
            }
            i++;
        }
    }

    strs[i] = NULL;
    return strs;
}

int main() {
    char **result = cmd_split("Hello 'world this' is a test");
    if (result) {
        for (int i = 0; result[i] != NULL; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }
    return 0;
}