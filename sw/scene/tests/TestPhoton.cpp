#include <algebra.h>
#include <gtest/gtest.h>
#include <stdio.h>
#include <photon.h>

class TestPhoton : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		patient_ = new photon();
	}

	// virtual void TearDown() {}

	photon* patient_;
};

TEST_F(TestPhoton, IsDist2Correct)
{
	photon other;
	other.set_position(patient_->get_position());
	float dist = patient_->dist2(other);

	EXPECT_EQ(0, dist);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
