#include "std_extension.h"

//Apparently this isn't a part

template <class T> int std_ext::count_unique(T* begin, T* end) {
	int occurences = 0;
	
	std::set<T> uniqueElems;

	for (; begin != end; begin++) {
		uniqueElems.insert(*begin);
	}

	return uniqueElems.size();
}