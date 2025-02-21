#include "../includes/libft.h"

/**
 * ft_strcmp - compares the strings s1 and s2.
 *
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return: 0 if s1 and s2 are identical.
 * Otherwise the difference between the first differing pair of bytes.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
