#include <iostream>
#include <fstream>
#include <vector>

#include "chunker.hpp"

using namespace std;
using namespace sorter;

Chunker::Chunker(const string& tmp_dir, int chunk_size)
{
    _tmp_dir = tmp_dir;
    _chunk_size = chunk_size;
}

void Chunker::Chunk(const string& _inputName)
{
    _current_index = 0;

    ifstream finput(_inputName);
    string tmp_string;
    vector<string> buffer;

    size_t current_size = 0;

    if (!finput.is_open()) {
        // @TODO throw exception
    }

    while (getline(finput, tmp_string)) {
        current_size += tmp_string.size();

        if (current_size > _chunk_size) {
            WriteChunk(buffer);

            buffer.clear();
            current_size = tmp_string.size();
        }

        buffer.push_back(tmp_string);
    }

    finput.close();
}

void Chunker::WriteChunk(const vector<string>& rows)
{
    string filename = GetNextChunkName();

    ofstream chunk(filename);

    if (!chunk.good()) {
        // @TODO: throw exception
    }

    vector<string>::const_iterator it = rows.begin(), ite = rows.end();

    for (; it != ite; ++it) {
        chunk << *it << endl;
    }

    chunk.close();
}

string Chunker::GetNextChunkName(void)
{
    string filename = string(_tmp_dir);
    filename += "\\_";
    filename += to_string(_current_index++);
    filename += ".chunk";
    return filename;
}