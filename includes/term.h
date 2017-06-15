#ifndef TERM_H
# define TERM_H

# include <unistd.h>
# include <signal.h>
# include "libft.h"

int			tc_sigstat(int reset);
void		tc_stop_signals();
void		tc_listen_signals();
void		tc_check_stdin();
int			tc_check_caps();


#endif
