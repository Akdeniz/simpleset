# simpleset
Simple set implementation that uses basic linear probing

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
