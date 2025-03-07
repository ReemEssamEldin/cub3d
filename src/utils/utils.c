#include "utils.h"

void	err_msg(char *err_msg)
{
	printf("%s", err_msg);
	//frees/destroys go here;
	exit(EXIT_FAILURE);
}

char	*remove_trailing(char *str, char const *c)
{
	int		start;
	int		end;
	char	*trimmed;

	if (!c || !str)
		return (NULL);
	start = 0;
	while (str[start] != '\0' && ft_strchr(c, str[start]) != NULL)
		start++;
	end = ft_strlen(str + start);
	while (end > start && ft_strchr(c, str[(start + end) - 1]) != NULL)
		end--;
	trimmed = ft_calloc((end + 1), sizeof(char *));
	if (!trimmed)
		return (NULL);
	ft_strncpy(trimmed, (str + start), end);
	free(str);
	return (trimmed);
}