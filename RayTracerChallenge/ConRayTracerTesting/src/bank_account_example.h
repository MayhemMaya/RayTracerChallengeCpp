#ifndef BANK_ACCOUNT_EXAMPLE_H
#define BANK_ACCOUNT_EXAMPLE_H

class BankAccount {
public:
	BankAccount();
	explicit BankAccount(const int& balance);
	int GetBalance();

private:
	int balance_ = 0;
};

#endif  // BANK_ACCOUNT_EXAMPLE_H
