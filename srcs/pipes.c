#include "../includes/sh.h"

void		do_pipes(t_lexit *list, t_env *env, t_sh *sh)
{
	pid_t 	pipid;
	int 	pipefd[2];
	int 	status;

	pipe(pipefd);
	pipid = fork();
	list->left->is_pipe = 1;
	if (pipid == 0)
	{
		if (list->left)
			dup2(pipefd[1], list->left->fdsrc);
		close(pipefd[0]);
		execs_deep(list->left, env, sh);
	}
	else
	{
		dup2(pipefd[0], sh->fd.saved_in);
		close(pipefd[1]);
		execs_deep(list->right, env, sh);
		waitpid(pipid, &status, 0);
	}
}
