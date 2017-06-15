#include "engine.h"
#include "term.h"

char	*en_getline()
{
	char	*line;
	int		ret;

	line = NULL;
	ft_putstr("$>");
	if ((ret = get_next_line(0, &line)) > 0)//a voir un gros bug si on depasse 8086 chars
	{
		if (ft_strlen(line) >= CMD_MAX)
		{
			ft_putstr("This shell can not interpret commands of more than ");
			ft_putnbr(CMD_MAX);
			ft_putendl(" chars.");
			free(line);
			line = NULL;
			return (ft_strdup("  "));
		}
		return (line);
	}
	if (line)
		free(line);
	return (NULL);
}
