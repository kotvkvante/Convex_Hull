Implementation of the Graham scan using C, OpenGL and SDL2.

Compile for linux with gcc:
    gcc -g -I src/SideSrc/glad/include src/main.c src/Core/Core.c src/Graph/Graph.c src/Graphics/Graphics.c src/Input/Input.c src/Math/GrahamAlg.c src/Math/Matrix.c src/SideSrc/glad/src/glad.c -lm -lSDL2 -lSDL2main -lGLU

Linker options (for windows):
  -lmingw32 -lSDL2main -lSDL2 -lopengl32

## Usage
  1) Left click to set point.
  2) Press "1" to see list of placed points.
  3) Press "2" to execute algorithm.
  4) "R" to reset.
  5) Thanks!

## Video

https://user-images.githubusercontent.com/76774437/176943992-42b12bd0-af9f-40dd-9063-e0ccb0be1253.mp4
