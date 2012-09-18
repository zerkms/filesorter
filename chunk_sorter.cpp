#include <algorithm>

#include "chunk_sorter.hpp"

using namespace sorter;

void ChunkSorter::Sort(std::vector<std::string>& source) const
{
    std::vector<std::string>::iterator it = source.begin(), ite = source.end();
    std::sort(it, ite);
}