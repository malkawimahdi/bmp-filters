# BMP-filters

This repository, contains the program that allows you to manipulate files ending in ".bmp" by using a selection of filters that can be applied to the original image to create an output.

## Filters

**Grayscale:** Takes an input image and turns the image into a black-and-white, by averaging the red, green and blue (RGB) values for a given pixel, which has the additional benefit of retaining the original image brightness.

**Reflection:** Takes an input image and reflects the image horizontally. The resulting image is what you would get by placing the original image in front of a mirror.

**Blur:** Takes an input image and implements a box blur. Box blur is implmented such that by taking each pixel and, for each colour value, giving it a new value by averaging the colour values of the neighbouring pixel where applicable.

**Edges:** Takes an input image and applies the sobel operator on the given image. Like **Blur** edge detection works by taking each pixel, and modifying it based on a 3x3 matrix that surronds a given pixel. However in this scenario, we use the Sobel operator to comput the new value of each pixel by taking a weighted sum of the values for the surronding pixels. Since edges can occur in both x and y directions within an image, we use two different "kernels" to compute the edges in a particular direction for each colour channel for a given pixel. Each channel for a given pixel will be processed using the Gx and Gy kernels, meaning that each pixel will have six(6) values. 

If 'I' is the source image, then we can apply Gx and Gy to the image: 

$$Gx=\begin{pmatrix}
+1&0&-1\\
+2&0&-2\\
+1&0&-1&\end{pmatrix} * I $$

$$Gy=\begin{pmatrix}
+1&+2&+1\\
 0&0&0\\
-1&-2&-1&\end{pmatrix} * I $$

In order to combine the values for a given channel after using the kernels Gx and Gy, we can: 

$$O=\sqrt{Gx^2 + Gy^2}$$

which generates 'O' the output which squares the result for each kernel, then adds that result and finally takes the square root to normalise the result. 
