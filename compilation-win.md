# Intro
For this program to be able to compile in windows, 
I had to painfully research a lot of websites in order 
to find a method that worked for me, and now I will share 
it so that you don't have the same problems as I did

# How to compile for windows
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

In ...


