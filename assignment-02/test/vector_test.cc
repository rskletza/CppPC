
/* ------------------------------------------------------------------------ *
 *                       DO NOT MODIFIY THIS FILE                           *
 * -------------------------------------------------------------------------*/

#include "vector_test.h"

#include <solution/vector.h>
#include <gtest/gtest.h>

using namespace cpppc;

TEST_F(VectorTest, StandardConcept)
{
  LOG_MESSAGE("VectorTest.StandardConcept: new");
  Vector v1 = Vector();
  Vector v2 = Vector();

  LOG_MESSAGE("VectorTest.StandardConcept: equals");
  ASSERT_EQ(1, v1 == v2);

  v1.push_back(12);
  v1.push_back(34);

  ASSERT_EQ(0, v1 == v2);

  LOG_MESSAGE("VectorTest.StandardConcept: assign");
  v1 = v2;

  ASSERT_EQ(1, v1 == v2);

  LOG_MESSAGE("VectorTest.StandardConcept: copy");
  Vector v3 = Vector(v1);

  ASSERT_EQ(1, v1 == v3);

}

TEST_F(VectorTest, VectorConcept)
{
  LOG_MESSAGE("VectorTest.VectorConcept: new");
  Vector v = Vector();

  ASSERT_EQ(0,  v.size());
  ASSERT_EQ(1,  v.empty());

  LOG_MESSAGE("VectorTest.VectorConcept: begin, end");
  ASSERT_EQ(v.begin(), v.end());
  ASSERT_EQ(v.end(), v.begin() + v.size());

  LOG_MESSAGE("VectorTest.VectorConcept: push_back(56)");
  v.push_back(56);
  LOG_MESSAGE("VectorTest.VectorConcept: push_back(78)");
  v.push_back(78);
  LOG_MESSAGE("VectorTest.VectorConcept: push_back(90)");
  v.push_back(90);

  ASSERT_EQ(v.end(), v.begin() + v.size());

  LOG_MESSAGE("VectorTest.VectorConcept: at");
  ASSERT_EQ(3,  v.size());
  ASSERT_EQ(0,  v.empty());
  ASSERT_EQ(56, v[0]);
  ASSERT_EQ(78, v[1]);
  ASSERT_EQ(90, v[2]);

  for (size_t i = 0; i < v.size(); i++) {
    LOG_MESSAGE("VectorTest.VectorConcept: v[%d] : %d",
                i, v[i]);
  }

  LOG_MESSAGE("VectorTest.VectorConcept: push_front(34)");
  v.push_front(34);

  LOG_MESSAGE("VectorTest.VectorConcept: push_front(12)");
  v.push_front(12);

  for (size_t i = 0; i < v.size(); i++) {
    LOG_MESSAGE("VectorTest.VectorConcept: v[%d] : %d",
                i, v[i]);
  }

  LOG_MESSAGE("VectorTest.VectorConcept: at");
  ASSERT_EQ(5,  v.size());
  ASSERT_EQ(0,  v.empty());
  ASSERT_EQ(12, v[0]);
  ASSERT_EQ(34, v[1]);
  ASSERT_EQ(90, v[4]);

  LOG_MESSAGE("VectorTest.VectorConcept: copy");
  Vector vcopy = Vector(v);

  LOG_MESSAGE("VectorTest.VectorConcept: begin, end");
  VectorIterator viter = v.begin();
  VectorIterator vend  = v.end();

  for (; viter != vend; ++viter) {
    *viter += 100;
  }

  LOG_MESSAGE("VectorTest.VectorConcept: at");
  for (size_t i = 0; i < vcopy.size(); i++) {
    ASSERT_EQ(v[i], vcopy[i] + 100);
  }

  LOG_MESSAGE("VectorTest.VectorConcept: assign(v_empty)");
  Vector v_empty = Vector();
  v = v_empty;

  ASSERT_EQ(1, v == v_empty);
  ASSERT_EQ(0, v.size());
  ASSERT_EQ(1, v.empty());
}

