#include "pch.h"
#include <cmath>
#include "utils.cpp"
#include "tuple.cpp"
#include "point.cpp"
#include "vector.cpp"

/*
#pragma region BankAccountTest
class BankAccountTest : public testing::Test {
 protected:
	BankAccount* account;
	BankAccountTest() {
		account = new BankAccount;
	}
	~BankAccountTest() {
		delete account;
	}
};

TEST_F(BankAccountTest, BankAccountStartsEmpty) {
	EXPECT_EQ(0, account->GetBalance());
}
#pragma endregion
*/

#pragma region TupleTests
TEST(TupleTest, TupleIsPoint) {
	Tuple a(4.3f, -4.2f, 3.1f, 1.0f);
	EXPECT_EQ(a[0], 4.3f);
	EXPECT_EQ(a[1], -4.2f);
	EXPECT_EQ(a[2], 3.1f);
	EXPECT_EQ(a[3], 1.0f);
	EXPECT_TRUE(a.IsPoint());
	EXPECT_FALSE(a.IsVector());
}

TEST(TupleTest, TupleIsVector) {
	Tuple a(4.3f, -4.2f, 3.1f, 0.0f);
	EXPECT_EQ(a[0], 4.3f);
	EXPECT_EQ(a[1], -4.2f);
	EXPECT_EQ(a[2], 3.1f);
	EXPECT_EQ(a[3], 0.0f);
	EXPECT_FALSE(a.IsPoint());
	EXPECT_TRUE(a.IsVector());
}

TEST(TupleTest, AddTwoTuples) {
	Tuple a1(3, -2, 5, 1);
	Tuple a2(-2, 3, 1, 0);
	EXPECT_TRUE(a1 + a2 == Tuple(1, 1, 6, 1));
}

TEST(TupleTest, SubtractTwoTuples) {
	Tuple a1(3, 2, 1, 1);
	Tuple a2(5, 6, 7, 0);
	EXPECT_TRUE(a1 - a2 == Tuple(-2, -4, -6, 1));
}

TEST(TupleTest, NegateTuple) {
	Tuple a(1, -2, 3, -4);
	EXPECT_TRUE(-a == Tuple(-1, 2, -3, 4));
}

TEST(TupleTest, MultiplyTupleByScalar) {
	Tuple a(1, -2, 3, -4);
	EXPECT_TRUE(a * 3.5 == Tuple(3.5, -7, 10.5, -14));
}

TEST(TupleTest, MultiplyTupleByFraction) {
	Tuple a(1, -2, 3, -4);
	EXPECT_TRUE(a * 0.5 == Tuple(0.5, -1, 1.5, -2));
}

TEST(TupleTest, DivideTupleByScalar) {
	Tuple a(1, -2, 3, -4);
	EXPECT_TRUE(a / 2 == Tuple(0.5, -1, 1.5, -2));
}
#pragma endregion

#pragma region PointTests
TEST(PointTest, CreatePoint) {
	Point p(4, -4, 3);
	EXPECT_TRUE(p == Tuple(4, -4, 3, 1));
}

TEST(PointTest, AddVectorToPoint) {
	Point p(5, 6, 7);
	Vector v(3, 2, 1);
	EXPECT_TRUE(p + v == Point(8, 8, 8));
}

TEST(PointTest, SubtractTwoPoints) {
	Point p1(3, 2, 1);
	Point p2(5, 6, 7);
	EXPECT_TRUE(p1 - p2 == Vector(-2, -4, -6));
}

TEST(PointTest, SubtractVectorFromPoint) {
	Point p(3, 2, 1);
	Vector v(5, 6, 7);
	EXPECT_TRUE(p - v == Point(-2, -4, -6));
}

TEST(PointTest, NegatePoint) {
	Point p(1, -2, 3);
	EXPECT_TRUE(-p == Point(-1, 2, -3));
}
#pragma endregion

#pragma region VectorTests
TEST(VectorTest, CreateVector) {
	Vector v(4, -4, 3);
	EXPECT_TRUE(v == Tuple(4, -4, 3, 0));
}

TEST(VectorTest, SubtractTwoVectors) {
	Vector v1(3, 2, 1);
	Vector v2(5, 6, 7);
	EXPECT_TRUE(v1 - v2 == Vector(-2, -4, -6));
}

TEST(VectorTest, SubtractVectorFromZeroVector) {
	Vector zero(0, 0, 0);
	Vector v(1, -2, 3);
	EXPECT_TRUE(zero - v == Vector(-1, 2, -3));
}

TEST(VectorTest, NegateVector) {
	Vector v(1, -2, 3);
	EXPECT_TRUE(-v == Vector(-1, 2, -3));
}

TEST(VectorTest, MultiplyVectorByScalar) {
	Vector v(1, -2, 3);
	EXPECT_TRUE(v * 3.5 == Vector(3.5, -7, 10.5));
}

TEST(VectorTest, MultiplyVectorByFraction) {
	Vector v(1, -2, 3);
	EXPECT_TRUE(v * 0.5 == Vector(0.5, -1, 1.5));
}

TEST(VectorTest, DivideVectorByScalar) {
	Vector v(1, -2, 3);
	EXPECT_TRUE(v / 2 == Vector(0.5, -1, 1.5));
}

TEST(VectorTest, ComputeMagnitudeOfVector1) {
	Vector v(1, 0, 0);
	EXPECT_EQ(v.magnitude(), 1);
}

TEST(VectorTest, ComputeMagnitudeOfVector2) {
	Vector v(0, 1, 0);
	EXPECT_EQ(v.magnitude(), 1);
}

TEST(VectorTest, ComputeMagnitudeOfVector3) {
	Vector v(0, 0, 1);
	EXPECT_EQ(v.magnitude(), 1);
}

TEST(VectorTest, ComputeMagnitudeOfVector4) {
	Vector v(1, 2, 3);
	EXPECT_EQ(v.magnitude(), sqrt(14));
}

TEST(VectorTest, ComputeMagnitudeOfVector5) {
	Vector v(-1, -2, -3);
	EXPECT_EQ(v.magnitude(), sqrt(14));
}

TEST(VectorTest, NormalizeVector1) {
	Vector v(4, 0, 0);
	EXPECT_TRUE(v.normalize() == Vector(1, 0, 0));
}

TEST(VectorTest, NormalizeVector2) {
	Vector v(1, 2, 3);
	EXPECT_TRUE(v.normalize() == Vector(0.26726, 0.53452, 0.80178));
}

TEST(VectorTest, NormalizeVector3) {
	Vector v(1, 2, 3);
	Vector norm = v.normalize();
	EXPECT_TRUE(utils::equal(norm.magnitude(), 1));
}

TEST(VectorTest, DotProductOfTwoVectors) {
	Vector a(1, 2, 3);
	Vector b(2, 3, 4);
	EXPECT_EQ(utils::dot(a, b), 20);
}

TEST(VectorTest, CrossProductOfTwoVectors) {
	Vector a(1, 2, 3);
	Vector b(2, 3, 4);
	EXPECT_TRUE(utils::cross(a, b) == Vector(-1, 2, -1));
	EXPECT_TRUE(utils::cross(b, a) == Vector(1, -2, 1));
}
#pragma endregion

