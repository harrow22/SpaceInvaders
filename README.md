# 👾 SpaceInvaders 👾
This is an emulator of the 1978 Taito arcade machine [Space Invaders](https://en.wikipedia.org/wiki/Space_Invaders) running on top of my [Intel8080 core](https://github.com/harrow22/Intel8080). It comes with color, sound, and high score persistence!
<p align="center">
  <img alt="Spacefight Invaders attract mode gif" src="https://raw.githubusercontent.com/harrow22/SpaceInvaders/master/examples/attract_mode.gif" height="400" />
</p>

# Controls
| Key         | Action                            |
|-------------|-----------------------------------|
| C           | deposit credits                   |
| 1           | start the game in one-player mode |
| 2           | start the game in two-player mode |
| left arrow  | move left                         |
| right arrow | move right                        |
| space       | shoot                             |
| T           | tilt the machine                  |

# Installation
I've provided an installer for Windows on the [releases](https://github.com/harrow22/SpaceInvaders/releases) page [(or build from source)](#building-from-source). After installation, you will need to add the [ROMs](assets/roms) and [sound files](assets/sound) to the assets folder. Then to run the emulator, simply double-click on `SpaceInvaders.exe`.

> [!NOTE] 
> If you're using the installer, the default directory will be `C:\Program Files\`, which will require you to open the `.exe` in administrator mode everytime if you want scores to save. I would just recommend installing somewhere else.

### Changing the behavior of the emulator
1) Open a terminal, then type out the path to where you installed `SpaceInvaders.exe`:
   ```
   path/to/SpaceInvadersEmulator/bin/SpaceInvaders.exe <PARAMETERS...>
   ```  
2) Replace `<PARAMETERS...>` with:

   | Parameter         | Range        | Default | Description                                               |
   |-------------------|--------------|---------|-----------------------------------------------------------|
   | `-lives <n>`      | [3,6]        | 3       | changes the number of lives you start with                |
   | `-extra_life <n>` | 1500 or 1000 | 1500    | changes the amount of points needed to gain an extra life |

   For example, if I wanted to start the game with 5 lives instead of 3, I would run: <br/>
   `'~\Downloads\Space Invaders Emulator\bin\SpaceInvaders.exe' -lives 5`

## Building from Source
### Dependencies
* **A c++ compiler**
* **CMake version 3.26+**
* **CMake build generator**
* **[SDL2](https://github.com/libsdl-org/SDL)**
* **[SDL_mixer](https://github.com/libsdl-org/SDL_mixer)**

### With CMake
1) Download the source code
    ```
    git clone https://github.com/harrow22/SpaceInvaders.git
    cd SpaceInvaders
    ```
2) **Optional:** If you want, you can customize the colors of the emulator by changing the color code constants defined in [Display.h](src/components/Display.h).  
3) Build
    ```
    cmake -S . -B build -G <generator> -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_PREFIX_PATH <path/to/sdl>
    cd build
    cmake --build . --config Release
    cmake --install . --config Release --prefix <path/to/install_directory>/SpaceInvadersEmulator/
    ```
4) Add the [ROMs](assets/roms) and [sound files](assets/sound) to the assets folder (in the install directory).
5) Run the executable

# Resources
[Computer Archeology Space Invaders](https://computerarcheology.com/Arcade/SpaceInvaders/)
