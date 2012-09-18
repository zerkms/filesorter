#ifndef CHUNKER_HPP_
#define CHUNKER_HPP_

#include <string>
#include <vector>

#include "chunk_sorter.hpp"

using namespace std;

namespace sorter {

    class Chunker
    {
    private:
        ChunkSorter sorter;
        string _tmp_dir;
        size_t _chunk_size;
        size_t _current_index;

        string WriteChunk(vector<string>& rows);
        string GetNextChunkName(void);

    public:
        Chunker(const string& tmp_dir, int chunk_size);
        vector<string> Chunk(const string& input);
    };

}

#endif