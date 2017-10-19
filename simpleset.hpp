/************************************************************************/
/* Simple set implementation that uses basic linear probing.            */
/************************************************************************/
#pragma once

#include <cmath>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <stdexcept>

// todo(demiroz): implement set_empty_key version as dense_hash_set. so that we can avoid using boolean vector.
template <class key_type, class hash_function_type = std::hash<key_type>,
          class hash_equal_type = std::equal_to<key_type>, class allocator_type = std::allocator<key_type>>
class SimpleSet
{
public:
 SimpleSet( const hash_function_type& hash_function = hash_function_type(),
            const hash_equal_type& hash_equal = hash_equal_type(), const allocator_type& allocator = allocator_type() )
     : keys_( allocator ),
       already_exists_( allocator ),
       capacity_( 0 ),
       size_( 0 ),
       load_factor_limit_( 0 ),
       hash_function_( hash_function ),
       hash_equal_( hash_equal ),
       allocator_( allocator )
 {
 }

  // return true if element is unique and inserted.
  bool insert(const key_type &key)
  {
    // if size is bigger than rehashing limit, finds next big prime and rehashes
    if (size_ >= load_factor_limit_)
    {
      reserve_internal(capacity_ + 1);
    }

    assert(size_ < capacity_);
    size_t index = hash_function_(key) % capacity_;

    // todo(demiroz) : try double hashing, quadratic probing?
    // apply basic linear probing
    while (already_exists_[index] && !hash_equal_(keys_[index], key))
    {
      index = (index + 1) % capacity_;
    }

    if (!already_exists_[index])
    {
      keys_[index] = key;
      already_exists_[index] = true;
      ++size_;
      return true;
    } else
    {
      return false;
    }
  }

  bool exists(const key_type &key)
  {
    assert(size_ < capacity_);
    size_t index = hash_function_(key) % capacity_;
    while (already_exists_[index] && !hash_equal_(keys_[index], key))
    {
      index = (index + 1) % capacity_;
    }

    return already_exists_[index];
  }

  void reserve(size_t new_capacity)
  {
    reserve_internal(static_cast<size_t>(std::ceil(new_capacity / LOAD_FACTOR)));
  }

  size_t size() const { return size_; };

private:
  inline void reserve_internal(size_t new_capacity)
  {
    assert(new_capacity < PRIME_LIST.back());

    // find big enough prime capacity from list
    auto it = std::lower_bound(PRIME_LIST.begin(), PRIME_LIST.end(), new_capacity);
    if( it == PRIME_LIST.end() )
    {
      throw std::invalid_argument( "new capacity is too high" );
    }

    new_capacity = *it;
    size_t rehashing_limit = static_cast<size_t>(std::round(new_capacity * LOAD_FACTOR));
    assert(capacity_ < new_capacity);
    assert(size_ < rehashing_limit);

    keys_.resize(new_capacity);

    std::vector<bool, allocator_type> new_already_exists( new_capacity, false, allocator_ );

    for (size_t idx = 0; idx != capacity_; ++idx)
    {
      if (already_exists_[idx])
      {
        key_type key = keys_[idx];
        already_exists_[idx] = false;
        while (true)
        {
          size_t index = hash_function_(key) % new_capacity;
          while (new_already_exists[index])
          {
            index = (index + 1) % new_capacity;
          }
          new_already_exists[index] = true;
          if (index < this->capacity_ && already_exists_[index])
          {
            std::swap(key, keys_[index]);
            already_exists_[index] = false;
            // follow the next key
          } else
          {
            keys_[index] = key;
            break;
          }
        }
      }
    }

    already_exists_ = std::move( new_already_exists );
    capacity_ = new_capacity;
    load_factor_limit_ = rehashing_limit;
  }

private:
  std::vector<key_type, allocator_type> keys_;
  std::vector<bool, allocator_type> already_exists_;
  size_t capacity_;
  size_t size_;
  size_t load_factor_limit_; // if size is equal to this value, grow to next prime capacity
  hash_function_type hash_function_;
  hash_equal_type hash_equal_;
  allocator_type allocator_;

  const double LOAD_FACTOR = 0.7;

  // todo(demiroz) : we may want to crop some of these  bigger sizes.
  // todo(demiroz) : try other grow ratios.
  // last 58 number of size_t is not covered
  // prime numbers which has grow ratio of ~1.5
  const std::vector<uint64_t> PRIME_LIST = std::vector<uint64_t>
  {
      2, 3, 5, 11, 13, 19, 29, 41, 67, 97, 149, 211, 317, 479, 719, 1069, 1601, 2399, 3607, 5399, 8093, 12143, 18211,
      27329, 40973, 61463, 92173, 138283, 207401, 311099, 466619, 699931, 1049891, 1574827, 2362229, 3543349, 5314961,
      7972451, 11958671, 17937989, 26906981, 40360471, 60540749, 90811057, 136216589, 204324851, 306487277, 459730919,
      689596379, 1034394551, 1551591841, 2327387749, 3491081621, 5236622429, 7854933643, 11782400447, 17673600691,
      26510401031, 39765601507, 59648402257, 89472603361, 134208905053, 201313357573, 301970036327, 452955054491,
      679432581727, 1019148872591, 1528723308887, 2293084963321, 3439627444949, 5159441167429, 7739161751117,
      11608742626777, 17413113940003, 26119670910071, 39179506365031, 58769259547511, 88153889321273, 132230833981901,
      198346250972977, 297519376459247, 446279064688931, 669418597033331, 1004127895549981, 1506191843324951,
      2259287764987423, 3388931647481129, 5083397471221711, 7625096206832549, 11437644310248799, 17156466465373199,
      25734699698059829, 38602049547089669, 57903074320634483, 86854611480951683, 130281917221427537,
      195422875832141341, 293134313748211931, 439701470622317857, 659552205933476777, 989328308900215043,
      1483992463350322721, 2225988695025484043, 3338983042538226211, 5008474563807339557, 7512711845711009797,
      11269067768566513681ull, 16903601652849770503ull, 18446744073709551557ull
  };
};
