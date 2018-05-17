#include "../solution/lazy_sequence.h"
#include "lazy_seq_test.h"
#include <gtest/gtest.h>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <array>

using namespace cpppc;

TEST_F(LazySequenceTest, StandardConcept)
{
  LOG_MESSAGE("LazySequenceTest.StandardConcept: constructor");
  lazy_sequence<int> seq(10, [](int i) { return (100 + i * i); });
  ASSERT_EQ(10, seq.size());

  ASSERT_EQ(100, *(seq.begin()));
  ASSERT_EQ(101, seq[1]);
  ASSERT_EQ(104, seq[2]);
  ASSERT_EQ(109, seq[3]);
  ASSERT_EQ(116, seq[4]);
  ASSERT_EQ(181, *(seq.rbegin()));
}