TEST_F(VectorTest, VectorFIFO)
{
  LOG_MESSAGE("VectorTest.VectorFIFO: new");
  Vector v = Vector();

  LOG_MESSAGE("VectorTest.VectorFIFO: empty");
  ASSERT_EQ(1, v.empty());

  LOG_MESSAGE("VectorTest.VectorFIFO: push_front(...)");
  v.push_front(444);
  v.push_front(333);
  v.push_front(222);
  v.push_front(111);
  ASSERT_EQ(4,   v.size());

  for (size_t i = 0; i < v.size(); i++) {
    LOG_MESSAGE("VectorTest.VectorConcept: v[%d] : %d",
                i, v[i]);
  }


  LOG_MESSAGE("VectorTest.VectorFIFO: pop_back(...)");
  ASSERT_EQ(444, v.pop_back());
  ASSERT_EQ(333, v.pop_back());
  ASSERT_EQ(222, v.pop_back());
  ASSERT_EQ(111, v.pop_back());
  ASSERT_EQ(0,   v.size());

  LOG_MESSAGE("VectorTest.VectorFIFO: push_back(...)");
  v.push_back(111);
  v.push_back(222);
  v.push_back(333);
  v.push_back(444);
  ASSERT_EQ(4,   v.size());

  LOG_MESSAGE("VectorTest.VectorFIFO: pop_front(...)");
  ASSERT_EQ(111, v.pop_front());
  ASSERT_EQ(222, v.pop_front());
  ASSERT_EQ(333, v.pop_front());
  ASSERT_EQ(444, v.pop_front());
  ASSERT_EQ(0,   v.size());

}

TEST_F(VectorTest, VectorLIFO)
{
  LOG_MESSAGE("VectorTest.VectorLIFO: new");
  Vector v = Vector();

  LOG_MESSAGE("VectorTest.VectorLIFO: push_front(...)");
  v.push_front(444);
  v.push_front(333);
  v.push_front(222);
  v.push_front(111);
  ASSERT_EQ(4,   v.size());

  LOG_MESSAGE("VectorTest.VectorLIFO: pop_front(...)");
  ASSERT_EQ(111, v.pop_front());
  ASSERT_EQ(222, v.pop_front());
  ASSERT_EQ(333, v.pop_front());
  ASSERT_EQ(444, v.pop_front());
  ASSERT_EQ(0,   v.size());

  LOG_MESSAGE("VectorTest.VectorLIFO: push_back(...)");
  v.push_back(111);
  v.push_back(222);
  v.push_back(333);
  v.push_back(444);
  ASSERT_EQ(4,   v.size());

  LOG_MESSAGE("VectorTest.VectorLIFO: pop_back(...)");
  ASSERT_EQ(444, v.pop_back());
  ASSERT_EQ(333, v.pop_back());
  ASSERT_EQ(222, v.pop_back());
  ASSERT_EQ(111, v.pop_back());
  ASSERT_EQ(0,   v.size());

}

TEST_F(VectorTest, VectorReverse)
{
  LOG_MESSAGE("VectorTest.VectorReverse: new");
  Vector v = Vector();

  LOG_MESSAGE("VectorTest.VectorReverse: reverse(empty vector)");
  v.reverse();
  ASSERT_EQ(0,   v.size());

  LOG_MESSAGE("VectorTest.VectorReverse: push_front(...)");
  v.push_front(444);
  v.push_front(333);
  v.push_front(222);
  v.push_front(111);
  ASSERT_EQ(4,   v.size());

  LOG_MESSAGE("VectorTest.VectorReverse: reverse(...)");
  v.reverse();
  ASSERT_EQ(4,   v.size());
  ASSERT_EQ(444, v[0]);
  ASSERT_EQ(333, v[1]);
  ASSERT_EQ(222, v[2]);
  ASSERT_EQ(111, v[3]);
}
