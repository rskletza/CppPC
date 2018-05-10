/* ------------------------------------------------------------------------ *
 *                       DO NOT MODIFIY THIS FILE                           *
 * -------------------------------------------------------------------------*/

#include "forward_list_test.h"

#include <solution/forward_list.h>
#include <gtest/gtest.h>

//using namespace std;
using namespace cpppc;

TEST_F(Forward_listTest, StandardConcept)
{
  LOG_MESSAGE("forward_listTest.StandardConcept: new");
  forward_list<int> v1;
  forward_list<int> v2;

  LOG_MESSAGE("forward_listTest.StandardConcept: equals");
  ASSERT_EQ(1, v1 == v2);

  v1.push_front(34);
  v1.push_front(12);

  ASSERT_EQ(12, *(v1.begin()));
  ASSERT_EQ(34, *(++v1.begin()));

  ASSERT_EQ(0, v1 == v2);

  LOG_MESSAGE("forward_listTest.StandardConcept: assign");
  v1 = v2;

  ASSERT_EQ(1, v1 == v2);

  LOG_MESSAGE("forward_listTest.StandardConcept: copy");
  forward_list<int> v3(v1);

  ASSERT_EQ(1, v1 == v3);
}

TEST_F(Forward_listTest, Forward_listLIFO)
{
  LOG_MESSAGE("forward_listTest.forward_listLIFO: new");
  forward_list<int> v;

  LOG_MESSAGE("forward_listTest.forward_listLIFO: push_front(...)");
  v.push_front(444);
  v.push_front(333);
  v.push_front(222);
  v.push_front(111);
  ASSERT_EQ(4,   v.size());

  v.print_list();

  LOG_MESSAGE("forward_listTest.forward_listLIFO: pop_front(...)");
  ASSERT_EQ(111, v.pop_front());
  ASSERT_EQ(222, v.pop_front());
  ASSERT_EQ(333, v.pop_front());
  ASSERT_EQ(444, v.pop_front());
  ASSERT_EQ(0,   v.size());
}
