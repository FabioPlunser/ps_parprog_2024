1) For both implementations, give a function f to calculate the number of data cache read misses for the matrix size n and the cache line size s in an 8-way set-associative cache. Assume that all variables are initialized appropriately (the matrix elements are of type int32_t) and that the matrices are stored in contiguous memory in row-major order. Additionally, the matrices are too large to store them entirely in the cache (n >> s)
    - In Theory there should be more cache misses in the column-wise data layout implementation. 
2) Use the two snippets to implement two versions of the Hadamard product.
    - Done. 
3) Log into the LCC3 cluster and analyze the cache behavior of the implementations using `cachegrind` (e.g. `valgrind --tool=cachegrind <your program>`) and `perf` (e.g. `perf stat -e LLC-load-misses -e LLC-store-misses <your program>`) Can you validate your theoretical findings? Compare the results of both tools.
    - See figure result.png.
    - The data confirms the theoretical findings. The column-wise implementation has more cache misses than the row-wise implementation. Most of the cache miss difference is in the D1 cache.
    - There is also a clear difference in execution time due to the cache misses. 