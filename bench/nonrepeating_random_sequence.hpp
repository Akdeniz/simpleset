#pragma once

// see http://preshing.com/20121224/how-to-generate-a-sequence-of-unique-random-integers/

class CNonRepeatingRandomSequence
{
public:
  CNonRepeatingRandomSequence( unsigned int seed, unsigned int seed_offset )
  {
    index_ = permute( permute( seed ) + 0x682f0161 );
    intermediate_offset_ = permute( permute( seed_offset ) + 0x46790905 );
  }

  unsigned int next()
  {
    return permute( ( permute( index_++ ) + intermediate_offset_ ) ^ 0x5bf03635 );
  }

private:
  unsigned int permute( unsigned int x )
  {
    static const unsigned int prime = 4294967291u;
    if ( x >= prime )
      return x;  // The 5 integers out of range are mapped to themselves.
    unsigned int residue = ( (unsigned long long)x * x ) % prime;
    return ( x <= prime / 2 ) ? residue : prime - residue;
  }

private:
  unsigned int index_;
  unsigned int intermediate_offset_;
};
