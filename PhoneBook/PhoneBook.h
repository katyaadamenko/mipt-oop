#ifndef PHONE_BOOK
#define PHONE_BOOK

#include <map>
#include <vector>
#include "Information.h"

typedef string fio_t;
typedef map<fio_t, Information> phoneBook_t;

class PhoneBook {
	phoneBook_t phoneBook;
public:
	phoneBook_t::iterator addSubscriber(const pair<fio_t, Information> & fioWithInfo);
	phoneBook_t::iterator addSubscriber(const fio_t & fio,
		const Information & info);
	phoneBook_t::iterator addSubscriber(const fio_t & fio,
		const phoneNumber_t & phoneNumber = "", const string & email = "");
	phoneBook_t::iterator addSubscriber(const pair<fio_t, phoneNumber_t> & fioWithNumber,
		const string & email = "");
	void addNumber(const fio_t & fio, const phoneNumber_t & newNumber) {
		phoneBook[fio].addPhoneNumber(newNumber);
	}
	void changeNumber(const fio_t & fio, const phoneNumber_t & oldNumber,
		const phoneNumber_t & newNumber);
	phoneNumbers_t getNumbers(const fio_t & fio)const;
	email_t getEmail(const fio_t & fio)const;
	void eraseSubscriber(const fio_t & fio);
	void erasePhoneNumber(const fio_t & fio, const phoneNumber_t & phoneNumber);
	fio_t findSubscriber(const phoneNumber_t & phoneNumber);
	void printPhoneNumbers(const fio_t & fio);
	void printNumbersAndEmail(const fio_t & fio);
	void printAll();
	vector<pair<fio_t, phoneNumber_t>> getAllRecords();
	void launchPhoneBook();
};

#endif