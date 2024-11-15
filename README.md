# OpenGL Fractal Explorer

A simple interactive fractal renderer (Mandelbrot & Julia sets) made up using pure C++ and GLSL graphic shaders.

## Building the code

To compile the project in Windows use this command:

```
make
```
And run with:
```
cd .\src\
.\main.exe
```
Make sure that glfw3.dll is in the same directory as the executable file.

# Controls

- **W, A, S, D** or arrow keys for moving up, down, left and right.
- **Left Ctrl and Left Shift** for zooming in and out.
- **Q and E** for increasing and decreasing the maximum iterations.
- **Esc** to quit the app. 

# Warning
If you try to render a frame that takes more than a few seconds to calculate Windows will think the GPU stopped responding, so it will decide to shut down the app.
If you desire to extend the GPU Timeout Detection look for tdr timeout.