#include <engine.h>
#include <shell.h>

int		main(void)
{
	t_engine en;
	char	*cmd;
	char	buf[1024];

	tcgetattr(0, &en.default_term);
	ft_set_term();
	tgetent(buf, getenv("TERM"));
	en.vm = malloc(sizeof(t_vm));
	en.vm->hs = NULL;
	en.rest = NULL;
	en.cp = NULL;
	en.tfd = 1;
	//while ((cmd = get_line(&en, 0)))
	if ((cmd = get_line(&en, 0, NULL)))
	{
		if (cmd && cmd[0])
		{
			ft_putstr("doing the cmd: ");
			ft_putstr(cmd);
			ft_putchar('\n');
		}
	}
	tcsetattr(0, TCSANOW, &en.default_term);
	return (0);
}
