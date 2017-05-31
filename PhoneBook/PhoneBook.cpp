#include "PhoneBook.h"

phoneBook_t::iterator PhoneBook :: addSubscriber(const pair<fio_t, Information> & fioWithInfo) {
	pair<phoneBook_t::iterator, bool> result;
	result = phoneBook.insert(fioWithInfo);
	if (!result.second)
		throw out_of_range("Impossible to add subscriber");
	return result.first;
}

phoneBook_t::iterator PhoneBook:: addSubscriber(const fio_t & fio,
	const Information & info) {
	phoneBook_t::iterator it = addSubscriber(make_pair(fio, info));
	return it;
}

phoneBook_t::iterator PhoneBook:: addSubscriber(const fio_t & fio,
	const phoneNumber_t & phoneNumber, const string & email) {
	Information info;
	info.addPhoneNumber(phoneNumber);
	info.setEmail(email);
	phoneBook_t::iterator it = addSubscriber(fio, info);
	return it;
}

phoneBook_t::iterator PhoneBook::addSubscriber(const pair<fio_t, phoneNumber_t> & fioWithNumber,
	const string & email) {
	Information info;
	info.addPhoneNumber(fioWithNumber.second);
	info.setEmail(email);
	phoneBook_t::iterator it = addSubscriber(fioWithNumber.first, info);
	return it;
}

phoneNumbers_t PhoneBook::getNumbers(const fio_t & fio)const {
	phoneNumbers_t phoneNumbers;
	phoneBook_t::const_iterator it;
	it = phoneBook.find(fio);
	if (it == phoneBook.end())
		throw out_of_range("There are no such a subscriber");
	else
		phoneNumbers = it->second.getNumbers();
	return phoneNumbers;
}

email_t PhoneBook::getEmail(const fio_t & fio)const {
	phoneBook_t::const_iterator it;
	it = phoneBook.find(fio);
	if (it == phoneBook.end())
		throw out_of_range("There are no such a subscriber");
	return it->second.getEmail();
}

void PhoneBook::eraseSubscriber(const fio_t & fio) {
	phoneBook_t::const_iterator it;
	it = phoneBook.find(fio);
	if (it != phoneBook.end())
		phoneBook.erase(it);
}

void PhoneBook::erasePhoneNumber(const fio_t & fio, const phoneNumber_t & phoneNumber) {
	phoneBook_t::iterator it;
	it = phoneBook.find(fio);
	if (it != phoneBook.end())
		it->second.erasePhoneNumber(phoneNumber);
}

void PhoneBook::changeNumber(const fio_t & fio, const phoneNumber_t & oldNumber,
	const phoneNumber_t & newNumber) {
	phoneBook_t::iterator it;
	it = phoneBook.find(fio);
	if (it != phoneBook.end())
		it->second.changePhoneNumber(oldNumber, newNumber);
}

fio_t PhoneBook::findSubscriber(const phoneNumber_t & phoneNumber) {
	phoneNumbers_t::iterator result;
	fio_t subscriber;
	bool subscriberWasFound = false;
	for (phoneBook_t::iterator it = phoneBook.begin(); it != phoneBook.end(); ++it) {
		result = it->second.getNumbers().find(phoneNumber);
		if (result != it->second.getNumbers().end()) {
			subscriberWasFound = true;
			subscriber = it->first;
			break;
		}
	}
	if (!subscriberWasFound)
		throw out_of_range("There is no subsciber with this number");
	return subscriber;
}

void PhoneBook::printPhoneNumbers(const fio_t & fio) {
	phoneNumbers_t & phoneNumbers = this->getNumbers(fio);
	cout << "Phone numbers:" << endl;
	for (phoneNumbers_t::iterator it = phoneNumbers.begin();
		it != phoneNumbers.end(); ++it)
		cout << *it << endl;
}

void PhoneBook::printNumbersAndEmail(const fio_t & fio) {
	this->printPhoneNumbers(fio);
	email_t email = this->getEmail(fio);
	if (!email.empty()) {
		cout << "E-mail: " << email << endl;
	}
}

