#include "cub3d.h"
#include <sys/wait.h>

/* void	play_audio(char *audio_file)
{
	int		pid;
	char	**argv;

	argv = ft_calloc(5, sizeof(char *));
	argv[0] = ft_strdup("aplay");
	//argv[2] = ft_itoa(loudness);
	argv[1] = ft_strdup(audio_file);
	//argv[2] = ft_strdup("-v 1");
	pid = fork();
	// if (!pid)
	// {
	// 	execve("/usr/bin/aplay", argv, NULL);
	// 	exit(0);
	// }
	if (pid == 0)
	{
		if (execve("/usr/bin/aplay", argv, NULL) == -1)
		{
			perror("Error executing aplay");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("Error forking process");
	free(argv[0]);
	free(argv[1]);
	//free(argv[2]);
//	free(argv[3]);
	free(argv);
} */

void play_audio(char *audio_file)
{
	int			pid;
	char		**argv;
	extern char	**environ;

	argv = ft_calloc(5, sizeof(char *));
	argv[0] = ft_strdup("aplay");
	argv[1] = ft_strdup(audio_file);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		if (execve("/usr/bin/aplay", argv, environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
		waitpid(pid, NULL, WNOHANG);
	free(argv[0]);
	free(argv[1]);
	free(argv);
}

void	end_audio(void)
{
	int		pid;
	char	**argv;
	extern char	**environ;

	argv = ft_calloc(4, sizeof(char *));
	argv[0] = ft_strdup("killall");
	argv[1] = ft_strdup("-9");
	argv[2] = ft_strdup("aplay");
	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/killall", argv, environ);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0); // Wait for killall to complete
	free(argv[0]);
	free(argv[1]);
	free(argv[2]);
	free(argv);
}

/* void	play_audio(char *audio, int loudness)
{
	(void) audio;
	loudness++;
}

void	end_audio(void)
{
} */