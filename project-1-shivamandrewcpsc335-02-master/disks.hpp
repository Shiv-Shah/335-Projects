///////////////////////////////////////////////////////////////////////////////
// disks.hpp
//
// Definitions for two algorithms that each solve the alternating disks
// problem.
//
// As provided, this header has four functions marked with TODO comments.
// You need to write in your own implementation of these functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// State of one disk, either light or dark.
enum disk_color { DISK_LIGHT, DISK_DARK };

// Data structure for the state of one row of disks.
class disk_state {
private:
  std::vector<disk_color> _colors;

public:

  disk_state(size_t light_count)
  : _colors(light_count * 2, DISK_LIGHT) {

    assert(light_count > 0);

    for (size_t i = 0; i < _colors.size(); i += 2) {
      _colors[i] = DISK_DARK;
    }
  }

  // Equality operator for unit tests.
  bool operator== (const disk_state& rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {
    return _colors.size();
  }

  size_t light_count() const {
    return total_count() / 2;
  }

  size_t dark_count() const {
    return light_count();
  }

  bool is_index(size_t i) const {
    return (i < total_count());
  }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

// function to check if class array is alternating starting with black
  bool is_alternating() const {
    // current value of disk; TRUE= DISK_LIGHT; FALSE= DISK_DARK
    bool alt = false;
    // disk iterator variable
    disk_color init_val = get(0);
    // return false and exit if first disk is light
    if(init_val == DISK_LIGHT)
    {
      return false;
    }
    // iterate through array while indexes are available
    int i = 1;
    while(is_index(i))
    {
      //  if current disk is light and next disk is dark, alternate variable
      //  else return false and exit
      if(alt == true)
      {
        if(get(i) ==  DISK_DARK)
        {
          alt = false;
          i++;
        }
        else
        {
          return false;
        }
      }
      //  if current disk is dark and next disk is light, alternate variable
      //  else return false and exit
      else if(alt == false)
      {
        if(get(i) ==  DISK_LIGHT)
        {
          alt = true;
          i++;
        }
        else
        {
          return false;
        }
      }
    }
    // end of iteration; no falsehoods detected; return true
    return true;
  }

// function to check if lower half of array is DISK_LIGHT and upper half is DISK_DARK
  bool is_sorted() const {
    // iterate through size of array/2 or light_count
    // if any disks in light_count range are DISK_DARK; return false
    for(unsigned int i = 0; i < light_count(); i++)
    {
      if(get(i) == DISK_DARK)
      {
        return false;
      }
    }
    // end of iteration; no falsehoods detected; return true
    return true;
  }

};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;

public:

  sorted_disks(const disk_state& after, unsigned swap_count)
  : _after(after), _swap_count(swap_count) { }

  sorted_disks(disk_state&& after, unsigned swap_count)
  : _after(after), _swap_count(swap_count) { }

  const disk_state& after() const {
    return _after;
  }

  unsigned swap_count() const {
    return _swap_count;
  }
};

// function to sort disks by reading and swapping disks left to right
// also returns number of disk swaps made
sorted_disks sort_left_to_right(const disk_state& before) {
  // record number of disk swaps
  int counter = 0;
  // make copy of disk array
  disk_state after = before;
  // iterate through array
  for(unsigned int r = 0; r < after.total_count(); r++)
  {
    for(unsigned int c = 0; c < after.total_count()-1; c++)
    {
      // swap disks if DISK_DARK and next disk is DISK_LIGHT
      if(after.get(c) == DISK_DARK && after.get(c+1) == DISK_LIGHT)
      {
        after.swap(c);
        // increment disk swaps counter
        counter++;
      }
    }
  }
  // return sorted array and number of swaps
  return sorted_disks(after, counter);
}

// function to sort disks by alternating reading left to right and right to left
// swaps disks left to right in order of DISK_LIGHT to the left and DISK_DARK to the right
// also returns number of disk swaps made
sorted_disks sort_lawnmower(const disk_state& before) {
  // record number of disk swaps
  int counter = 0;
  // make copy of array
  disk_state after = before;
  // keep record of size of array
  int size = after.total_count();
  //iterate through array
  for( int c = 0; c < size; c++)
  {
    // left to right reading
    for( int i = 0; i < size-1;i++)
    {
      // swap disks if DISK_DARK and next disk is DISK_LIGHT
      if(after.get(i) == DISK_DARK &&  after.get(i+1) == DISK_LIGHT)
      {
        after.swap(i);
        // increment disk swap counter
        counter++;
      }
    }
    // reduce the size
    size--;
    // right to left reading
    for( int t = size-1; t > 1; t--)
    {
      // swap disks if DISK_LIGHT and disk prior is DISK_DARK
      if(after.get(t) == DISK_LIGHT &&  after.get(t-1) == DISK_DARK)
      {
        after.swap(t-1);
        // increment disk swap counter
        counter++;
      }
    }
  }
  // return sorted array and disk swaps
  return sorted_disks(after, counter);
}
