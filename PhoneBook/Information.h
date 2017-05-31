#ifndef INFORMATION
#define INFORMATION

#include <iostream>
#include <set>
#include <string>
using namespace std;

typedef string phoneNumber_t;
typedef string email_t;
typedef set<phoneNumber_t> phoneNumbers_t;

class Information {
	phoneNumbers_t phoneNumbers;
	email_t email;
public:
	Information();
	Information(phoneNumbers_t & phoneNumbers) {
		this->phoneNumbers = phoneNumbers;
		email = "";
	}
	void addPhoneNumber(const phoneNumber_t & phoneNumber) {
		pair<phoneNumbers_t::iterator, bool> result;
		result = phoneNumbers.insert(phoneNumber);
	}
	void erasePhoneNumber(const phoneNumber_t & phoneNumber);
	void changePhoneNumber(const phoneNumber_t & oldPhoneNumber, const phoneNumber_t & newPhoneNumber);
	void setEmail(const email_t & email) {
		this->email = email;
	}
	email_t getEmail()const {
		return email;
	}
	phoneNumbers_t getNumbers()const {
		return phoneNumbers;
	}
	phoneNumbers_t & getNumbers() {
		return phoneNumbers;
	}
};

#endif