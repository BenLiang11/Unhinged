#ifndef M_DATABASE
#define M_DATABASE

#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"

class MemberDatabase {

	public:
		MemberDatabase();
		
		~MemberDatabase();
	
		bool LoadDatabase(std::string filename);
	
		std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;

		const PersonProfile* GetMemberByEmail(std::string email) const;
		
	private:
		RadixTree<PersonProfile*> emailToProfile;
		std::vector<PersonProfile*> emailToProfileDELETE;

		RadixTree<std::vector<std::string>*> avpToEmail;
		std::vector<std::vector<std::string>*> avpToEmailDELETE;
};



#endif