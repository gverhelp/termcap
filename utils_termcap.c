/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termcap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverhelp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by gverhelp          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by gverhelp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/test.h"

int		ft_putchar2(int c)
{
	write(1, &c, 1);
	return (1);
}

void	init_struct_tc(t_termcap *tc)
{
	tc->i = 0;
	tc->y = 0;
	tc->line = NULL;
	tc->history = NULL;
	tc->len = 0;
	tc->a = 0;
	tc->fdhist = 0;
}

void	init_term(void)
{
	t_termios	term;
	t_termios	term_backup;

	tgetent(0, getenv("TERM"));
	tcgetattr(0, &term);
	tcgetattr(0, &term_backup);
	term.c_lflag = term.c_lflag & ~ICANON;
	term.c_lflag = term.c_lflag & ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
}

char	**ft_split_line(char *line, char *line2, int fd)
{
	char	**str;

	str = NULL;
	free(line);
	str = ft_split(line2, '\n');
	free(line2);
	close(fd);
	return (str);
}

char	**get_tab(void)
{
	int		fd;
	char	*line;
	char	*line2;
	char	*fri;

	line = NULL;
	line2 = ft_strdup("");
	if ((fd = open(".minishell_history.txt", O_RDONLY)) < 0)
		return (NULL);
	while (get_next_line3d(fd, &line) > 0)
	{
		fri = line2;
		line2 = ft_strjoin(line2, line);
		free(fri);
		fri = line2;
		line2 = ft_strjoin(line2, "\n");
		free(fri);
		free(line);
	}
	return (ft_split_line(line, line2, fd));
}
