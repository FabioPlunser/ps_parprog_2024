# Task 1

> Vectorize your sequential program using OpenMP. Do not use any OpenMP thread-based parallelism.
> 
Done. See [sequential_float.c](./sequential_float.c).

# Task 2

> Compile your OpenMP-vectorized code with `-O1` but without any compiler flags for auto-vectorization and compare its performance for the problem size 2048 to both the sequential version and the compiler-vectorized version. What can you observe? Is the result still correct?
> 
| OpenMP-Vectorized | Sequential | Auto-Vectorized |
| ----------------- | ---------- | --------------- |
| 0.510             | 2.677      | 0.510           |

The auto OpenMP vectorization is exaclty the same as the automatic one done by the compiler. 

Yes the result is still correct. 


# Task 3

> Verify any findings using `perf` as described in Exercise 1.
<table>
  <thead>
    <tr>
      <th>Event</th>
      <th>OpenMP Vectorized</th>
      <th>None Vectorized</th>
      <th>Auto Vectorized</th>
      <th>Descritpion</th>
      <th>Remark</t>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>FP_COMP_OPS_EXE.X87</td>
      <td>655</td>
      <td>3,486</td>
      <td>741</td>
      <td>Number of floating-point operations executed by the x87 floatin-point unit</td>
      <td></td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.MMX</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>Number oof MMX insturctions executed</td>
      <td></td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.SSE_FP</td>
      <td>1,019,423,678</td>
      <td>4,090,621,574</td>
      <td>1,020,645,777</td>
      <td>Number of SSE (Streaming SIMD Extensions) floating-point operations  </td>
      <td>OpenMP very similar to auto vectorization</td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.SSE2_INTEGER</td>
      <td>28,087</td>
      <td>32,566</td>
      <td>12,083</td>
      <td>Number of SSE2 (Streaming SIMD Extensions 2) Integer operations</td>
      <td>For some reason OpenMP has a higher count than Auto vectorized.  </td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.SSE_FP_PACKED</td>
      <td>1,020,262,405</td>
      <td>0</td>
      <td>1,022,338,138</td>
      <td>Numer of SSE floating-point single-precissions instructions</td>
      <td>OpenMP very similar to the Auto Vectorization</td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.SSE_FP_SCALAR</td>
      <td>4,110</td>
      <td>4,099,363,382</td>
      <td>24,535</td>
      <td>Number of scalar SISD (Singl Insturction Single Data) single-precision floating-point Instruction</td>
      <td>The lower the better so OpenMP vectoriation is a bit better</td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.SSE_SINGLE_PRECISION</td>
      <td>1,027,060,217</td>
      <td>4,101,462,815</td>
      <td>1,027,384,119</td>
      <td>Number of single-precision floating-pont operations</td>
      <td>Not really releveant if using float variables, should be zero when using double</td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.SSE_DOUBLE_PRECISION</td>
      <td>0</td>
      <td>0</td>
      <td>8,203</td>
      <td>Number of double-precision floating-point operations</td>
      <td>Thsi is using float variables so no double-precision operations should occur. When using double this should be way higher.</td>
    </tr>
  </tbody>
</table>

# Task 4

> Repeat the sequential and OpenMP executions when changing the data type from `float` to `double`. What can you observe?
<table>
  <thead>
    <tr>
      <th>Event</th>
      <th>Float</th>
      <th>Double</th>
      <th>Descritpion</th>
      <th>Remark</t>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>FP_COMP_OPS_EXE.X87</td>
      <td>655</td>
      <td>2,052</td>
      <td>Number of floating-point operations executed by the x87 floatin-point unit</td>
      <td></td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.MMX</td>
      <td>0</td>
      <td>0</td>
      <td>Number oof MMX insturctions executed</td>
      <td></td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.SSE_FP</td>
      <td>1,019,423,678</td>
      <td>2,047,803,143</td>
      <td>Number of SSE (Streaming SIMD Extensions) floating-point operations  </td>
      <td>Because SSEE has a register size of 128 bit and with a <strong>float 32bit</strong> the SSE instruction han process 4 floats. Because <strong>double is 64 bit</strong> SEE can only process two at 
      a time as such for the same code it has to do twice as many operations </td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.SSE2_INTEGER</td>
      <td>28,087</td>
      <td>36,542</td>
      <td>Number of SSE2 (Streaming SIMD Extensions 2) Integer operations</td>
      <td>Similar enough</td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.SSE_FP_PACKED</td>
      <td>1,020,262,405</td>
      <td>2,046,101,109</td>
      <td>Numer of SSE floating-point single-precissions instructions</td>
      <td>Same as with SSE_FP </td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.SSE_FP_SCALAR</td>
      <td>4,110</td>
      <td>29,947</td>
      <td>Number of scalar SISD (Singl Insturction Single Data) single-precision floating-point Instruction</td>
      <td>It could be that because that each operations is less "dense" using double since it's twice the size and less variables can be processed at the same time. There might be some extra scaalr instruction to handle parts of the loop that couldn't be vectorized efficiently </td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.SSE_SINGLE_PRECISION</td>
      <td>1,027,060,217</td>
      <td>0</td>
      <td>Number of single-precision floating-pont operations</td>
      <td>Since double is double-precision no single-precisions operations are used</td>
    </tr>
    <tr>
      <td>FP_COMP_OPS_EXE.SSE_DOUBLE_PRECISION</td>
      <td>0</td>
      <td>2,052,172,09</td>
      <td>Number of double-precision floating-point operations</td>
      <td>Using double obsviously uses double-precision operations. But same as in SSE_FP because double is twice the size, twice the operations are needed</td>
    </tr>
  </tbody>
</table>


# Task 5

> How does the solution for this Exercise compare to Exercise 1? Are there any advantages or disadvantages?

- A disadvantage could be, you have to know where to use the `#pragma omp simd`, and normally a compiler has better knowledge about the hardware so it maybe can vectorize code which OpenMP can't
- Advantage more controll over the vectorization. 


# Task 6

> Enter the wall clock time of the OpenMP-vectorized version with size 2048, 1e6 repetitions and data type `float` to the spreadsheet linked on Discord.
> 
Done 0.510s