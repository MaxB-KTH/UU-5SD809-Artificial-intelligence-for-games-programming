Examples of free C++ compilers with multiple platform support:

https://visualstudio.microsoft.com/downloads/
https://gcc.gnu.org

**********
Example: Crash course for using Visual C++
**********
Open Visual Studio
File -> New -> Project
[Click "Browse"] and select location for the C++ project
Installed -> Templates -> Visual C++ -> General -> Empty Project + [Click "OK"]
<An empty C++ project should now exist>
[Right-click "Source Files"] -> Add -> Existing Item + [Select the .cpp and .h-files under AT/A1/GameOfLife/Console/]
[Compile and run]: [Click "Local Windows Debugger"] + ["Yes"] 
<The application should now be running>
Until the method void Game::UpdateFrontBuffer() is completed by the student, all rendered frames could look the same...