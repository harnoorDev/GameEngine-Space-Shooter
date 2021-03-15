# GameEngine-Space-Shooter
Space Shooting Game made in C++ using SDL (Simple DirectMedia Layer) framework and Visual Studio as the IDE

Used various sprites for the rocket, bullets, coins, hearts and explosions.
Added sound effects for firing bullets and when rocket is generating thrust.

Used Bullet shooting system, collision system, kinematic system by implementing 2D Game Engine Physics.


### Prerequisites

```
Visual Studio, SDL Framework, Some sprites to work with (included in this repo)

```
## How to Play 

``` 
Just run the sln file after downloading the repo as a zip, build and start the application without debugging.

```

### Steps to install SDL on Visual Studio 
**In-depth Tutorial available here : https://www.wikihow.com/Set-Up-SDL-with-Visual-Studio-2017#**
**or you can follow the below steps:**

```
1. Create a Visual Studio project as an 'empty project' (do NOT select console or other types)
2. Once created,  click 'Tools' ->NuGet Package Manager -> 'Manage nuGet packages for Solution'
3. In the 'nuGet' window that was opened, click the 'Browse' tab (by default, it would be in the 'installed tab'
4. Search for 'sdl2.nuget' . This should be listed as version '2.0.10'.  Click on sdl2.nuget
5. Now, in the right side of the screen, check mark on the project name, and click 'Install'. Press OK when asked to confirm.
6.Changing Properties of the project. Under solution explorer, right click on the project name and click 'Properties'
7. In the window that got opened, click Linker -> System
8. Under the 'SubSystem', select 'Windows'
9. Test the following code to see whether the SDL window opens (and automatically closes in few seconds):

If the program compiled and window opens, you are good to go through. 
If you have errors, you have to check whether you followed all the steps mentioned above.

Code (Create Test.cpp and copy/paste the following code to test it out)

#include "SDL.h"
int main(int argc, char* argv[])
{	
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow
       ("An SDL2 window", // window's title
	10, 25, // coordinates on the screen, in pixels, of the window's upper left corner
        640, 480, // window's length and height in pixels  
	SDL_WINDOW_OPENGL);

	SDL_Delay(5000); // window lasts 5 seconds
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
```

## Video demo
![Alt Text](https://media.giphy.com/media/BIFjLXlS2wHyuj3O6X/giphy.gif) 
![Alt Text](https://media.giphy.com/media/YAhFDKIMuVpviKyAYv/giphy.gif) 

## Authors
```
Harnoor Singh
```


