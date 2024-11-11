#version 330 core

in vec4 gl_FragCoord;
out vec4 FragColor;

#define MAX_ITERATIONS 300

uniform float xcenter;
uniform float ycenter;
uniform float scale;
uniform int width;
uniform int height;

int mandelbrot_iterations(float x, float y)
{
   float real = 0;
   float imag = 0;
   int iterations = 0;
   float temp_real;

   while (iterations < MAX_ITERATIONS)
   {
      temp_real = real;
      real = real * real - imag * imag + x;
      imag = 2.0 * temp_real * imag + y;

      if (real * real + imag * imag > 4.0)
      {
         break;
      } 

      iterations++;
   }
   return iterations;
}


int julia_iterations(float x, float y, float julia_x, float julia_y)
{
   float real = julia_x;
   float imag = julia_y;
   int iterations = 0;
   float temp_x;

   while (iterations < MAX_ITERATIONS)
   {
      temp_x = x;
      x = x * x - y * y + real;
      y = 2.0 * temp_x * y + imag;

      if (x * x + y * y > 4.0)
      {
         break;
      } 

      iterations++;
   }
   return iterations;
}
vec4 return_color()
{
   float x = xcenter + (gl_FragCoord.x / width - 0.5) / scale;  
   float y = ycenter + (2 * gl_FragCoord.y - height) / 2 / width / scale;

   //int iterations = mandelbrot_iterations(x, y);
   int iterations = julia_iterations(x, y, -0.57, -0.57);
   float color = float(iterations) / MAX_ITERATIONS;
   return vec4(color, color, color, 1.0f);
}

void main()
{
   FragColor = return_color();
}