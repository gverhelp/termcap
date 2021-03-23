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
    char *fri;

    str = NULL;
    line = NULL;
    line2 = ft_strdup("");
    if ((fd = open("minishell_history.txt", O_RDONLY)) < 0)
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
    free(line);
    str = ft_split(line2, '\n');
    free(line2);
//    printf("%s\n", line2);
    return (str);
}

int     main(void)                                            //////// GOOD MAIN ////////////////
{
    char    str[2000];
    int     len;
    int     fd;
    int     i;
    int     y;
    int     a;
    char    *line;
    char    **history;
    char    **add;
    char    *fri;
    int     flag;
    int     count;

    (void)flag;
    (void)count;
    len = 0;
    fd = 0;
    i = 0;
    y = 0;
    a = 0;
    flag = 0;
    count = 0;
    line = NULL;
    history = NULL;
    init_term();
//    tputs(save_cursor, 1, ft_putchar2);
    if ((fd = open("minishell_history.txt", O_WRONLY |
			O_APPEND | O_CREAT, 0644)) < 0)
            return (-1);
    printf("START\n");
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
//            printf("%s\n", str);
            if (!ft_strcmp(str, "\e[A"))
            {
                flag = 1;
                if (a == 0)
				{
                    if (line[0] == '\0')
                    {
                        add = malloc(sizeof(char*) * 2);
                        add[0] = ft_strdup("");
                        add[1] = NULL;
                    }
                    else               
                        add = ft_split(line, '\n');
					history = ft_tabjoin(history, add);
                    y++;
					a = 1;
				}
                if (i != 0)
                {
                    i--;
//                    tputs(restore_cursor, 1, ft_putchar2);
                    tputs(tgetstr("dl", NULL), 1, ft_putchar2);
                    tputs(history[i], 1, ft_putchar2);
                    line = ft_strdup(history[i]);
                }
            }
            else if (!ft_strcmp(str, "\e[B"))
            {
                flag = 1;
                if (i + 1 < y)
                {
                    i++;
//                    tputs(restore_cursor, 1, ft_putchar2);
                    tputs(tgetstr("dl", NULL), 1, ft_putchar2);
                    tputs(history[i], 1, ft_putchar2);
                    line = ft_strdup(history[i]);
                }
            }
            else if (!ft_strcmp(str, "\n") || ((!ft_strcmp(str, "\n[A") || !ft_strcmp(str, "\n[B")) && flag == 1))
            {               
                write(1, "\n", 1);
                flag = 0;
                a = 0;
                break;
            }
            else if (!ft_strcmp(str, key_backspace)) // || (!ft_strcmp(str, "[A")) || (!ft_strcmp(str, "[B")))
			{
                fri = ft_substr(line, 0, ft_strlen(line) - 1);
                free(line);
                line = ft_strdup(fri);
                free(fri);
				tputs(cursor_left, 1, ft_putchar2);
				tputs(tgetstr("dc", NULL), 1, ft_putchar2);
			}
            else if (ft_strcmp(str, "\e[D") && ft_strcmp(str, "\e[C"))
            {
                fri = line;
                line = ft_strjoin(line, str);
                free(fri);
                write(1, str, len);
            }
        }
//        write(1, "OK", 2);
        if (line[0] != '\0')
        {
            write(fd, line, ft_strlen(line));
            write(fd, "\n", 1);
        }
//        printf("OK\n");
    }
    return (0);
}