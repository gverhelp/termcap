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
    while (ft_strcmp(str, "\4"))
    {
        tputs(save_cursor, 1, ft_putchar2);
        do
        { 
            len = read(0, str, 100);
            str[len] = 0;
            if (!ft_strcmp(str, "\e[A"))
            {
                tputs(restore_cursor, 1, ft_putchar2);
                tputs(tigetstr("ed"), 1, ft_putchar2);
                write(1, "previous", 8);
            }
            else if (!ft_strcmp(str, "\e[B"))
            {
                tputs(restore_cursor, 1, ft_putchar2);
                tputs(tigetstr("ed"), 1, ft_putchar2);
                write(1, "next", 4);
            }
            else if (!ft_strcmp(str, key_backspace) && !ft_strcmp(str, "\177"))
            {
                tputs(cursor_left, 1, ft_putchar2);
                tputs(tigetstr("ed"), 1, ft_putchar2);
            }
            else
                write(1, str, len);
        } while (ft_strcmp(str, "\n") && ft_strcmp(str, "\4"));
    }
    write(1, "\n", 1);
    return (0);
}