#ifndef A_TRANSLATOR
#define A_TRANSLATOR

#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"

class AttributeTranslator {
	public:
		AttributeTranslator();

		~AttributeTranslator();

		bool Load(std::string filename);

		std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;

	private:
		RadixTree<std::vector<AttValPair>*> avpToCompatable;
		std::vector<std::vector<AttValPair>*> avpDELETE;
};

#endif