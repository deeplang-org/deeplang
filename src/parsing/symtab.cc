#include "symtab.h"

namespace dp {
namespace internal {

template <class T>
void SymTab<T>::push(std::string k, T v) {
	table.insert(std::make_pair(k, v));
}

template <class T>
void SymTab<T>::remove(T v) {
	table.erase(table.find(v));
}

template <class T>
T SymTab<T>::find(std::string k) {
	return *table.find(k);
}

} // namespace internal
} // namespace dp
