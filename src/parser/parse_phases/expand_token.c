/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:30:51 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/24 21:03:42 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	up(size_t *i)
{
	(*i)++;
}

static size_t	get_real_token_size(t_list *env, char *rawtoken)
{
	size_t	i;
	size_t	len;
	char	*varname;

	i = 0;
	len = 0;
	while (rawtoken[i])
	{
		if (ft_isquote(rawtoken[i]))
		{
			len += get_quotelen(env, rawtoken + i);
			i += get_unexpanded_quotelen(rawtoken + i);
			continue ;
		}
		else if (rawtoken[i] == '$')
		{
			varname = get_varname(rawtoken + i);
			len += get_env_var_len(env, varname);
			i += get_varname_len(rawtoken + i);
			free(varname);
			continue ;
		}
		(up(&i), up(&len));
	}
	return (++len);
}

static int	expand_quote_var(char *raw_value, int i, char **aux, t_list *env)
{
	if (ft_isquote(raw_value[i]))
	{
		*aux = expand_quote(env, raw_value + i);
		i += get_unexpanded_quotelen(raw_value + i);
	}
	else if (raw_value[i])
	{
		*aux = expand_var(env, raw_value + i);
		i += get_varname_len(raw_value + i);
	}
	return (i);
}

char	*expand_token(t_list *env, t_token_type type, char *raw_value)
{
	const size_t	real_size = get_real_token_size(env, raw_value);
	int				i;
	int				j;
	char			*result;
	char			*aux;

	i = 0;
	j = 0;
	if (type == HD)
		return (ft_strdup(raw_value));
	result = ft_calloc(real_size, 1);
	while (raw_value[i])
	{
		if (!ft_isquote(raw_value[i]) && raw_value[i] != '$')
		{
			result[j++] = raw_value[i++];
			continue ;
		}
		i = expand_quote_var(raw_value, i, &aux, env);
		j = ft_strlcat(result, aux, real_size);
		free(aux);
	}
	return (result);
}
