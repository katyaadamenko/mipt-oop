#include "Information.h"

Information::Information() {
	set<string> s;
	phoneNumbers = s;
	string str;
	email = str;
}

void Information::erasePhoneNumber(const phoneNumber_t & phoneNumber) {
	phoneNumbers_t::iterator it;
	it = phoneNumbers.find(phoneNumber);
	if (it != phoneNumbers.end())
		phoneNumbers.erase(it);
}

void Information::changePhoneNumber(const phoneNumber_t & oldPhoneNumber, const phoneNumber_t & newPhoneNumber) {
	phoneNumbers_t::iterator it = phoneNumbers.find(oldPhoneNumber);
	if (it == phoneNumbers.end())
		throw out_of_range("Wrong old phone number to change.");
	else {
		phoneNumbers.erase(it);
		phoneNumbers.insert(newPhoneNumber);
	}
}