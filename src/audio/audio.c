#include "cub3d.h"
#include <sys/wait.h>

/**
 * @brief Detects the appropriate audio player command based on the system platform
 *
 * This function determines which command-line audio player to use depending
 * on the operating system:
 * - On macOS: "afplay"
 * - On other systems: "aplay"
 *
 * @return A newly allocated string containing the audio player command.
 * The caller is responsible for freeing this memory.
 */
char	*detect_audioplayer(void)
{
	char	*audio_player;

	#ifdef __APPLE__
		audio_player = ft_strdup("afplay");
	#else
		audio_player = ft_strdup("aplay");
	#endif
	return (audio_player);
}

/**
 * @brief Plays an audio file using an available audio player
 * 
 * This function plays the specified audio file by detecting an available
 * audio player on the system, and executing it in a separate child process.
 * The parent process continues execution without waiting for the audio
 * playback to complete (non-blocking).
 * 
 * @param audio_file Path to the audio file to be played
 * 
 * @note The function automatically detects an appropriate audio player
 *       using the detect_audioplayer() function.
 * @note Memory allocated during execution is properly freed before returning.
 * @note If fork() or execve() fails, appropriate error messages are displayed.
 */
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

/**
 * @brief Terminates the audio player process
 * 
 * This function terminates any running audio player process by:
 * 1. Detecting the currently used audio player
 * 2. Creating a child process using fork()
 * 3. Executing killall command with -9 signal on the detected audio player
 * 4. Waiting for the child process to complete
 * 5. Cleaning up allocated memory
 * 
 * The function uses execve() to run the killall command and properly
 * frees all allocated memory to prevent leaks.
 * 
 * @note This function assumes killall binary is located at "/usr/bin/killall"
 */
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