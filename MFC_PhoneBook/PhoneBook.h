#pragma once
#include <string>

using namespace std;

class PhoneBook {
public:
    PhoneBook() {};
    static const string FILE_NAME;
    static const string PHONE_MASK;
    static const string NOTE_DELIMETER;
    static const string FORMAT_ARGUMENTS;

    static void flush(string name, string phone);
    static void findByName(string key, string* name, string* phone);
    static void findByPhone(string key, string* name, string* phone);

private:
    static bool isNameCorrect(string name);
    static bool isPhoneCorrect(string phone);

    static bool checkNameInRecord(string record, string name);
    static bool checkPhoneInRecord(string record, string phone);

    static string getNameFromNote(string note);
    static string getPhoneFromNote(string note);

    static bool isRepeatRecord(string name, string phone);
};
