1) For both implementations, give a function f to calculate the number of data cache read misses for the matrix size n and the cache line size s in an 8-way set-associative cache. Assume that all variables are initialized appropriately (the matrix elements are of type int32_t) and that the matrices are stored in contiguous memory in row-major order. Additionally, the matrices are too large to store them entirely in the cache (n >> s)
    - The formula for the row-wise implementation is: f = 2 * n (n/(s/4)), where the both parentheses are rounded up to the nearest integer.
    - First we need the number of elements in a cache line: s/4.
    - Then we need the number of cache lines in a row: n/(s/4).
    - Finally we need the number of needed cache lines in the matrix: n * n/(s/4).
    - And the x2 is because we have to read from the a and b matrix.
    - s needs to be in bytes.
    - The formula for the colum-wise implementation is: f = 2 * n ^ 2.
    - Here its a bit simpler. Because we have to read every element of the matrix, we have to read n^2 elements. And again we have to read from the a and b matrix.
    - s needs to be in bit.
2) Use the two snippets to implement two versions of the Hadamard product.
    - Done. 
3) Log into the LCC3 cluster and analyze the cache behavior of the implementations using `cachegrind` (e.g. `valgrind --tool=cachegrind <your program>`) and `perf` (e.g. `perf stat -e LLC-load-misses -e LLC-store-misses <your program>`) Can you validate your theoretical findings? Compare the results of both tools.
    - As expected, the row-wise implementation has a lower number of cache misses than the column-wise implementation. For n == 1000 the row-wise implementation has 126,000 cache misses and the column-wise implementation has 2,000,000 cache misses.
    - There is also a clear difference in execution time due to the cache misses. 
    - See figure result.png.