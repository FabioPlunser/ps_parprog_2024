- How is the speedup of a parallel program defined?
    - Speedup is defined as a ratio of time when a program runs on a single core to the time when the program runs on multiple cores. It is a measurement of how much faster a program runs on multiple cores compared to a single core.
    - $Speedup = T(1) / T(n)$
- What is the formal definition of Amdahl's law and what relationship does it describe for parallel programs (explain in your own words)? Why/How is this significant?
    - $S(s) = 1/((1-p) + (p/s))$  
    p = fraction of the program that can be parallelized, s = number of cores
    - In nearly all programs, there is a portion of the code that cannot be parallelized. Amdahl's law describes this relationship between the speedup of a program and the fraction of the program that can be parallelized.  
    It is significant because it shows that the speedup of a program is limited by the fraction of the program that can't be parallelized. This means that even if a program is parallelized, it will not run infinitely faster as the number of cores increases.  
    At some point the non-parallelizable portion of the program will play a significant role in the overall runtime of the program and limit the speedup.
- Compute the theoretical speedup of a program that spends 10% of its time in unparallelizable, sequential regions for 6 cores and for a hypothetically unlimited number of cores.
    - $S(6) = 1/((1-0,9) + (0,9/6)) = 1 / (0,1 + 0,15) = 1/0,25 = 4$
    - $S(\infty) = 1/((1-0,9) + (0,9/\infty)) = 1 / (0,1 + 0) = 1/0,1 = 10$
- Compute the theoretical speedup of a program that spends 20% of its time in unparallelizable, sequential regions for 6 cores and for a hypothetically unlimited number of cores.
    - $S(6) = 1/((1-0,8) + (0,8/6)) = 1 / (0,2 + 0,133) = 1/0,333 = 3$
    - $S(\infty) = 1/((1-0,8) + (0,8/\infty)) = 1 / (0,2 + 0) = 1/0,2 = 5$
- Given an algorithm of time complexity O(n^3). How large (in %) can the unparallelizable, sequential region be at most, such that a speedup of 10 can be achieved using 64 cores?
    - $S(64) = 10$
    - $10 = 1/((1-p) + (p/64))$
    - $10 * ((1-p) + (p/64)) = 1$
    - $(1-p) + (p/64) = 0,1$
    - $64 - 64p + p = 6,4$
    - $-64p + p = 6,4 - 64$
    - $-63p = -57,6$
    - $63p = 57,6$
    - $p = 0,914286$
    - $p = 91,43\\%$   
    So the unparallelizable, sequential region can be at most 8,57% of the program for a speedup of 10 using 64 cores.
    The time complexity of the algorithm if for the most part not relevant for the calculation of the unparallelizable, sequential region. The time complexity only tells us how the runtime of the program scales with the input size. The unparallelizable, sequential region is a property of the program itself and not of the input size.
