To load the models and shaders correctly you must change the PATHTOSHADER
and PATHTOMODELS macro inside game.cpp. For an example of how to do this see
our examples in the source code. Additionally we use ASSIMP to load models in
our game. The dependencies folder contains all the libraries that you will need.
You may need to (in MSVC) change the include and library directories. Or use
CMake to remake the binaries. Once the program is compiled then you will likely
get an error saying "This program cannot start because assimp-vc140-mt.dll is
not installed". Once you get that error then locate your binary file
(either Debug or Release) and place the included dll file inside that folder.