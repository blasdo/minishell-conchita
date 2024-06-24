/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:49:21 by bvelasco          #+#    #+#             */
/*   Updated: 2024/06/25 00:39:52 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_empty_line(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (1);
		line++;
	}
	return (0);
}

static void	executor(t_input *input, int *status)
{
	__int8_t	code;	

	signals_notty();
	if (input && input->noc == 1)
	{
		if (input->cmds[0]->args && input->cmds[0]->args[0]
			&& !ft_strncmp(input->cmds[0]->args[0], "exit", 5))
		{
			if (input->cmds[0]->argc < 2)
				code = 2;
			else if (input->cmds[0]->argc > 2)
				return ((void)printf("exit: too many args\n"));
			else
				if (!ft_isnumber(input->cmds[0]->args[1]))
					return ((void)printf("The argument must be numeric\n"),
						exit(2));
			else
				code = ft_atoi(input->cmds[0]->args[1]);
			(printf("exit\n"), exit(code));
		}
		exec_one(input, status);
	}
	else if (input && input->noc > 1)
		exec_multiple(input, status);
	signals_tty();
}

int	ft_wexitstatus(int raw_status)
{
	return ((raw_status & 0xFF00) >> 8);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*env;
	t_input	*input;
	char	*rawline;
	int		status;

	if (argc == 2)
	{
		if (!ft_strncmp(argv[1], "--version", 10))
		{
			printf("conchita 1.0 by bvelasco & dximenez\nmainteined by:bvelasco\n");
			exit(0);
		}
	}
	((void) argc, (void) argv, signals_tty(), get_cwd());
	env = parse_env(envp);
	rawline = readline("conchita$ ");
	while (rawline)
	{
		if (rawline[0] != 0)
		{
			add_history(rawline);
			if (is_empty_line(rawline))
			{
				input = parse_line(&env, rawline);
				executor(input, &status);
				set_qtmark(&env, ft_wexitstatus(status));
				clear_input(input);
			}
		}
		free(rawline);
		rawline = readline("conchita$ ");
	}
	return (ft_lstclear_type(&env, clear_env_list), 0);
}
