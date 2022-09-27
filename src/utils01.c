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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	while (n > 0)
	{
		n--;
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
		if (c1 != c2)
			return (c1 - c2);
		if (c1 == '\0')
			return (0);
	}
	return (0);
}

char* ft_strjoin(char const *s1, char const *s2)
{
	int len = ft_strlen(s1) + ft_strlen(s2) + 1;
	char *str = malloc(sizeof(char) * len);

	while(s1 && *s1)
	{
		*str++ = *s1++;
	}
	while(s2 && *s2)
	{
		*str++ = *s2++;
	}
	*str = '\0';
	return (str - len);
}