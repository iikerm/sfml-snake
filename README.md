# Snake game in C++ using SFML library

This is a simple version of the popular game 'snake' that I 
made to learn how to use classes in C++, along with the SFML graphics library.

It is currently only compiled for Windows as `snake.exe` and for Ubuntu/Linux as `snake`.

# Game preview

![imagen](https://github.com/iikerm/sfml-snake/assets/151840754/b1f2af64-9d38-450f-a420-a2d2debc97f9)

---

# Compilation for windows using visual studio and vcpkg
For this program to be able to compile in windows, 
I had to painfully research a lot of websites in order 
to find a method that worked for me, and now I will share 
it so that you don't have the same problems as I did

# How to compile for windows (dynamically)
First of all, we are going to install **Visual Studio 2022** and 
the **vcpkg** packet manager, which have a nice integration. 
To install the latter, you will need to install [**git for windows**](https://git-scm.com/download/win), 
I followed a very good [tutorial](https://learn.microsoft.com/es-es/vcpkg/get_started/get-started-msbuild?pivots=shell-cmd) 
by microsoft which explains step by step 
how to install vcpkg and configure it to work beside visual studio, however for this we will only need point nº1 of the tutorial.

Before continuing, you must add vcpkg to your path (or it is recommended to do so at least). Do it by using: 

 `Right-click on windows icon > System > Advanced System Configuration > Environment Variables > Double-click Path` 
  
  Then you can simply copy the path to your vcpkg installation (folder where vcpkg.exe is found) into the last row

After having everything installed, we can follow the next steps:

1. Create a new project in visual studio using the `Console App` template and name it however you want. It is important to specify that we want the solution and the project in the same directory
2. Once inside the project, you can erase the contents of the initial .cpp file (which is just a hello world program) and write/paste your code that uses SFML.
3. Now you can go to `Tools > Command Line > Developer Command Line` in visual studio
4. Run the following commands:
- `vcpkg new --application`
- `vcpkg add port sfml`
 
  What each one of these commands does is explained in the vcpkg install tutorial mentioned above (part nº2)
5. Now you can close the console and go to the project's properties in visual studio, where you must do the following:
- `Configuration properties > vcpkg > use vcpkg manifest` set it to yes

Now your project is ready to be compiled dynamically (to execute the .exe, the dll files must be in the same folder)

# How to compile the SFML file statically

In case that you want to link the libraries statically (.exe file weighs more, but only the exe needed to run the program), there are a few additional steps to take:
1. In the project's properties in visual studio, go to `Configuration properties > vcpkg` :
- Set the `use static libraries` option to yes
- [optional] Set the `vcpkg configuration` option to debug or release according to your preferences
2. Then go to `Configuration properties > C/C++ > Preprocessor > Preprocessor definitions` and click on edit. Then at the end add the following flag: `SFML_STATIC`
3. Finally, go to `Configuration properties > Linker > Input > Additional dependencies` and click on edit. At the end you must add the following elements at the end depending on what sfml libraries you are using:
- SFML Graphics: `opengl32.lib` and `freetype.lib`
- SFML Window: `opengl32.lib`, `winmm.lib` and `gdi32.lib`
- SFML System: `winmm.lib`
> They don't need to be repeated, it is enough with adding each one a single time. They must each be added on their own in a new line. You can visit [this](https://www.sfml-dev.org/tutorials/2.6/start-vc.php) page to see a full list of dependencies for the rest of the SFML libraries.

Now your project can be compiled statically!

# How to remove the console from the SFML program

For the final part, because most programs that use SFML are games, and having a black console behind a game does not inspire trust in a game, the following are some steps to prevent the console from executing when your program (.exe file) runs:

1. Inside visual studio, go to your project's properties and then set `Configuration properties > Linker > System > Subsystem` to the option `Windows (/SUBSYSTEM:WINDOWS)`
2. Because doing only the step above will result in a compilation error, you must now change your program's main function name from `int main(int argc, char *argv[])...` to `int WinMain(int argc, char *argv[])...`

After doing these steps, the program can be compiled without a command window popping up in your game's background

>Take into account that these last two steps are not mandatory (e.g. You can link dynamically and remove the console window without linking statically,
> you can just link the program statically, without removing the console etc.)

---

# How to use the sfml++ 'compiler' in Ubuntu
First of all, you will need to have the sfml library installed. This can be achieved by using:

 `sudo apt install libsfml-dev`

When you compile C++ code files that use any of the headers from the
SFML library, you always need to include various dependencies, so to make this part
a bit simpler to write, I made my own program that uses the g++ compiler
and some arguments that can be passed to it in order to make compilation commands simpler to write.

To compile the file `snake.cc`, for changing the game's colors for example, the following command can be copied:

`g++ snake.cc -o snake -lsfml-window -lsfml-system -lsfml-graphics`

  
Or you can also use my program as follows:
 
`./sfml++ -n <filename.cc> -o <execname> -<sfml_options>`
 
The -<sfml_options> tag can be one or more of the following:
> 
> SFML system header (-lsfml-system): `-sys`
> 
> SFML window header (-lsfml-window): `-win`
> 
> SFML graphics header (-lsfml-graphics): `-gra`
> 
> SFML network header (-lsfml-network): `-net`
> 
> SFML audio header (-lsfml-audio): `-aud`
> 
> OpenGL library (-lGL): `-opengl`
 
Therefore to compile the file `snake.cc` we can use:
 
`./sfml++ -n snake.cc -o snake -sys -win -gra`

