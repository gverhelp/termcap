/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverhelp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by gverhelp          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by gverhelp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdlib.h>
# include <term.h>
# include <termios.h>
# include "../libft/libft.h"

typedef struct termios	t_termios;

typedef struct	s_termcap
{
	int			len;
	int			i;
	int			y;
	int			a;
	char		*line;
	char		**history;
	int			fdhist;
}				t_termcap;

int				ft_putchar2(int c);
void			init_struct_tc(t_termcap *tc);
void			init_term(void);
char			**ft_split_line(char *line, char *line2, int fd);
char			**get_tab();
void			get_history(t_termcap *tc);
void			ft_write_in_history(t_termcap *tc);
void			ft_write_line(t_termcap *tc, char *str);
void			ft_key_backspace(t_termcap *tc);
void			ft_key_down(t_termcap *tc);
int				ft_newline_history(t_termcap *tc, char **add);
int				ft_key_up(t_termcap *tc, char **add);
int				ft_loop(t_termcap *tc, char **add, char *str);
char			*ft_termcap(void);

#endif
