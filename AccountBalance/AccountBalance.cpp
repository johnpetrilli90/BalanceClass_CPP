// AccountBalance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cassert> 

using namespace std;

class Balance {
public:
	Balance(int   dollars, int cents) {
		_dollars = dollars;
		_cents = cents;
	}
	Balance operator +(const Balance& other) const {
		Balance result(other.dollars(), other.cents());
		if ((cents() + result.cents()) >= 100) {
			result.set_dollars(dollars() + result.dollars() + 1); 
			result.set_cents(result.cents() + cents() - 100);
		}
		else {
			result.set_cents(cents() + result.cents()); 
			result.set_dollars(dollars() + result.dollars());
		}
		return result;
	}

	Balance operator -(const Balance& other) const {
		Balance result(other.dollars(), other.cents());
		assert(dollars() > result.dollars()); if (result.cents() > cents()) {
			result.set_dollars(dollars() - result.dollars() - 1); result.set_cents(100 -  result.cents()
				+ cents());
		}
		else {
			result.set_cents(cents() - result.cents()); 
			assert(dollars() > result.dollars());
			result.set_dollars(dollars() - result.dollars());
		}
		return result;
	}
	int dollars() const {
		return _dollars;
	}
	void set_dollars(int d) {
		_dollars = d;
	}
	int cents() const {
		return _cents;
	}
	void set_cents(int c) {
		_cents = c;
	}
private:
	int _dollars; 
	int _cents;
};


int main() {
	Balance savings(1234, 56); // $1,234.56
	Balance deposit(13, 11); // $13.11 
	Balance withdraw(107, 91); // $107.91
	Balance remaining = savings + deposit - withdraw; 
	assert(remaining.dollars() == 1139);
	assert(remaining.cents() == 76);
	return 0;
}
