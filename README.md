Song repository managment service with a console user interface featuring authorization, songs repo, liked songs, recommendations and settings to choose different recommendation engine. 

**Requirments & how to build**
In order to build and run the project you need to have:

* IDE like Visual Studio Code that supports C++
* GCC (GNU Compiler Collection)
* CMake build system

Once you have sucessfuly installed CMake run the following command to build:

```
cmake -B build - S.
cmake --build build --config Release
```

Once built, the libraries should be fetched and the program .exe file is stored at ./build/Release subfolder

To run the program simply open .exe file in your terminal:

```
./build/Release/lviv_music.exe
```

To run unit tests, open the following file:

```
./build/Release/lviv_music_tests.exe
```
