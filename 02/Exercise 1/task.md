- Interpret the output and describe what information you can gather. Please also elaborate on these questions:
  - Can you retrieve the number of CPUs and cores from the output?
    - We got two physical packages(Sockes), so two CPUs. 
    - 0 -> 5 in Package L#0 and 6 -> 11 in Package L#1, so 12 cores in total
  - Investigate the memory hierarchy information provided by lstopo.
    - How much memory (RAM) does the compute node offer?
        - 31 GB + 31GB = 62 GB total  
    - What does the term `NUMANode` tell you about the memory? Why are there two `NUMANodes`?
        - NUMA = Non-uniform memory access
        - So each processor has its own memory, and the two NUMANodes are the two processors. The benefit of this is that the memory access time is reduced, if a processor accesses its own memory, but increased if it accesses the memory of the other processor.
    - What interesting information can you retrieve about the caches of the system?
        - You can see the different levels of caches, and the size of each cache.(L1i, L1d, L2, L3).
        - L1i = Instruction cache
        - L1d = Data cache
  - Is there anything else you can find out from the output?
    - In Addition to the core count you can also see the number of PU's (Processing Units) of each core.
    - You can also see the connected PCI devices e.g. the network card(PCI 0b:00.0, PCI 0b:00.1) or a storage devices(PCI 10:00.0).
- Based on your observations, how many threads could you utilize at maximum when parallelizing a program with OpenMP on this system?
    - Theoretically 24 threads, but depending on the memory access pattern, it might be better to use only 12 threads. So that you only use the memory of one NUMANode.   
    But if my assumption of the next question is correct and we only see the login nodes, then it might possible to use all 162 compute nodes at once, so 324 threads. But that only works if a user is allowed to use all nodes at once. But again we could have a problem with the memory access between the nodes.
- Compare your observations to the [LCC3 documentation](https://www.uibk.ac.at/zid/systeme/hpc-systeme/leo3/hardware/) and [CPU documentation](https://www.intel.com/content/www/us/en/products/sku/47922/intel-xeon-processor-x5650-12m-cache-2-66-ghz-6-40-gts-intel-qpi/specifications.html). Do your observations match the documentation?
    - The information about the CPUs seems valid, but the memory size is different. The documentation states 24GB per NUMANode, but we got 31GB per NUMANode.  
    Also based on the documentation, I assume that the information we get when using `lstopo` is for the login/job-submission node, and not for the compute nodes. But I am not a 100% certain about that.