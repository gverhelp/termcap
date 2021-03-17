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

int			ft_outc(int c)
{
//    int fd;

    
//    fd = open("minishell_history.txt", O_RDONLY);
//    read(fd, )
    (void)c;
	write(1, "salut\n", 6);
	return (0);
}

void		raw_term(void)
{
	t_termios		term;
	int				fd;

	fd = open("/dev/tty", O_RDONLY);
	if (fd == -1)
		fd = 0;
	tcgetattr(fd, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(fd, TCSANOW, &term);
	if (fd > 0)
		close(fd);
}

void		default_term(void)
{
	t_termios		term;
	int				fd;

	fd = open("/dev/tty", O_RDONLY);
	if (fd == -1)
		fd = 0;
	tcgetattr(fd, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(fd, TCSANOW, &term);
	if (fd > 0)
		close(fd);
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
    if ((ret = ft_init_term()) == -1)
        return (-1);
//    keyup = tgetstr("ku", NULL);
//    keyup = key_up;
    while (1)
    {
        raw_term();
        while (1)
        {
            len = read(0, str, 100);
//        printf("|%s|\n", str);
            if (!ft_strcmp(str, "\e[A"))
            {
                printf("OK\n");
                tputs(tgetstr("cd", NULL), 1, putchar);
            }
            if (!ft_strcmp(str, "\e[B"))
            {
                tputs(tgetstr("cd", NULL), 1, putchar);
            }
            if (!ft_strcmp(str, "\eH"))
            {
                printf("OK\n");
                tputs(tgetstr("kd", NULL), 1, putchar);    
            }
            if (!ft_strcmp(str, "\n"))
                break ;
            else
            {
                if (!line)
                    line = ft_strdup(str);
                else
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
        write(1, "\n", 1);
        default_term();
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
    default_term();
//    close(fd);
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