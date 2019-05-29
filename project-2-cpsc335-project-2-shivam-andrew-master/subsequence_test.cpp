///////////////////////////////////////////////////////////////////////////////
// subsequence_test.cpp
//
// Unit tests for subsequence.hpp
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>

#include "rubrictest.hpp"

#include "subsequence.hpp"

int main() {

  Rubric rubric;

  const sequence input1{0, 8, 4, 12, 2},
                 solution1{0, 8, 12},
                 input2{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15},
                 solution2{0, 4, 6, 9, 13, 15},
                 input3{631, 459, 752, 77, 401, 934, 54, 56, 93, 617},
                 solution3{54, 56, 93, 617},
                 input4{114, 530, 748, 840, 611, 709, 810, 231, 713, 848},
                 solution4{114, 530, 611, 709, 810, 848},
                 input5{224, 81, 264, 691, 978, 366, 993, 396, 995, 299},
                 solution5{224, 264, 691, 978, 993, 995},
                 input6{1, 2, 3, 4},
                 solution6{1, 2, 3, 4},
                 input7{4, 3, 2, 1},
                 solution7{4};

  rubric.criterion("end-to-beginning examples", 2,
		   [&]() {
         TEST_EQUAL("first input", solution1, longest_increasing_end_to_beginning(input1));
         TEST_EQUAL("second input", solution2, longest_increasing_end_to_beginning(input2));
		   });

  rubric.criterion("end-to-beginning additional cases", 1,
		   [&]() {
         TEST_EQUAL("input3", solution3, longest_increasing_end_to_beginning(input3));
         TEST_EQUAL("input4", solution4, longest_increasing_end_to_beginning(input4));
         TEST_EQUAL("input5", solution5, longest_increasing_end_to_beginning(input5));
         TEST_EQUAL("input6", solution6, longest_increasing_end_to_beginning(input6));
         TEST_EQUAL("input7", solution7, longest_increasing_end_to_beginning(input7));
		   });

  rubric.criterion("powerset examples", 2,
		   [&]() {
         TEST_EQUAL("first input", solution1, longest_increasing_powerset(input1));
         TEST_EQUAL("first input", solution2, longest_increasing_powerset(input2));
		   });

  rubric.criterion("powert additional cases", 1,
		   [&]() {
         TEST_EQUAL("input3", solution3, longest_increasing_powerset(input3));
         TEST_EQUAL("input4", solution4, longest_increasing_powerset(input4));
         TEST_EQUAL("input5", solution5, longest_increasing_powerset(input5));
         TEST_EQUAL("input6", solution6, longest_increasing_powerset(input6));
         TEST_EQUAL("input7", solution7, longest_increasing_powerset(input7));
		   });

  return rubric.run();
}
