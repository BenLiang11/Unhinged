#ifndef MATCHMAKER
#define MATCHMAKER

#include "provided.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"

class MatchMaker {
	public:
		MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
		~MatchMaker();
		std::vector<EmailCount> IdentifyRankedMatches(std::string email,int threshold) const;

	private:
		const MemberDatabase* m_mdb;
		const AttributeTranslator* m_at;
};


#endif