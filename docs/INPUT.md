# INPUT

## General flow
The input module here is basically just a mini-module separated only to make things look more organized than they actually are, because otherwise it would also makes sense to put the key hooks in the init module.

Nothing much happens here other than the usual system checking (like in the audio module) to setup key mapping in apple and linux systems.

### Press & release
The key press and release basically registers as setting a "flag" either on (press) or off (release). Of course, it is also here that the primary mean of exiting the program is set. This is done by mapping the ESC key to a destroy function or by pressing the 'X' on the corner of the program window.