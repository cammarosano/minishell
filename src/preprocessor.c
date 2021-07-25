#include "header.h"

static int	is_valid_char4varname(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

static void	text(char **dst, char *line, int *state)
{
	if (*line == '|')
		*(*dst)++ = PIPE;
	else if (*line == '$' && is_valid_char4varname(line[1]))
		*(*dst)++ = DOLLAR_SIGN;
	else if (*line == ' ')
		*(*dst)++ = SPACEBAR;
	else if (*line == '<')
		*(*dst)++ = LESS_THAN;
	else if (*line == '>')
		*(*dst)++ = GREATER_THAN;
	else if (*line == '\"')
		*state = s_dquote;
	else if (*line == '\'')
		*state = s_squote;
	else
		*(*dst)++ = *line;
}

static void	dquote(char **dst, char *line, int *state)
{
	if (*line == '$' && is_valid_char4varname(line[1]))
		*(*dst)++ = DOLLAR_SIGN;
	else if (*line == '\"')
		*state = s_text;
	else
		*(*dst)++ = *line;
}

static void	squote(char **dst, char *line, int *state)
{
	if (*line == '\'')
		*state = s_text;
	else
		*(*dst)++ = *line;
}

// Returns a freeable string containing the characters of line after
// interpreting quoting ( "  ' ).
// Spaces, dollar-sign, > , < and pipe are replaced by negative integers
char	*pre_processor(char *line)
{
	char			*dst;
	char			*ptr;
	int				state;
	static	void	(*f[5])(char **, char *, int *) = {text, dquote, squote};

	dst = malloc(ft_strlen(line) + 1);
	if (!dst)
		return (NULL);
	ptr = dst;
	state = s_text;
	while (*line)
	{
		f[state](&ptr, line, &state);
		line++;
	}
	*ptr = '\0';
	if (state != s_text)
	{
		ft_putendl_fd("Syntax error", 2);
		free(dst);
		dst = NULL;
	}
	return (dst);
}
