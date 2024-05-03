# Description
> Compilers often perform dependence analysis as a pre-step in order to safely perform optimizations such as vectorization in a second step. In this exercise, we will look at the first step only, namely compiler capabilities and reporting.

# Task 1
> Compile the given program [analysis.c](analysis.c) with gcc 12.2.0 (`module load  gcc/12.2.0-gcc-8.5.0-p4pe45v`) and the flags `-O2 -ftree-vectorize -fopt-info-vec-all-internals`.
- Done, see [Makefile](Makefile) + [output](output.txt)

# Task 2
> Examine the output. What information about dependence analysis can you find in the output? Can you identify any information pointing to successful or unsuccessful vectorization? Does the compiler perform any analysis beyond checking for dependencies and semantic correctness? What are your findings?

In the output, we can find following information about the different loops:
## Loop 1(10-12)
> A Cost Model analysis was performed  
> The loop was vectorized using the V4SI vectorization factor (16 bytes)  
> Means 8 instructions were generated for the vectorized loop(not sure here)   
## Loop 2(14-16)
> not vectorized: more than one data ref in stmt: MEM <unsigned char[4096]> [(char * {ref-all})&b] = MEM <unsigned char[4096]> [(char * {ref-all})&a];  
> That means the loop could not be vectorized because of possible alias involving gather/scatter between a and b(pointes to the same memory location)
> In this case it should be possible to vectorize the loop, but the compiler is tries to be safe and does not vectorize it.
## Loop 3(18-20)
> statement clobbers memory: __builtin_memmove (&a, _12, 4080);   
> Means the loop could not be vectorized because of possible alias involving gather/scatter between a and _12 
> Sadly there are no more information about the loop in the output  
> My guess would be that the compiler is not able to vectorize the loop because of the data dependency(anti) between the elements in a.  

| i   | a[i-4] | a[i] |
| --- | ------ | ---- |
| 4   | 0      | 4    |
| 5   | 1      | 5    |
| 6   | 2      | 6    |
| 7   | 3      | 7    |
| 8   | 4      | 8    |
| ... | ...    | ...  |
## Loop 4(22-24)
> The compiler try different vectorization factors such as V4QI and V8QI.  
> The loop could't be vectorized because of possible alias involving gather/scatter between a[_4] and a[i_47]
> Again the compiler is trying to be safe and does not vectorize the loop.  
> It tried to vectorize the loop with V4QI and V8QI, but it was not possible because of different data dependencies between the elements in a.
## Loop 5(27-30)
> not vectorized: loop contains function calls or data references that cannot be analyzed
> The printf function call is the reason for not vectorizing the loop

## Performance Analysis
> vect_analyze_data_ref_accesses: Checks for Data dependence in the loop
> vect_analyze_scalar_cycles: It checks for variables that change linearly with each iteration of the loop.(e.g. i++)  
> vect_pattern_recog: This check is recognizing patterns in the code that can be vectorized. 
> Vectorization factor: Loop can be performed simultaneously.  
> Cost model analysis: It estimates the cost of vectorizing the loop versus executing it in a scalar manner  

## TL;DR
> One loop where vectorization was successful, one loop where it was not possible because of aliasing, one loop where it was not possible because of a function call, and two loops where it was not possible because of aliasing.

## GNU Compiler Vector Base Type
https://gcc.gnu.org/onlinedocs/gcc-3.1/gcc/Vector-Extensions.html  
For vector types these have the form VnB; n should be the number of elements in the vector, and B should be the base mode of the individual elements.
> QI  
> -     An integer that is as wide as the smallest addressable unit, usually 8 bits.  
> HI  
> -     An integer, twice as wide as a QI mode integer, usually 16 bits.  
> SI  
> -     An integer, four times as wide as a QI mode integer, usually 32 bits.  
> DI  
> -     An integer, eight times as wide as a QI mode integer, usually 64 bits.  
>SF  
> -     A floating point value, as wide as a SI mode integer, usually 32 bits.  
>DF  
> -     A floating point value, as wide as a DI mode integer, usually 64 bits.   