/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:53:06 by bvelasco          #+#    #+#             */
/*   Updated: 2024/06/19 20:40:18 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expand_token(t_list *env, t_token_type type, char *raw_value);

static t_token_type	identify_token_type(char *value)
{
	int	i;

	i = 0;
	if (!ft_isredir(value[0]))
		return (ARG);
	if (value[0] == '<')
	{
		if (!ft_isredir(value[1]))
			return (RD);
		if (value[1] == '>' || ft_isredir(value[2]))
			return (IN);
		if (value[1] && value[1] == '<')
			return (HD);
	}
	if (value [0] == '>' && (value[1] == '<'))
		return (IN);
	while (ft_isredir(value[i]))
		i++;
	if (i > 2)
		return (IN);
	return (RD);
}

char	*expand_var(t_list *env, char *var)
{
	char	*result;
	char	*varname;

	varname = get_varname(var);
	if (!varname)
		return (NULL);
	result = get_env_var(env, varname);
	free(varname);
	return (result);
}

static size_t	create_token(t_list *env, char *start, size_t len,
		t_list **list)
{
	t_list	*node;
	t_token	*tok;
	char	*substr;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (1);
	substr = ft_substr(start, 0, len);
	if (!substr)
		return (free(tok), 1);
	tok->type = identify_token_type(substr);
	tok->value = expand_token(env, tok->type, substr);
	free(substr);
	if (tok->type == IN)
		return (printf("Invalid redir\n"), free(tok->value), free(tok), 1);
	if (!tok->value)
		return (free(tok), 1);
	node = ft_lstnew_type(OTHER, (t_content)(void *)tok);
	if (!node)
		return (free(tok->value), free(tok), 1);
	ft_lstadd_back(list, node);
	return (0);
}

static void	free_tok(t_content cnt, t_type type)
{
	t_token	*tok;

	(void) type;
	tok = cnt.oth;
	free(tok->value);
	free(tok);
}

/* Converts a "raw_command" in t_token list (use with ft_lstmap_env) */
t_content	create_token_list(t_list *env, t_content line)
{
	t_list	*toklist;
	int		i;
	int		toklen;

	i = 0;
	toklist = NULL;
	while (line.str[i])
	{
		if (!ft_isspace(line.str[i]))
		{
			toklen = get_rawtoken_len(line.str + i);
			if (create_token(env, line.str + i, toklen, &toklist))
				return (ft_lstclear_type(&toklist, free_tok),
					(t_content)(void *) NULL);
			i += toklen;
			continue ;
		}
		i++;
	}
	return (((t_content)(void *) toklist));
}
