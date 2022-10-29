#include "provided.h"
#include "PersonProfile.h"
#include "RadixTree.h"
#include <iostream>
#include <vector>
using namespace std;


PersonProfile::PersonProfile(std::string name, std::string email) {
	m_name = name;
	m_email = email;
}

PersonProfile::~PersonProfile() {

}

std::string PersonProfile::GetName() const {
	return m_name;
}

std::string PersonProfile::GetEmail() const {
	return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval) {
	string avp = attval.attribute + "," + attval.value;
	if (avpTree.search(avp) != nullptr) {
		return;
	}
	else {
		avpTree.insert(avp, attval);
		avpVector.push_back(attval);
	}
}

int PersonProfile::GetNumAttValPairs() const {
	return avpVector.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
	if (0 <= attribute_num && attribute_num < avpVector.size()) {
		attval = avpVector[attribute_num];
		return true;
	}
	return false;
}



