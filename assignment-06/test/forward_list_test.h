#ifndef CPPPC__01__FORWARD_LIST_TEST_H__INCLUDED
#define CPPPC__01__FORWARD_LIST_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"
#include <solution/forward_list.h>
//#include <list>

class Forward_listTest : public ::testing::Test {

public:

  Forward_listTest() {
    LOG_MESSAGE("Opening test suite: Forward_listTest");
  }

  virtual ~Forward_listTest() {
    LOG_MESSAGE("Closing test suite: Forward_listTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__01__FORWARD_LIST_TEST_H__INCLUDED
