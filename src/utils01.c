#include "../minishell.h"

static void	ft_count(char const *s, char c, int *parts, int *cC)
{
	int		i;

	i = 0;
	while (s[i] != 0 && s[i] == c)
	{
		i++;
		(*cC)++;
	}
	while (s[i] != 0)
	{
		if (s[i] == c)
		{
			while (s[i] != 0 && s[i] == c)
			{
				i++;
				(*cC)++;
			}
			if (s[i] == 0)
				return ;
			(*parts)++;
		}
		else
			i++;
	}
}

static void	ft_enter_data(void	*startPtr, int fLen, char const *s, char c)
{
	int		i;
	int		j;
	int		skp;

	i = 0;
	j = 0;
	skp = 0;
	if (s[i] != c)
	{
		((char **)startPtr)[j] = &((char *)startPtr)[fLen];
		j++;
	}
	while (s[i] != 0)
	{
		if (s[i] == c && s[i] == s[i + 1] && s[i + 1] != '\0')
			skp++;
		if (s[i] == c && s[i] != s[i + 1] && s[i + 1] != '\0')
		{
			((char **)startPtr)[j] = &((char *)startPtr)[i + fLen + 1 - skp];
			j++;
		}
		else if (s[i] != c)
			((char *)startPtr)[i + fLen - skp] = s[i];
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		fLen;
	int		cC;
	void	*startPtr;
	int		parts;

	parts = 1;
	cC = 0;
	ft_count(s, c, &parts, &cC);
	fLen = sizeof(char *) * (parts + 1);
	startPtr = ft_calloc((fLen + ft_strlen(s) - cC + parts), 1);
	if (startPtr == 0)
		return (NULL);
	if (*s == '\0')
	{
		((char **)startPtr)[0] = NULL;
		return ((char **)startPtr);
	}
	ft_enter_data(startPtr, fLen, s, c);
	return ((char **)startPtr);
}
