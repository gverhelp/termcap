#include "include/test.h"

int	ft_putchar2(int c)
{
	write(1, &c, 1);
    return (1);
}

void    init_term(void)
{
    t_termios		term;
//    t_termios       term_backup;

    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON);
    term.c_lflag &= ~(ECHO);
    tcsetattr(0, TCSANOW, &term);
    tgetent(0, getenv("TERM"));  
}

char **get_tab()
{
    int  fd;
    char **str;
    char *line;
    char *line2;

    str = NULL;
    line = NULL;
    line2 = ft_strdup("");
    if ((fd = open("minishell_history.txt", O_RDONLY)) < 0)
        return (NULL);
    while (get_next_line3d(fd, &line) > 0)
    {
        line2 = ft_strjoin(line2, line);
        line2 = ft_strjoin(line2, "\n");
    }
    str = ft_split(line2, '\n');
//    printf("%s\n", line2);
    return (str);
}

int     main(void)
{
    char    str[2000];
    int     len;
    int     fd;
    int     i;
    int     y;
    int     a;
    char    *line;
    char    *tmp;
    char    **history;

    len = 0;
    fd = 0;
    i = 0;
    y = 0;
    a = 0;
    line = NULL;
    tmp = ft_strdup("");
    history = NULL;
    init_term();
    tputs(save_cursor, 1, ft_putchar2);
    while (1)
    {
        line = ft_strdup("");
        if ((history = get_tab()))
        {
            i = 0;
            while (history[i])
                i++;
			y = i;
        }
        while ((len = read(0, str, 100)) != 0)
        {
//            printf("|%s|\n", str);
            if (!ft_strcmp(str, "\e[A"))
            {
                tputs(restore_cursor, 1, ft_putchar2);
                tputs(tgetstr("dl", NULL), 1, ft_putchar2);
//                write(1, "UP", 2);
                if (i != 0)
                {
                    i--;
                    ft_putstr(history[i]);
                }
            }
            else if (!ft_strcmp(str, "\e[B"))
            {
                if (line[0] != '\0' && a == 0)
				{
					tmp = line;
					a = 1;
				}
                tputs(restore_cursor, 1, ft_putchar2);
                tputs(tgetstr("dl", NULL), 1, ft_putchar2);
//                write(1, "DOWN", 4);
                if (i + 1 < y)
                {
                    i++;
                    ft_putstr(history[i]);
                }
                else if (tmp[0] != '\0')
                {
					printf("\n%s", tmp);
					a = 0;
				}
            }
            else if (!ft_strcmp(str, "\n"))
            {
                write(1, "\n", 1);
                break;
            }
            else
            {
                line = ft_strjoin(line, str);
                write(1, str, len);
            }
        }
        if ((fd = open("minishell_history.txt", O_WRONLY |
			O_APPEND | O_CREAT, 0644)) < 0)
            return (-1);
        if (line[0] != '\0')
        {
            write(fd, line, ft_strlen(line));
            write(fd, "\n", 1);
        }
//        printf("OK\n");
    }
    return (0);
}