void PhoneBook::printAll() {
	for (phoneBook_t::iterator iteratorInBook = phoneBook.begin();
		iteratorInBook != phoneBook.end(); ++iteratorInBook) {
		phoneNumbers_t & phoneNumbers = iteratorInBook->second.getNumbers();
		for (phoneNumbers_t::iterator iteratorInNumbers = phoneNumbers.begin();
			iteratorInNumbers != phoneNumbers.end(); ++iteratorInNumbers)
			cout << iteratorInBook->first << ' ' << *iteratorInNumbers << endl;
	}
}

 vector<pair<fio_t, phoneNumber_t>> PhoneBook:: getAllRecords() {
	 vector<pair<fio_t, phoneNumber_t>> allRecords;
	 for (map<fio_t, Information>::iterator itInBook = phoneBook.begin();
		 itInBook != phoneBook.end(); ++itInBook) {
		 phoneNumbers_t & phoneNumbers = itInBook->second.getNumbers();
		 for (phoneNumbers_t::iterator itInNumbers = phoneNumbers.begin();
			 itInNumbers != phoneNumbers.end(); ++itInNumbers) {
			 pair<fio_t, phoneNumber_t> newRecord;
			 newRecord.first = itInBook->first;
			 newRecord.second = *itInNumbers;
			 allRecords.push_back(newRecord);
		 }
	 }
	 return allRecords;
}

 void PhoneBook::launchPhoneBook() {
	 cout << "Choose function:" << endl;
	 cout << "1 - add subscriber" << endl;
	 cout << "2 - change number" << endl;
	 cout << "3 - add number to subscriber" << endl;
	 cout << "4 - delete subscriber" << endl;
	 cout << "5 - delete phone number" << endl;
	 cout << "6 - print all phone numbers of suscriber" << endl;
	 cout << "7 - print phone numbers and e-mail of suscriber" << endl;
	 cout << "8 - print all records" << endl;
	 cout << "9 - print name of suscriber by phone number" << endl;
	 cout << "0 - close phone book" << endl;
	 cout << endl;
	 char command;
	 cin >> command;
	 while (command != '0') {
		 cout << endl;
		 if (command == '1') {
			 cout << "If you want to add only full name press 1" << endl;
			 cout << "full name with number - 2" << endl;
			 cout << "full name, number and email - 3" << endl << endl;
			 fio_t fullName, surname, name, patronymic;
			 phoneNumber_t phoneNumber = "";
			 email_t email = "";
			 char command2;
			 cin >> command2;
			 cout << "Surname: ";
			 cin >> surname;
			 cout << "Name: ";
			 cin >> name;
			 cout << "Patronymic: ";
			 cin >> patronymic;
			 fullName = surname + ' ' + name + ' ' + patronymic;
			 if (command2 == '2' || command2 == '3') {
				 cout << "Phone number: ";
				 cin >> phoneNumber;
				 if (command2 == '3')
					 cout << "E-mail: ";
					 cin >> email;
			 }
			 try {
				 addSubscriber(fullName, phoneNumber, email);
			 }
			 catch (out_of_range & ex) {
				 cout << ex.what() << endl;
				 cout << "If you want to change number press 1, \n add - 2, \n to continue - 3" << endl << endl;
				 cin >> command2;
				 if (command2 == '3')
					 continue;
				 else if (command2 == '1') {
					 phoneNumber_t oldNumber, newNumber;
					 cout << endl << "Old number:";
					 cin >> oldNumber;
					 cout << endl << "New number:";
					 cin >> newNumber;
					 try {
						 changeNumber(fullName, oldNumber, newNumber);
					 }
					 catch (out_of_range & ex) {
						 cout << ex.what() << endl;
					 }
				 }
				 else {
					 phoneNumber_t newNumber;
					 cout << "New number:";
					 cin >> newNumber;
					 try {
						 addNumber(fullName, newNumber);
					 }
					 catch (out_of_range & ex) {
						 cout << ex.what() << endl;
					 }
				 }
			 }
		 }
		 else if (command == '2') {
			 fio_t fullName, surname, name, patronymic;
			 cout << "Subscriber:" << endl;
			 cout << "Surname: ";
			 cin >> surname;
			 cout << "Name: ";
			 cin >> name;
			 cout << "Patronymic: ";
			 cin >> patronymic;
			 fullName = surname + ' ' + name + ' ' + patronymic;
			 phoneNumber_t oldNumber, newNumber;
			 cout << "Old number:";
			 cin >> oldNumber;
			 cout << "New number:";
			 cin >> newNumber;
			 try {
				 changeNumber(fullName, oldNumber, newNumber);
			 }
			 catch (out_of_range & ex) {
				 cout << ex.what() << endl;
			 }
		 }
		 else if (command == '3') {
			 fio_t fullName, surname, name, patronymic;
			 cout << "Subscriber:" << endl;
			 cout << "Surname: ";
			 cin >> surname;
			 cout << "Name: ";
			 cin >> name;
			 cout << "Patronymic: ";
			 cin >> patronymic;
			 fullName = surname + ' ' + name + ' ' + patronymic;
			 phoneNumber_t newNumber;
			 cout << "New number:";
			 cin >> newNumber;
			 try {
				 addNumber(fullName, newNumber);
			 }
			 catch (out_of_range & ex) {
				 cout << ex.what() << endl;
			 }
		 }
		 else if (command == '4') {
			 fio_t fullName, surname, name, patronymic;
			 cout << "Subscriber:" << endl;
			 cout << "Surname: ";
			 cin >> surname;
			 cout << "Name: ";
			 cin >> name;
			 cout << "Patronymic: ";
			 cin >> patronymic;
			 fullName = surname + ' ' + name + ' ' + patronymic;
			 eraseSubscriber(fullName);
		 }
		 else if (command == '5') {
			 fio_t fullName, surname, name, patronymic;
			 cout << "Subscriber:" << endl;
			 cout << "Surname: ";
			 cin >> surname;
			 cout << "Name: ";
			 cin >> name;
			 cout << "Patronymic: ";
			 cin >> patronymic;
			 fullName = surname + ' ' + name + ' ' + patronymic;
			 phoneNumber_t phoneNumber;
			 cout << "Phone number:";
			 cin >> phoneNumber;
			 erasePhoneNumber(fullName, phoneNumber);
		 }
		 else if (command == '6') {
			 fio_t fullName, surname, name, patronymic;
			 cout << "Subscriber:" << endl;
			 cout << "Surname: ";
			 cin >> surname;
			 cout << "Name: ";
			 cin >> name;
			 cout << "Patronymic: ";
			 cin >> patronymic;
			 fullName = surname + ' ' + name + ' ' + patronymic;
			 try {
				 printPhoneNumbers(fullName);
			 }
			 catch (out_of_range & ex) {
				 cout << ex.what() << endl;
			 }
		 }
		 else if (command == '7') {
			 fio_t fullName, surname, name, patronymic;
			 cout << "Subscriber:" << endl;
			 cout << "Surname: ";
			 cin >> surname;
			 cout << "Name: ";
			 cin >> name;
			 cout << "Patronymic: ";
			 cin >> patronymic;
			 fullName = surname + ' ' + name + ' ' + patronymic;
			 try {
				 printNumbersAndEmail(fullName);
			 }
			 catch (out_of_range & ex) {
				 cout << ex.what() << endl;
			 }
		 }
		 else if (command == '8') {
			 printAll();
		 }
		 else {
			 phoneNumber_t phoneNumber;
			 cout << "Phone number:" << endl;
			 cin >> phoneNumber;
			 fio_t subscriber = "";
			 try {
				 subscriber = findSubscriber(phoneNumber);
			 }
			 catch (out_of_range & ex) {
				 cout << ex.what() << endl;
			 }
			 if (!subscriber.empty())
				 cout << subscriber << endl;
		 }
		 cin >> command;
		 cout << endl;
	 }
	 return;
 }

