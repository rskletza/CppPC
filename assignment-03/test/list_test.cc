/* ------------------------------------------------------------------------ *
 *                       DO NOT MODIFIY THIS FILE                           *
 * -------------------------------------------------------------------------*/

#include "list_test.h"

#include <solution/list.h>
//#include <list>
#include <gtest/gtest.h>

//using namespace std;
using namespace cpppc;

TEST_F(ListTest, StandardConcept)
{
  LOG_MESSAGE("listTest.StandardConcept: new");
  list<int> v1;
  list<int> v2;

  LOG_MESSAGE("listTest.StandardConcept: equals");
  ASSERT_EQ(1, v1 == v2);

  v1.push_back(12);
  v1.push_back(34);

  ASSERT_EQ(0, v1 == v2);

  LOG_MESSAGE("listTest.StandardConcept: assign");
  v1 = v2;

  ASSERT_EQ(1, v1 == v2);

  LOG_MESSAGE("listTest.StandardConcept: copy");
  list<int> v3 = v1;

  ASSERT_EQ(1, v1 == v3);

}

TEST_F(ListTest, ListConcept)
{
  LOG_MESSAGE("listTest.listConcept: new");
  list<int> v;

  ASSERT_EQ(0,  v.size());
  ASSERT_EQ(1,  v.empty());

  LOG_MESSAGE("listTest.listConcept: begin, end");
  ASSERT_EQ(v.begin(), v.end());
  //ASSERT_EQ(v.end(), v.begin() + v.size());

  LOG_MESSAGE("listTest.listConcept: push_back(56)");
  v.push_back(56);
  LOG_MESSAGE("listTest.listConcept: push_back(78)");
  v.push_back(78);
  LOG_MESSAGE("listTest.listConcept: push_back(90)");
  v.push_back(90);

  //ASSERT_EQ(v.end(), v.begin() + v.size());

//  LOG_MESSAGE("listTest.listConcept: at");
//  ASSERT_EQ(3,  v.size());
//  ASSERT_EQ(0,  v.empty());
//  ASSERT_EQ(56, v[0]);
//  ASSERT_EQ(78, v[1]);
//  ASSERT_EQ(90, v[2]);
//
//  for (size_t i = 0; i < v.size(); i++) {
//    LOG_MESSAGE("listTest.listConcept: v[%d] : %d",
//                i, v[i]);
//  }

  LOG_MESSAGE("listTest.listConcept: push_front(34)");
  v.push_front(34);

  LOG_MESSAGE("listTest.listConcept: push_front(12)");
  v.push_front(12);

//  for (size_t i = 0; i < v.size(); i++) {
//    LOG_MESSAGE("listTest.listConcept: v[%d] : %d",
//                i, v[i]);
//  }

//  LOG_MESSAGE("listTest.listConcept: at");
//  ASSERT_EQ(5,  v.size());
//  ASSERT_EQ(0,  v.empty());
//  ASSERT_EQ(12, v[0]);
//  ASSERT_EQ(34, v[1]);
//  ASSERT_EQ(90, v[4]);

  LOG_MESSAGE("listTest.listConcept: copy");
  list<int> vcopy = v;

  LOG_MESSAGE("listTest.listConcept: begin, end");
  list<int>::iterator viter = v.begin();
  list<int>::iterator vend  = v.end();

  for (; viter != vend; ++viter) {
    *viter += 100;
  }

//  LOG_MESSAGE("listTest.listConcept: at");
//  for (size_t i = 0; i < vcopy.size(); i++) {
//    ASSERT_EQ(v[i], vcopy[i] + 100);
//  }

  LOG_MESSAGE("listTest.listConcept: assign(v_empty)");
  list<int> v_empty;
  v = v_empty;

  ASSERT_EQ(1, v == v_empty);
  ASSERT_EQ(0, v.size());
  ASSERT_EQ(1, v.empty());
}

TEST_F(ListTest, ListFIFO)
{
  LOG_MESSAGE("listTest.listFIFO: new");
  list<int> v;

  LOG_MESSAGE("listTest.listFIFO: empty");
  ASSERT_EQ(1, v.empty());

  LOG_MESSAGE("listTest.listFIFO: push_front(...)");
  v.push_front(444);
  v.push_front(333);
  v.push_front(222);
  v.push_front(111);
  ASSERT_EQ(4,   v.size());

//  for (size_t i = 0; i < v.size(); i++) {
//    LOG_MESSAGE("listTest.listConcept: v[%d] : %d",
//                i, v[i]);
//  }


  LOG_MESSAGE("listTest.listFIFO: pop_back(...)");
  ASSERT_EQ(444, v.pop_back());
  ASSERT_EQ(333, v.pop_back());
  ASSERT_EQ(222, v.pop_back());
  ASSERT_EQ(111, v.pop_back());
  ASSERT_EQ(0,   v.size());

  LOG_MESSAGE("listTest.listFIFO: push_back(...)");
  v.push_back(111);
  v.push_back(222);
  v.push_back(333);
  v.push_back(444);
  ASSERT_EQ(4,   v.size());

  LOG_MESSAGE("listTest.listFIFO: pop_front(...)");
  ASSERT_EQ(111, v.pop_front());
  ASSERT_EQ(222, v.pop_front());
  ASSERT_EQ(333, v.pop_front());
  ASSERT_EQ(444, v.pop_front());
  ASSERT_EQ(0,   v.size());

}

TEST_F(ListTest, ListLIFO)
{
  LOG_MESSAGE("listTest.listLIFO: new");
  list<int> v;

  LOG_MESSAGE("listTest.listLIFO: push_front(...)");
  v.push_front(444);
  v.push_front(333);
  v.push_front(222);
  v.push_front(111);
  ASSERT_EQ(4,   v.size());

  LOG_MESSAGE("listTest.listLIFO: pop_front(...)");
  ASSERT_EQ(111, v.pop_front());
  ASSERT_EQ(222, v.pop_front());
  ASSERT_EQ(333, v.pop_front());
  ASSERT_EQ(444, v.pop_front());
  ASSERT_EQ(0,   v.size());

  LOG_MESSAGE("listTest.listLIFO: push_back(...)");
  v.push_back(111);
  v.push_back(222);
  v.push_back(333);
  v.push_back(444);
  ASSERT_EQ(4,   v.size());

  LOG_MESSAGE("listTest.listLIFO: pop_back(...)");
  ASSERT_EQ(444, v.pop_back());
  ASSERT_EQ(333, v.pop_back());
  ASSERT_EQ(222, v.pop_back());
  ASSERT_EQ(111, v.pop_back());
  ASSERT_EQ(0,   v.size());

}
