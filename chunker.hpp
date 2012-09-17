#ifndef CHUNKER_HPP_
#define CHUNKER_HPP_

#include <string>
#include <vector>

using namespace std;

namespace sorter {

    class Chunker
    {
    private:
        string _tmp_dir;
        int _chunk_size;
        int _current_index;

        void WriteChunk(vector<string>& rows);
        string GetNextChunkName(void);

    public:
        Chunker(const string& tmp_dir, int chunk_size);
        void Chunk(const string& input);
    };

}

#endif