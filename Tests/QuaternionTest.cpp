#include <gtest/gtest.h>
#include "BSMath/Quaternion.h"

namespace BSMath
{
	TEST(QuaternionTest, Constructor)
	{
		const static float Zeros[4]{ 0.0f, 0.0f, 0.0f, 1.0f };

		Quaternion quat0;
		Quaternion quat1{ 0.0f, 0.0f, 0.0f, 1.0f };
		Quaternion quat2{ Quaternion::Identity };
		Quaternion quat3{ Zeros };
		Quaternion quat4{ Vector3::Zero, 0.0f };

		EXPECT_EQ(quat0, quat1);
		EXPECT_EQ(quat0, quat2);
		EXPECT_EQ(quat0, quat3);
		EXPECT_EQ(quat0, quat4);
	}

	TEST(QuaternionTest, Multiply)
	{
		
	}

	TEST(QuaternionTest, Global)
	{
		
	}
}