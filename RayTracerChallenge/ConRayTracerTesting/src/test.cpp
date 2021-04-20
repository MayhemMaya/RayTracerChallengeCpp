#include "pch.h"
#include "bank_account_example.h"
#pragma region BankAccountTest

class BankAccountTest : public testing::Test {
 public:
	BankAccount* account_;
	BankAccountTest()
			: account_(new BankAccount) {}
	~BankAccountTest() {
		delete account_;
	}
};

TEST_F(BankAccountTest, BankAccountStartsEmpty) {
	EXPECT_EQ(0, account_->GetBalance());
}
#pragma endregion

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}