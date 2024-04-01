3) Benchmark your program on the LCC3 cluster, document your results and add them to the comparison spreadsheet linked on Discord. How would you improve program performance?
    - If you are forced to use a single thread, you can improve performance by using a more efficient algorithm. For example, the current algorithm calculates runes in O(n^2) time, where n is the number of pixels in the image. 
    - You could also improve performance by using a more efficient data layout. For example, it makes a difference whether you iterate over the pixels in row-major or column-major order. In most cases, it is more efficient to iterate over the rows first(in c), because the memory is stored in row-major order(better caching). 
4) Can you think of a way to parallelize this algorithm?
    - See mandelbrot_fast.c for a parallel implementation of the Mandelbrot set calculation using OpenMP.
    - By adding #pragma omp parallel for, to the outer loop, the program will automatically parallelize the calculation of the Mandelbrot set and the image will still look the same. 
    - Adding #pragma omp parallel for to the inner loop will increase the performance, but not as much as the outer loop. 
    - And using at both loops will not increase the performance, further than just using it at the outer loop.
