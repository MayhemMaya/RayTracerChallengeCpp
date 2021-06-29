#include "pch.h"
#include <cmath>
#include "utils.cpp"
#include "tuple.cpp"
#include "point.cpp"
#include "vector.cpp"
#include "color.cpp"
#include "canvas.cpp"
#include "Matrix2.cpp"
#include "Matrix3.cpp"
#include "Matrix4.cpp"

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
#pragm a endregion
*/

#pragma region UtilsTests
TEST(UtilsTests, ClampToZero) {
	EXPECT_EQ(utils::clamp(-1.5, 0.0, 1.0), 0.0);
}

TEST(UtilsTests, ClampToOne) {
	EXPECT_EQ(utils::clamp(1.5, 0.0, 1.0), 1.0);
}

TEST(UtilsTests, SwapFloatValues) {
	float a = 5.1f;
	float b = 6.3f;
	utils::swap(a, b);
	EXPECT_EQ(a, 6.3f);
	EXPECT_EQ(b, 5.1f);
}

TEST(UtilsTests, SwapIntegerValues) {
	int a = 4;
	int b = 3;
	utils::swap(a, b);
	EXPECT_EQ(a, 3);
	EXPECT_EQ(b, 4);
}

TEST(UtilsTests, SwapDoubleValues) {
	double a = 7.4;
	double b = 8.6;
	utils::swap(a, b);
	EXPECT_EQ(a, 8.6);
	EXPECT_EQ(b, 7.4);
}
#pragma endregion

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

#pragma region ColorTests
TEST(ColorTest, CreateColor) {
	Color c(-0.5f, 0.4f, 1.7f);
	EXPECT_EQ(c[0], -0.5f);
	EXPECT_EQ(c[1], 0.4f);
	EXPECT_EQ(c[2], 1.7f);
}

TEST(ColorTest, AddTwoColors) {
	Color c1(0.9, 0.6, 0.75);
	Color c2(0.7, 0.1, 0.25);
	EXPECT_TRUE(c1 + c2 == Color(1.6, 0.7, 1.0));
}

TEST(ColorTest, SubtractTwoColors) {
	Color c1(0.9, 0.6, 0.75);
	Color c2(0.7, 0.1, 0.25);
	EXPECT_TRUE(c1 - c2 == Color(0.2, 0.5, 0.5));
}

TEST(ColorTest, MultiplyColorByScalar) {
	Color c1(0.2, 0.3, 0.4);
	EXPECT_TRUE(c1 * 2 == Color(0.4, 0.6, 0.8));
}

TEST(ColorTest, MultiplyTwoColors) {
	Color c1(1, 0.2, 0.4);
	Color c2(0.9, 1, 0.1);
	EXPECT_TRUE(c1 * c2 == Color(0.9, 0.2, 0.04));
}
#pragma endregion

#pragma region CanvasTests
TEST(CanvasTest, CreateCanvas) {
	Canvas c(10, 20);
	for (int y = 0; y < c.GetHeight(); y++) {
		for (int x = 0; x < c.GetWidth(); x++) {
			ASSERT_TRUE(c.PixelAt(x, y) == Color(0, 0, 0));
		}
	}
}

TEST(CanvasTest, WritePixelToCanvas) {
	Canvas c(10, 20);
	Color red(1, 0, 0);
	c.WritePixel(2, 3, red);
	EXPECT_TRUE(c.PixelAt(2, 3) == red);
}

TEST(CanvasTest, ConstructPPMHeader) {
	Canvas c(5, 3);
	std::string ppm = c.ToPPM();
	std::vector<std::string> ppm_lines = utils::split_lines(ppm);
	EXPECT_EQ(ppm_lines[0], "P3");
	EXPECT_EQ(ppm_lines[1], "5 3");
	EXPECT_EQ(ppm_lines[2], "255");
}

