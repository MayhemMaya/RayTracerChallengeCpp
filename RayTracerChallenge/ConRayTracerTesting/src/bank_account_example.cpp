#include "pch.h"
#include "bank_account_example.h"

BankAccount::BankAccount() {}
BankAccount::BankAccount(const int& balance)
		: balance_(balance) {}

int BankAccount::GetBalance() { return balance_; }