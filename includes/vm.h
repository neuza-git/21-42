#ifndef VM_H
# define VM_H

# include <fcntl.h>
# include <string.h>
# include "env.h"
# include "ast.h"
# include "builtins.h"
# include "sys/wait.h"

# define VRDF_APPEND 0x8
# define VRDF_STDERR 0x4
# define VRF_SKIP 0x1
# define VRF_LAST_KO 0x10

typedef struct		s_vm
{
	t_envent		*env;
	t_envent		*local;
	t_ast			*ast;
	t_cmd			*work;
	int				reg;
}					t_vm;

void		vm_free(t_vm **vm);
t_vm		*vm_init(char **environ);
void		vm_loadast(t_vm *vm, t_ast *ast);
int			vm_readast(t_vm	*vm, t_ast *ast);
int			vm_isbuiltin(t_cmd *cmd, t_vm *vm);
int			vm_isextbuiltin(t_cmd *cmd);
void		vm_kill_cmds(t_cmd *cmd);

int			vm_fork_cmd(char *path, t_cmd *cmd, t_vm *vm,
int (*f)(t_cmd *cmd, int, t_vm *));
int			vm_fork(char *path, t_cmd *cmd, t_vm *vm,
int (*f)(t_cmd *cmd, int, t_vm *));
int			vm_fork_builtin(t_cmd *cmd, t_vm *vm,
int (*f)(t_cmd *cmd, int, t_vm *));

int			vm_fcb_piped(t_cmd *cmd, int pid, t_vm *vm);
int			vm_fcb_def(t_cmd *cmd, int pid, t_vm *vm);
int			vm_exec_redir(t_cmd *cmd, t_ast *redir, t_vm *vm);
int			vm_exec(t_cmd *cmd, int flags, t_vm *vm);

int			vm_exec_rdout(t_ast *rd);
int			vm_exec_rdin(t_ast *redir);
int			vm_open_dup(char *name, int fd, int flags);
void		vm_duplocals(t_envent *loc, t_token **toks);

void		ft_env(t_cmd *cmd, t_envent **ev, t_vm *vm);

#endif
