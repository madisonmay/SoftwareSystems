Q: In `matrix2.c` there are two versions of `matrix_sum`: one traverses the rows and one traverses the columns.  Assuming that the matrix is bigger than the memory cache and that a memory cache line is big enough to hold 8 matrix elements, what cache hit rate would you expect for each version of `matrix_sum`?  Explain your reasoning

A: By traversing the rows you ensure that 7 out of every 8 elements are cached when accessed. Since 8 matrix elements fit into each block, accessing the first element in a block means that the next seven will be in cache memory.  But by traversing the columns, you could cause none of the matrix element accesses to result in a cache hit -- resulting in a cache hit rate of 0. If one column of the matrix is too large to fit in the cache, this means that by the time you loop back around and access the second element in a block of eight, that portion of the matrix is no longer in the cache, effectively making the caching process more detrimental than beneficial.      