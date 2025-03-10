#include "cub3d.h"
#include <sys/wait.h>

char	*detect_audioplayer(void)
{
	char	*audio_player;

	#ifdef __APPLE__
		aud_play = ft_strdup("afplay");
	#else
		audio_player = ft_strdup("aplay");
	#endif
	return (audio_player);
}

void play_audio(char *audio_file)
{
	int			pid;
	char		**argv;
	extern char	**environ;
	char		*audio_player;
	char		*path;

	audio_player = detect_audioplayer();
	argv = ft_calloc(3, sizeof(char *));
	argv[0] = ft_strdup(audio_player);
	argv[1] = ft_strdup(audio_file);
	path = ft_strjoin("/usr/bin/", audio_player);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
		waitpid(pid, NULL, WNOHANG);
	free(audio_player);
	free(argv[0]);
	free(argv[1]);
	free(argv);
	free(path);
}

void	end_audio(void)
{
	int		pid;
	char	**argv;
	extern char	**environ;
	char		*audio_player;

	audio_player = detect_audioplayer();
	argv = ft_calloc(4, sizeof(char *));
	argv[0] = ft_strdup("killall");
	argv[1] = ft_strdup("-9");
	argv[2] = ft_strdup(audio_player);
	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/killall", argv, environ);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	free(audio_player);
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