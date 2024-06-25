/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:30:29 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/25 11:47:24 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Get the current working directory
 * @param cwd The destination string
 * @return 1 if success, 0 if error
 */
char	*get_cwd(void)
{
	static char	cwd[PATH_MAX];
	char		_cwd[PATH_MAX];

	if (getcwd(_cwd, PATH_MAX) == NULL)
	{
		if (*_cwd != '\0')
			return (cwd);
		return (NULL);
	}
	ft_memcpy(cwd, _cwd, PATH_MAX);
	return (cwd);
}
