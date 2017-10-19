# simpleset
Simple set implementation that uses basic linear probing

#### Build & Run
```
-- build and install google benchmark
git clone https://github.com/google/benchmark.git
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_LTO=true


mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
./bench/BenchmarkSet

Run on (8 X 3900 MHz CPU s)
2017-10-19 16:03:45
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
--------------------------------------------------------------------------------
Benchmark                                         Time           CPU Iterations
--------------------------------------------------------------------------------
BM_SimpleSetSequentialInsert/65536                3 ms          3 ms        233
BM_SimpleSetSequentialInsert/262144              10 ms         10 ms         70
BM_SimpleSetSequentialInsert/2097152             76 ms         76 ms          9
BM_SimpleSetSequentialInsert/16777216           604 ms        604 ms          1
BM_UnorderedSetSequentialInsert/65536             4 ms          4 ms        159
BM_UnorderedSetSequentialInsert/262144           18 ms         18 ms         37
BM_UnorderedSetSequentialInsert/2097152         147 ms        147 ms          5
BM_UnorderedSetSequentialInsert/16777216       1081 ms       1081 ms          1
BM_SimpleSetRandomInsert/65536                    9 ms          9 ms         81
BM_SimpleSetRandomInsert/262144                  32 ms         32 ms         22
BM_SimpleSetRandomInsert/2097152                306 ms        306 ms          2
BM_SimpleSetRandomInsert/16777216              2954 ms       2954 ms          1
BM_UnorderedSetRandomInsert/65536                 9 ms          9 ms         84
BM_UnorderedSetRandomInsert/262144               74 ms         74 ms          9
BM_UnorderedSetRandomInsert/2097152            1209 ms       1209 ms          1
BM_UnorderedSetRandomInsert/16777216           9227 ms       9227 ms          1
```

#### Comparison:
 Comparison table below shows the performance and memory benefit at **insertion** phase compared to std::unordered_set.

|                             |TIME      |              |PEAK MEMORY|              |
|-----------------------------|---------:|-------------:|----------:|-------------:|
|                             |SIMPLESET | UNORDEREDSET | SIMPLESET | UNORDEREDSET |
|ascending_unique_int32_200m  |8.22      | 22.93        |~2.6       |~9.0          |
|descending_unique_int32_200m |8.19      | 23.87        |~2.6       |~9.0          |
|random_unique_int32_200m     |24.27     | 205.47       |~4.5       |~9.6          |
|random_nonunique_int32_200m  |12.49     | 96.18        |~4.5       |~6.0          |



#### About test data:
* **ascending_unique_int32_200m** : ascending numbers from 0 to 200m.
* **descending_unique_int32_200m** : descending numbers from 200m to 0.
* **random_unique_int32_200m** : 200m uint32 with random order.
* **random_nonunique_int32_200m** : lower random ordered half(100m) is replicated to upper half, so both halves are unique in itself.

#### Scripts
* [To generate random unique integers](https://gist.github.com/Akdeniz/91a16867ab6e4f58a09a8cb030e84c82)

#### TODO
* Compare performance of other functions
* Compare with other implementations(dense_hash_set etc)
