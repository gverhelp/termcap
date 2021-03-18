#include "include/test.h"
#include <termios.h>

int ft_init_term()
{
    char    *term_type;
    int     ret;
    
    if (!(term_type = getenv("TERM")))
    {
        printf("getenv failed\n");
        return (-1);
    }
    ret = tgetent(NULL, term_type);
    if (ret == 0)
    {
        printf("Pas assez d'infos\n");
        return (-1);
    }
    if (ret == -1)
    {
        printf("Pas accès au database\n");
        return (-1);
    }
    return (0);
}

void		raw_term(void)
{
	t_termios		term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
}

int main(int argc, char **argv)
{
    char    *keyup;
    char    *line;
    int     ret;
    int     fd;
    char    str[120];
    int     len;

    (void)argc;
    (void)argv;
    (void)line;  
    (void)fd; 
    (void)keyup;
    (void)len;
    (void)str;
    line = NULL;
    ft_bzero(str, 0);
    raw_term();
	if ((ret = ft_init_term()) == -1)
      	return (-1);
//    keyup = key_up;
	printf("START\n");
    while (1)
    {
		line = ft_strdup("");
		tputs(save_cursor, 1, putchar);
        while ((len = read(0, str, 100)) != 0)
        {
//        printf("|%s|\n", str);
            if (!ft_strcmp(str, "\e[A"))
            { 
				tputs(restore_cursor, 1, putchar);
				tputs(tgetstr("ed", NULL), 1, putchar);
				write(1, "UP", 3);
				break ; 
			}	
            else if (!ft_strcmp(str, "\e[B"))
            { 
				tputs(restore_cursor, 1, putchar);
				tputs(tgetstr("ed", NULL), 1, putchar);
				write(1, "DOWN", 5);
				break ; 
			}	
            else if (!ft_strcmp(str, "\e[D"))
			{
				write(1, "DEL", 3);
				tputs(restore_cursor, 1, putchar);
				tputs(cursor_left, 1, putchar);
				tputs(tgetstr("ed", NULL), 1, putchar);
			}
            else if (!ft_strcmp(str, "\n"))
        	{
				write(1, "\n", 1);
				break ;
			}
            else
            {
                line = ft_strjoin(line, str);
                write(1, str, len);
            }
            ft_bzero(str, 0);
        }
        if ((fd = open("minishell_history.txt", O_WRONLY |
			O_APPEND | O_CREAT, 0644)) < 0)
            return (-1);
        if (line[0] != '\0')
        {
            write(fd, line, ft_strlen(line));
            write(fd, "\n", 1);
        }
    }
    printf("|%s|\n", line);

/*    while (get_next_line3d(STDIN_FILENO, &line) > 0)
    {
        if ((fd = open("minishell_history.txt", O_WRONLY |
			O_APPEND | O_CREAT, 0644)) < 0)
            return (-1);
        if (line[0] != '\0')
        {
            write(fd, line, ft_strlen(line));
            write(fd, "\n", 1);
        }
//        tputs(tgetstr("up", NULL), 1, ft_outc);
    } */
    close(fd);
    return (ret);
}



//    keyup = tgetstr("ku", NULL);
//    tputs(tgoto(keyup, 5, 5), 1, putchar);



//    initscr();
//    keypad(stdscr, TRUE);
//    noecho();
//    cbreak();
//    while (getch() != 27)
//    {
//    }
