#ifndef CHUNK_SORTER_HPP_
#define CHUNK_SORTER_HPP_

#include <string>
#include <vector>

namespace sorter {

    class ChunkSorter
    {
    public:
        void Sort(std::vector<std::string>& source) const;
    };

}

#endif