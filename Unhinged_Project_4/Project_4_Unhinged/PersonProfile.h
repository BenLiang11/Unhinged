#ifndef PERSONPROFILE
#define PERSONPROFILE

#include "provided.h"
#include "RadixTree.h"
#include <vector>

class PersonProfile {
public:
	PersonProfile(std::string name, std::string email);
	~PersonProfile();
	std::string GetName() const;
	std::string GetEmail() const;
	void AddAttValPair(const AttValPair& attval);
	int GetNumAttValPairs() const;
	bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
	std::string m_name;
	std::string m_email;
	RadixTree<AttValPair>avpTree;
	std::vector<AttValPair>avpVector;
};

#endif