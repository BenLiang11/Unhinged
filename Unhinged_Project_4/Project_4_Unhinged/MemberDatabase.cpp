#include "MemberDatabase.h"
#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

MemberDatabase::MemberDatabase() {

}

MemberDatabase::~MemberDatabase() {
	vector<PersonProfile*>::iterator it = emailToProfileDELETE.begin();
	while (it != emailToProfileDELETE.end()) {
		it = emailToProfileDELETE.erase(it);
	}

	vector<std::vector<std::string>*>::iterator it2 = avpToEmailDELETE.begin();
	while (it2 != avpToEmailDELETE.end()) {
		it2 = avpToEmailDELETE.erase(it2);
	}

}

bool MemberDatabase::LoadDatabase(std::string filename) {
	ifstream infile(filename);
	if (!infile) {
		return false;
	}
	else {
		string line;
		string name, email, attribute, value, pairs;
		string avpString;
	out:
		getline(infile, name);
		getline(infile, email);
		getline(infile, pairs);
		PersonProfile* pp = new PersonProfile(name, email);
		while (getline(infile, line)) {
			if (line == "") {                                //If we reached last avp, add email and PersonProfile pp to RadixTree
				emailToProfileDELETE.push_back(pp);
				emailToProfile.insert(email, pp);
				goto out;
			}
			istringstream iss(line);                         //Insert avps into PersonProfile pp;
			getline(iss, attribute, ',');
			getline(iss, value);
			AttValPair avp(attribute, value);
			pp->AddAttValPair(avp);

			avpString = attribute + ',' + value;             //Turn avps into strings to store into RadixTree
			if (avpToEmail.search(avpString) != nullptr) {
				(*(avpToEmail.search(avpString)))->push_back(email); //Add email to vector
			}
			else {
				vector<string>* newVec = new vector<string>;         //Create new vector of emails
				(*newVec).push_back(email);
				avpToEmail.insert(avpString, newVec);
				avpToEmailDELETE.push_back(newVec);
			}
		}
		emailToProfile.insert(email, pp);
		return true;
	}
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
	string avpString = input.attribute + ',' + input.value;
	vector<string> output;
	if (avpToEmail.search(avpString) != nullptr) {
		vector<string>* found = *(avpToEmail.search(avpString));
		vector<string>::iterator it = (*found).begin();           //Insert emails into output vector
		while (it != (*found).end()) {
			output.push_back(*it);
			it++;
		}
	}
	return output;                                                //(Returns empty vector if avp was not found)
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {
	PersonProfile** ptr = emailToProfile.search(email);
	if (ptr == nullptr) return nullptr;
	else return *ptr;
}
