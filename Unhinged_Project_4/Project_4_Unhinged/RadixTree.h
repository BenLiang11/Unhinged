#ifndef RADIX
#define RADIX

#include <iostream>
#include <unordered_map>


template <typename ValueType>
class RadixTree {
	public:
		RadixTree() {}
		~RadixTree() {}
		void insert(std::string key, const ValueType& value) {
			tree[key] = value;
		}
		ValueType* search(std::string key) const {
			if (tree.find(key) != tree.end()) {
				return const_cast<ValueType*>(&(tree.find(key)->second));
			}
			return nullptr;
		}
	private:
		std::unordered_map<std::string, ValueType> tree;
};



#endif