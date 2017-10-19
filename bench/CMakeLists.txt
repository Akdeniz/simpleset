# git clone https://github.com/google/benchmark.git
# mkdir build && cd build
# cmake .. -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_LTO=true
# make && make install

find_package(benchmark REQUIRED)

add_executable(BenchmarkSet
   bench_set.cpp
    ../simpleset.hpp
   nonrepeating_random_sequence.hpp
)

target_link_libraries(BenchmarkSet benchmark pthread)
