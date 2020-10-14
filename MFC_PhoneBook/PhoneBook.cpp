#include "PhoneBook.h"
#include <fstream>
#include <iostream>

const string PhoneBook::FILE_NAME = "Phone_Book_DB.txt";
const string PhoneBook::PHONE_MASK = "";
const string PhoneBook::FORMAT_ARGUMENTS = "FORMAT:\n   NAME could has [a-z],[A-Z],[0-9],'_'\n  PHONE = +*-???-???-??-??";
const string PhoneBook::NOTE_DELIMETER = "|";

void PhoneBook::flush(string name, string phone) throw(runtime_error, invalid_argument, exception) {
    ofstream fout;
    fout.open(FILE_NAME, ios::app);
    if (!fout.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        throw runtime_error("CAN'T OPEN THE FILE = " + FILE_NAME);
    }
    

    try { (isRepeatRecord(name, phone)); }
    catch (exception& error) {
        fout.close();
        throw error;
    };
    
    if (isNameCorrect(name) && isPhoneCorrect(phone)) {
        fout << name + NOTE_DELIMETER + phone << endl;
        fout.close();
    }
    else {
        fout.close();
        throw invalid_argument("Incorrect data: name = " + name + " phone = " + phone +'\n'+FORMAT_ARGUMENTS);
    }
}

void PhoneBook::findByName(string name, string* varForName, string* varForPhone) throw(runtime_error, invalid_argument) {
    ifstream fin;
    fin.open(FILE_NAME);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        throw runtime_error("CAN'T OPEN THE FILE = " + FILE_NAME);
    }

    string note;
    while (!fin.eof()) {
        fin >> note;
        if (checkNameInRecord(note, name)) {
            *varForName = getNameFromNote(note);
            *varForPhone = getPhoneFromNote(note);
            fin.close();
            return;
        }
    }
  
    *varForName = "null";
    *varForPhone = "null";
    fin.close();
    throw invalid_argument("Ошибка :: нет записи для name=" + name);
}

void PhoneBook::findByPhone(string phone, string* varForName, string* varForPhone) throw(runtime_error, invalid_argument) {
    ifstream fin;
    fin.open(FILE_NAME);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        throw runtime_error("CAN'T OPEN THE FILE = " + FILE_NAME);
    }

    string note;
    while (!fin.eof()) {
        fin >> note;
        if (checkPhoneInRecord(note, phone)) {
            *varForName = getNameFromNote(note);
            *varForPhone = getPhoneFromNote(note);
            fin.close();
            return;
        }
    }

    *varForName = "null";
    *varForPhone = "null";
    fin.close();
    throw invalid_argument("Ошибка :: нет записи для phone=" + phone);
}

bool PhoneBook::checkNameInRecord(string record, string name) {
    int rec_pos = 0;
    for (char c : name) {
        if (c == record[rec_pos])
        {
            rec_pos++;
        }
        else {
            return false;
        }
    }
    if (record[rec_pos] == '|')
        return true;
    else
        return false;
}

bool PhoneBook::checkPhoneInRecord(string record, string phone) {
    int rec_pos = record.find("|");
    rec_pos++;
    for (char c : phone) {
        if (c == record[rec_pos])
        {
            rec_pos++;
        }
        else {
            return false;
        }
    }
    if (rec_pos == record.size())
        return true;
    else
        return false;
}

bool PhoneBook::isRepeatRecord(string name, string phone) throw(runtime_error,invalid_argument){
    ifstream fin;
    fin.open(FILE_NAME, ios::in);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        throw runtime_error("CAN'T OPEN THE FILE = " + FILE_NAME);
    }

    string note;
    while (!fin.eof()) {
        fin >> note;
        string recName = getNameFromNote(note);
        string recPhone = getPhoneFromNote(note);
        if (recName == name && recPhone == phone) {
            fin.close();
            throw invalid_argument("the Record is repeated:\nname  =" + name + "\nphone = " + phone + " is in DB now");
        }
        if (recName == name) {
            fin.close();
            throw invalid_argument("the Record is repeated: name = "+name+"is in DB now");
        }
        if (recPhone==phone) {
            fin.close();
            throw invalid_argument("the Record is repeated: phone = " + phone + " is in DB now");
        }
    }
    fin.close();
    return false;
}

string PhoneBook::getNameFromNote(string note) {
    int pos = note.find(NOTE_DELIMETER);
    return note.substr(0, pos);
}

string PhoneBook::getPhoneFromNote(string note) {
    int pos = note.find(NOTE_DELIMETER);
    return note.substr(pos + 1, note.size());
}

bool PhoneBook::isNameCorrect(string name) {
    for (char c : name) {
        if ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c == '_' || '0' <= c && c <= '9')
            continue;
        else
            return false;
    }
    return true;
}

bool PhoneBook::isPhoneCorrect(string phone) {
    int phone_pos = 0;
    for (char c : PHONE_MASK) {
        switch (c) {
        case '+':
            if (phone[phone_pos] == '+' && phone_pos == 0) {
                phone_pos++;
            }
            else {
                return false;
            }
            break;

        case '*':
            if ('0' <= phone[phone_pos] && phone[phone_pos] <= '9') {
                while ('0' <= phone[phone_pos] && phone[phone_pos] <= '9')
                    phone_pos++;
            }
            else {
                return false;
            }
            break;

        case '-':
            if (phone[phone_pos] == '-') {
                phone_pos++;
                continue;
            }
            else {
                return false;
            }
            break;

        case '?':
            if ('0' <= phone[phone_pos] && phone[phone_pos] <= '9') {
                phone_pos++;
            }
            else {
                return false;
            }
            break;
        }
    }
    return true;
}