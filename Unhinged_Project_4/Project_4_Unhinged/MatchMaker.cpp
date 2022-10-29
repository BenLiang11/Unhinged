#include "MatchMaker.h"
#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

//Comparison operators
struct cmp {
	bool operator()(const int& a, const int& b) const {
		return (a > b);
	}
};

struct cmpS {
	bool operator()(const AttValPair& a, const AttValPair& b) const {
		return (a.attribute + a.value) < (b.attribute + b.value);
	}
};

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {
	m_mdb = &mdb;
	m_at = &at;
}
MatchMaker::~MatchMaker() {

}
std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
	const PersonProfile* profile = m_mdb->GetMemberByEmail(email);
	int max = profile->GetNumAttValPairs();
	set<AttValPair, cmpS> avpC;
	for (int i = 0; i < max; i++) {                                         //Translate all avps to a set of compatable avps
		AttValPair avp;
		profile->GetAttVal(i, avp);
		vector<AttValPair> avpCTemp = m_at->FindCompatibleAttValPairs(avp);
		vector<AttValPair>::iterator it = avpCTemp.begin();
		while (it != avpCTemp.end()) {
			avpC.insert(*it);
			it++;
		}
	}
	map<string, int>emailCounts;
	set<AttValPair>::iterator it2 = avpC.begin();
	while (it2 != avpC.end()) {                                              //Iterate through the set of converted avps
		vector<string> emails = m_mdb->FindMatchingMembers(*it2);
		vector<string>::iterator it3 = emails.begin();
		while (it3 != emails.end()) {                                        //Iterate through vector of emails associated with each avp
			if (emailCounts.find(*it3) == emailCounts.end()) {
				emailCounts[*it3] = 1;
			}	
			else if (emailCounts.find(*it3)->first == (*it3)) {
				(emailCounts.find(*it3)->second)++;
			}
			it3++;
		}
		it2++;
	}
	multimap<int, string, cmp>sortedEmails;                        //Reverse map to a multimap to sort
	map<string, int>::iterator it4 = emailCounts.begin();         
	while (it4 != emailCounts.end()) {
		sortedEmails.insert({ it4->second, it4->first });
		it4++;
	}

	vector<EmailCount>output;                                       //Vector of EmailCounts
	map<int, string>::iterator it5 = sortedEmails.begin();
	while (it5 != sortedEmails.end()) {
		if (it5->first >= threshold) {
		EmailCount in(it5->second, it5->first);
		output.push_back(in);
		}
		it5++;
	}

	return output;

}