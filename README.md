# LSDetris
The best and most delirious tetris that will ever be made!

## Build
To build this piece of software you need cmake... and many other things. Yeah. And gcc of version 10 at least for linux builds. This project uses C++20 so check your compiler.

So... some piece of instructions.

This project uses vcpkg to manage project dependencies - install it first.
You can easily do it using install-vcpkg.sh script for linux and install-vcpkg.bat for windows.
Their contents (and the contents of the other scripts) is pretty poor so, please, forgive me my modest knowledge of shell scripting and even more modest desire to fuck with it. But this shit seems to work.

Next you must install dependencies themselves. For that you use install-deps script. It will install entt, glfw, glm, glew and openal-soft packages.

Next you must configure this godlike piece of software/ For that use use configure script: it simply calls some fancy cmake command that will set
vcpkg toolchain file (this is very important). And it also uses hardcoded version of a gcc compiler (I'm a very bad person). Scripts are pretty simple so feel free to modify them.

To build the all-dancing, all-singing piece of software you simple call cmake --build build ... and that's it! You're fucked! I've stolen all yours and your gf's nudes (; . See you in LeakedIn.

!!!Warning!!! Check your installed libraries (like ALSA libraries, for example) before building! I was missing sound on Ubuntu because of missing ALSA installation. You can get openal-soft separately and try to build it to have ability to check configuration and build output.

This is the very basic version of README