TEST(CanvasTest, ConstructPPMPixelData) {
	Canvas c(5, 3);
	Color c1(1.5, 0, 0);
	Color c2(0, 0.5, 0);
	Color c3(-0.5, 0, 1);
	c.WritePixel(0, 0, c1);
	c.WritePixel(2, 1, c2);
	c.WritePixel(4, 2, c3);
	std::string ppm = c.ToPPM();
	std::vector<std::string> ppm_lines = utils::split_lines(ppm);
	EXPECT_EQ(ppm_lines[3], "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
	EXPECT_EQ(ppm_lines[4], "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");
	EXPECT_EQ(ppm_lines[5], "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
}

TEST(CanvasTest, SplitLongLinesInPPMFiles) {
	Canvas c(10, 2);
	for (int y = 0; y < c.GetHeight(); y++) {
		for (int x = 0; x < c.GetWidth(); x++) {
			c.WritePixel(x, y, Color(1, 0.8, 0.6));
		}
	}
	std::string ppm = c.ToPPM();
	std::vector<std::string> ppm_lines = utils::split_lines(ppm);
	EXPECT_EQ(ppm_lines[3], "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
	EXPECT_EQ(ppm_lines[4], "153 255 204 153 255 204 153 255 204 153 255 204 153");
	EXPECT_EQ(ppm_lines[5], "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
	EXPECT_EQ(ppm_lines[6], "153 255 204 153 255 204 153 255 204 153 255 204 153");
}

TEST(CanvasTest, PPMFileTerminatedByNewlineCharacter) {
	Canvas c(5, 3);
	std::string ppm = c.ToPPM();
	EXPECT_EQ(ppm[ppm.size()-1], '\n');
}
#pragma endregion

#pragma region MatrixTests
TEST(MatrixTest, Create2x2Matrix) {
	Matrix2 M(-3, 5,
						1, -2);
	EXPECT_EQ(M(0, 0), -3);
	EXPECT_EQ(M(0, 1), 5);
	EXPECT_EQ(M(1, 0), 1);
	EXPECT_EQ(M(1, 1), -2);
}

TEST(MatrixTest, Create3x3Matrix) {
	Matrix3 M(-3, 5, 0,
						1, -2, -7,
						0, 1, 1);
	EXPECT_EQ(M(0, 0), -3);
	EXPECT_EQ(M(1, 1), -2);
	EXPECT_EQ(M(2, 2), 1);
}

TEST(MatrixTest, Create4x4Matrix) {
	Matrix4 M(1, 2, 3, 4,
						5.5, 6.5, 7.5, 8.5,
						9, 10, 11, 12,
						13.5, 14.5, 15.5, 16.5);
	EXPECT_EQ(M(0, 0), 1);
	EXPECT_EQ(M(0, 3), 4);
	EXPECT_EQ(M(1, 0), 5.5);
	EXPECT_EQ(M(1, 2), 7.5);
	EXPECT_EQ(M(2, 2), 11);
	EXPECT_EQ(M(3, 0), 13.5);
	EXPECT_EQ(M(3, 2), 15.5);
}

TEST(MatrixTest, _2x2MatrixEqualityWithIdentical2x2Matrices) {
	Matrix2 A(1, 2,
						3, 4);

	Matrix2 B(1, 2,
						3, 4);
	EXPECT_TRUE(A == B);
}

TEST(MatrixTest, _2x2MatrixEqualityWithDifferent2x2Matrices) {
	Matrix2 A(1, 2,
						3, 4);

	Matrix2 B(4, 3,
						2, 1);
	EXPECT_TRUE(A != B);
}

TEST(MatrixTest, _3x3MatrixEqualityWithIdentical3x3Matrices) {
	Matrix3 A(1, 2, 3, 
						4, 5, 6,
						7, 8, 9);

	Matrix3 B(1, 2, 3,
						4, 5, 6,
						7, 8, 9);
	EXPECT_TRUE(A == B);
}

TEST(MatrixTest, _3x3MatrixEqualityWithDifferent3x3Matrices) {
	Matrix3 A(1, 2, 3,
						4, 5, 6,
						7, 8, 9);

	Matrix3 B(9, 8, 7,
						6, 0, 1,
						2, 3, 4);
	EXPECT_TRUE(A != B);
}

TEST(MatrixTest, _4x4MatrixEqualityWithIdentical4x4Matrices) {
	Matrix4 A(1, 2, 3, 4,
						5, 6, 7, 8,
						9, 8, 7, 6,
						5, 4, 3, 2);

	Matrix4 B(1, 2, 3, 4,
						5, 6, 7, 8,
						9, 8, 7, 6,
						5, 4, 3, 2);
	EXPECT_TRUE(A == B);
}

TEST(MatrixTest, _4x4MatrixEqualityWithDifferent4x4Matrices) {
	Matrix4 A(1, 2, 3, 4,
						5, 6, 7, 8,
						9, 8, 7, 6,
						5, 4, 3, 2);

	Matrix4 B(2, 3, 4, 5,
						6, 7, 8, 9,
						8, 7, 6, 5,
						4, 3, 2, 1);
	EXPECT_TRUE(A != B);
}

TEST(MatrixTest, MultiplyTwoMatrices) {
	Matrix4 A(1, 2, 3, 4,
						5, 6, 7, 8,
						9, 8, 7, 6,
						5, 4, 3, 2);

	Matrix4 B(-2, 1, 2, 3,
						3, 2, 1, -1,
						4, 3, 6, 5,
						1, 2, 7, 8);
	Matrix4 C = A * B;
	EXPECT_TRUE(C == Matrix4(20, 22, 50, 48,
													 44, 54, 114, 108,
													 40, 58, 110, 102,
													 16, 26, 46, 42));
}

TEST(MatrixTest, MultiplyMatrixByTuple) {
	Matrix4 A(1, 2, 3, 4,
						2, 4, 4, 2,
						8, 6, 4, 1,
						0, 0, 0, 1);
	Tuple b(1, 2, 3, 1);
	Tuple c = A * b;
	EXPECT_TRUE(c == Tuple(18, 24, 33, 1));
}

TEST(MatrixTest, MultiplyMatrixByIdentityMatrix) {
	Matrix4 A(0, 1, 2, 4,
						1, 2, 4, 8,
						2, 4, 8, 16,
						4, 8, 16, 32);
	Matrix4 identity_matrix;
	EXPECT_TRUE(A * identity_matrix == A);
}

TEST(MatrixTest, MultiplyIdentityMatrixByTuple) {
	Tuple a(1, 2, 3, 4);
	Matrix4 identity_matrix;
	EXPECT_TRUE(identity_matrix * a == a);
}

TEST(MatrixTest, TransposeMatrix) {
	Matrix4 A(0, 9, 3, 0,
						9, 8, 0, 8,
						1, 8, 5, 3,
						0, 0, 5, 8);
	EXPECT_TRUE(A.transpose() == Matrix4(0, 9, 1, 0,
																			 9, 8, 8, 0,
																			 3, 0, 5, 5,
																			 0, 8, 3, 8));
}

TEST(MatrixTest, TransposeIdentityMatrix) {
	Matrix4 identity_matrix;
	Matrix4 A = identity_matrix.transpose();
	EXPECT_TRUE(A == identity_matrix);
}

TEST(MatrixTest, CalculateDeterminantOf2x2Matrix) {
	Matrix2 A(1, 5, -3, 2);
	EXPECT_EQ(A.determinant(), 17);
}

TEST(MatrixTest, SubmatrixOf3x3MatrixIs2x2Matrix) {
	Matrix3 A(1, 5, 0,
						-3, 2, 7,
						0, 6, -3);
	EXPECT_TRUE(A.submatrix(0, 2) == Matrix2(-3, 2,
																					 0, 6));
}

TEST(MatrixTest, SubmatrixOf4x4MatrixIs3x3Matrix) {
	Matrix4 A(-6, 1, 1, 6,
						-8, 5, 8, 6,
						-1, 0, 8, 2,
						-7, 1, -1, 1);
	EXPECT_TRUE(A.submatrix(2, 1) == Matrix3(-6, 1, 6,
																					 -8, 8, 6,
																					 -7, -1, 1));
}

TEST(MatrixTest, CalculateMinorOf3x3Matrix) {
	Matrix3 A(3, 5, 0,
						2, -1, -7,
						6, -1, 5);
	Matrix2 B = A.submatrix(1, 0);
	EXPECT_EQ(B.determinant(), 25);
	EXPECT_EQ(A.minor(1, 0), 25);
}

TEST(MatrixTest, CalculateCofactorOf3x3Matrix) {
	Matrix3 A(3, 5, 0,
						2, -1, -7,
						6, -1, 5);
	EXPECT_EQ(A.minor(0, 0), -12);
	EXPECT_EQ(A.cofactor(0, 0), -12);
	EXPECT_EQ(A.minor(1, 0), 25);
	EXPECT_EQ(A.cofactor(1, 0), -25);
}

TEST(MatrixTest, CalculateDeterminantOf3x3Matrix) {
	Matrix3 A(1, 2, 6,
						-5, 8, -4,
						2, 6, 4);
	EXPECT_EQ(A.cofactor(0, 0), 56);
	EXPECT_EQ(A.cofactor(0, 1), 12);
	EXPECT_EQ(A.cofactor(0, 2), -46);
	EXPECT_EQ(A.determinant(), -196);
}

TEST(MatrixTest, CalculateDeterminantOf4x4Matrix) {
	Matrix4 A(-2, -8, 3, 5,
						-3, 1, 7, 3,
						1, 2, -9, 6,
						-6, 7, 7, -9);
	EXPECT_EQ(A.cofactor(0, 0), 690);
	EXPECT_EQ(A.cofactor(0, 1), 447);
	EXPECT_EQ(A.cofactor(0, 2), 210);
	EXPECT_EQ(A.cofactor(0, 3), 51);
	EXPECT_EQ(A.determinant(), -4071);
}

TEST(MatrixTest, MatrixIsInvertible) {
	Matrix4 A(6, 4, 4, 4,
						5, 5, 7, 6,
						4, -9, 3, -7,
						9, 1, 7, -6);
	EXPECT_EQ(A.determinant(), -2120);
	EXPECT_TRUE(A.invertible());
}

TEST(MatrixTest, MatrixIsNotInvertible) {
	Matrix4 A(-4, 2, -2, -3,
						9, 6, 2, 6,
						0, -5, 1, -5,
						0, 0, 0, 0);
	EXPECT_EQ(A.determinant(), 0);
	EXPECT_FALSE(A.invertible());
}

TEST(MatrixTest, CalculateInverseOfMatrix1) {
	Matrix4 A(-5, 2, 6, -8,
						1, -5, 1, 8,
						7, 7, -6, -7,
						1, -3, 7, 4);

	Matrix4 B = A.inverse();
	EXPECT_EQ(A.determinant(), 532);
	EXPECT_EQ(A.cofactor(2, 3), -160);
	EXPECT_EQ(B(3, 2), -160.0f/532.0f);
	EXPECT_EQ(A.cofactor(3, 2), 105);
	EXPECT_EQ(B(2, 3), 105.0f/532.0f);
	EXPECT_TRUE(B == Matrix4(0.21805,  0.45113,  0.24060, -0.04511,
													-0.80827, -1.45677, -0.44361,  0.52068,
													-0.07895, -0.22368, -0.05263,  0.19737,
													-0.52256, -0.81391, -0.30075,  0.30639));
}

TEST(MatrixTest, CalculateInverseOfMatrix2) {
	Matrix4 A(8, -5, 9, 2,
						7, 5, 6, 1,
						-6, 0, 9, 6,
						-3, 0, -9, -4);
	EXPECT_TRUE(A.inverse() == Matrix4(-0.15385, -0.15385, -0.28205, -0.53846,
																		 -0.07692,  0.12308,  0.02564,  0.03077,
																		  0.35897,  0.35897,  0.43590,  0.92308,
																		 -0.69231, -0.69231, -0.76923, -1.92308));
}

TEST(MatrixTest, CalculateInverseOfMatrix3) {
	Matrix4 A(9, 3, 0, 9,
						-5, -2, -6, -3,
						-4, 9, 6, 4,
						-7, 6, 6, 2);
	EXPECT_TRUE(A.inverse() == Matrix4(-0.04074, -0.07778,  0.14444, -0.22222,
																		 -0.07778,  0.03333,  0.36667, -0.33333,
																		 -0.02901, -0.14630, -0.10926,  0.12963,
																		  0.17778,  0.06667, -0.26667,  0.33333));
}

TEST(MatrixTest, MultiplyMatrixByItsInverse) {
	Matrix4 A(3, -9, 7, 3,
						3, -8, 2, -9,
						-4, 4, 4, 1,
						-6, 5, -1, 1);

	Matrix4 B(8, 2, 2, 2,
						3, -1, 7, 0,
						7, 0, 5, 4,
						6, -2, 0, 5);

	Matrix4 C = A * B;
	EXPECT_TRUE(C * B.inverse() == A);
}
#pragma endregion