#include "pipex.h"

int ft_countwords(const char *str)
{
    int count = 0;
    int inWord = 0;

    while (*str)
    {
        if (*str == ' ')
            inWord = 0;
        else if (!inWord)
        {
            inWord = 1;
            count++;
        }
        str++;
    }
    return (count);
}

static char *ft_worddup(const char *str, int len)
{
    char *copy = malloc(len + 1);
    if (!copy)
        return (NULL);
    ft_strlcpy(copy, str, len + 1);
    return copy;
}

static char **ft_free_splits(char **strs, int count)
{
    while (count--)
		free(strs[count]);
	free(strs);
	return (NULL);
}

char **cmd_split(char const *s)
{
    int wordCount;
    int i;
    const char *start;

    if (!s)
        return NULL;
    wordCount = ft_countwords(s);
    char **strs = malloc(sizeof(char *) * (wordCount + 1));
    if (!strs)
        return NULL;
    i = 0;
    while (*s)
    {
        while (*s == ' ')
            s++;
        if (*s == '\0')
            break;
        if (*s == '\'')
        {
            s++;  
            start = s;
            while (*s && *s != '\'')  
                s++;
            int len = s - start;
            strs[i] = ft_worddup(start, len);
            if (!strs[i])
                return ft_free_splits(strs, i);
            i++;
            if (*s)
                s++;   
        }
        else
        {  
            start = s;
            while (*s && *s != ' ' && *s != '\'')  
                s++;
            int len = s - start;
            strs[i] = ft_worddup(start, len);
            if (!strs[i]) {
                return ft_free_splits(strs, i);
            }
            i++;
        }
    }

    strs[i] = NULL;
    return strs;
}

// int main() {
//     char **result = cmd_split("Hello 'world this' is a test");
//     if (result) {
//         for (int i = 0; result[i] != NULL; i++) {
//             printf("%s\n", result[i]);
//             free(result[i]);
//         }
//         free(result);
//     }
//     return 0;
// }
