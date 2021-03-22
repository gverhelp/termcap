#include "include/test.h"

int	ft_putchar2(int c)
{
	write(1, &c, 1);
    return (1);
}

int     main(void)
{
    char    str[2000];
    int     len;
    t_termios		term;
//    t_termios       term_backup;

    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON);
    term.c_lflag &= ~(ECHO);
    tcsetattr(0, TCSANOW, &term);
    tgetent(0, getenv("TERM"));

    tputs(save_cursor, 1, ft_putchar2);
    while (1)
    {
        while ((len = read(0, str, 100)) != 0)
        {
            if (!ft_strcmp(str, "\e[A"))
            {
                tputs(restore_cursor, 1, ft_putchar2);
                tputs(tgetstr("dl", NULL), 1, ft_putchar2);
                write(1, "UP", 2);
            }
            else if (!ft_strcmp(str, "\e[B"))
            {
                tputs(restore_cursor, 1, ft_putchar2);
                tputs(tgetstr("dl", NULL), 1, ft_putchar2);
                write(1, "DOWN", 4);
            }
//            else if (!ft_strcmp(str, "\n"))
//                break;
            else
                write(1, str, len);
        }
        printf("OK\n");
    }// while (ft_strcmp(str, "\n"));
    //write(1, "\n", 1);
    return (0);
}