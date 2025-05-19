# AUDIO

## General flow
Well, this is not even a bonus, but the idea seems neat. The idea basically is to  detect the system running the program, if Apple system then use the audio player `afplay`, if linux, then `aplay`.

Then the `play_audio` function just runs a child process that plays a specified track (set in the defines.h header file) using that audio player.

The `end_audio` function is just called whenever the program is terminated by using killall to send SIGTERM to kill the audio playback. Just a kill may probably suffice, but I dont really remember anymore why I went with killall, presumably I was thinking of running two different audio tracks but this experiment results in nothing unfortunately. 

The main drawback of this rudimentary implementation is namely: The audio only plays once, and before I found out how to play it on repeat, I was already moving on to other parts of the project.

