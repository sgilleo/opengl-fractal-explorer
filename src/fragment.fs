#version 410 core

out vec4 FragColor;

#define PI 3.14159265

uniform double xcenter;
uniform double ycenter;
uniform double scale;
uniform int max_iterations;
uniform int width;
uniform int height;

int mandelbrot_iterations(double x, double y)
{
   double real = 0.0f;
   double imag = 0.0f;
   int iterations = 0;
   double temp_real;

   while (iterations < max_iterations)
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


int julia_iterations(double x, double y, double julia_x, double julia_y)
{
   double real = julia_x;
   double imag = julia_y;
   int iterations = 0;
   double temp_x;

   while (iterations < max_iterations)
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
   double screen_ratio = double(width) / double(height);
   double x = xcenter + screen_ratio * (gl_FragCoord.x / width - 0.5) / scale;  
   double y = ycenter + (gl_FragCoord.y / height - 0.5) / scale;

   int iterations = mandelbrot_iterations(x, y);
   //int iterations = julia_iterations(x, y, -0.57, -0.57);
   
   float r, g, b;

   if (iterations == max_iterations)
   {
      r = 0.0f;
      g = 0.0f;
      b = 0.0f;
   }
   
   else
   {
      r = 0.5 + 0.5 * sin((mod(float(iterations) / max_iterations * 3 + 0.6, 1.0) + 0.85) * 2 * PI);
      g = 0.5 + 0.5 * sin((mod(float(iterations) / max_iterations * 3 + 0.6, 1.0) + 0.0) * 2 * PI);
      b = 0.5 + 0.5 * sin((mod(float(iterations) / max_iterations * 3 + 0.6, 1.0) + 0.15) * 2 * PI);
   }

   return vec4(r, g, b, 1.0f);
}

void main()
{
   FragColor = return_color();
}