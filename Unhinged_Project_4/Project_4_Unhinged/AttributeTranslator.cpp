#include "AttributeTranslator.h"
#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


AttributeTranslator::AttributeTranslator() {

}

AttributeTranslator::~AttributeTranslator() {
	vector<vector<AttValPair>*>::iterator it = avpDELETE.begin();
	while (it != avpDELETE.end()) {
		it = avpDELETE.erase(it);
	}
}

bool AttributeTranslator::Load(std::string filename) {
	ifstream infile(filename);
	if (!infile) {
		return false;
	}
	else {
		string line;
		string attribute, value, attributeC, valueC;
		string avpString;
		while (getline(infile, line)) {
			istringstream iss(line);                         //Insert avps into PersonProfile pp;
			getline(iss, attribute, ',');
			getline(iss, value, ',');
			getline(iss, attributeC, ',');
			getline(iss, valueC);

			avpString = attribute + ',' + value;
			AttValPair avp(attributeC, valueC);

			if (avpToCompatable.search(avpString) != nullptr) {
				(*(avpToCompatable.search(avpString)))->push_back(avp); //Add avp to vector
			}
			else {
				vector<AttValPair>* newVec = new vector<AttValPair>;    //Create new vector of avps
				(*newVec).push_back(avp);
				avpToCompatable.insert(avpString, newVec);
				avpDELETE.push_back(newVec);
			}
		}
		return true;
	}
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
	string avpString = source.attribute + ',' + source.value;
	vector<AttValPair> output;
	if (avpToCompatable.search(avpString) != nullptr) {                                  //Insert atvs into output vector
		vector<AttValPair>* found = *(avpToCompatable.search(avpString));
		vector<AttValPair>::iterator it = (*found).begin();
		while (it != (*found).end()) {
			output.push_back(*it);
			it++;
		}
	}
	return output;
}

