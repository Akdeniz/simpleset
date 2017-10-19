#include "benchmark/benchmark.h"

#include <unordered_set>

#include "../simpleset.hpp"
#include "nonrepeating_random_sequence.hpp"

static void BM_SimpleSetSequentialInsert( benchmark::State &state )
{
  while ( state.KeepRunning() )
  {
    SimpleSet<int> insertion_test;
    for ( int i = 0, i_end = state.range( 0 ); i < i_end; i++ )
    {
      insertion_test.insert( i );
    }
  }
}
BENCHMARK( BM_SimpleSetSequentialInsert )->Unit(benchmark::kMillisecond)->Range( 1 << 16, 1 << 24 );

static void BM_UnorderedSetSequentialInsert( benchmark::State &state )
{
  while ( state.KeepRunning() )
  {
    std::unordered_set<int> insertion_test;
    for ( int i = 0, i_end = state.range( 0 ); i < i_end; i++ )
    {
      insertion_test.insert( i );
    }
  }
}
BENCHMARK( BM_UnorderedSetSequentialInsert )->Unit(benchmark::kMillisecond)->Range( 1 << 16, 1 << 24 );

static void BM_SimpleSetRandomInsert( benchmark::State &state )
{
  CNonRepeatingRandomSequence generator{0xDEADBEEF, state.range( 0 )};
  while ( state.KeepRunning() )
  {
    SimpleSet<int> insertion_test;
    for ( int i = 0, i_end = state.range( 0 ); i < i_end; i++ )
    {
      insertion_test.insert( generator.next() );
    }
  }
}
BENCHMARK( BM_SimpleSetRandomInsert )->Unit(benchmark::kMillisecond)->Range( 1 << 16, 1 << 24 );

static void BM_UnorderedSetRandomInsert( benchmark::State &state )
{
  CNonRepeatingRandomSequence generator{0xDEADBEEF, state.range(0)};
  while ( state.KeepRunning() )
  {
    std::unordered_set<int> insertion_test;
    for ( int i = 0, i_end = state.range( 0 ); i < i_end; i++ )
    {
      insertion_test.insert( generator.next()  );
    }
  }
}
BENCHMARK( BM_UnorderedSetRandomInsert )->Unit(benchmark::kMillisecond)->Range( 1 << 16, 1 << 24 );

BENCHMARK_MAIN();
