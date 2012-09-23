#include <iostream>
#include <fstream>
#include <vector>

#include "chunker.hpp"

using namespace std;
using namespace sorter;

Chunker::Chunker(const string& tmp_dir, int chunk_size) : _tmp_dir(tmp_dir), _chunk_size(chunk_size), sorter()
{
}

vector<string> Chunker::Chunk(const string& _input_name)
{
    vector<string> chunks;

    _current_index = 0;

    ifstream finput(_input_name);
    vector<string> buffer;

    if (!finput.is_open()) {
        // @TODO throw exception
    }

    while (FillChunkBuffer(finput, buffer)) {
        chunks.push_back(WriteChunk(buffer));
        buffer.clear();
    }

    finput.close();

    return chunks;
}

bool Chunker::FillChunkBuffer(ifstream& input_stream, vector<string>& rows) const
{
    size_t current_size = 0;
    string tmp_string;

    while (getline(input_stream, tmp_string)) {
        current_size += tmp_string.size();
        rows.push_back(tmp_string);

        if (current_size > _chunk_size) {
            break;
        }
    }

    if (current_size > 0) {
        return true;
    }

    return false;
}

string Chunker::WriteChunk(vector<string>& rows)
{
    sorter.Sort(rows);

    string filename = GetNextChunkName();

    ofstream chunk(filename);

    if (!chunk.good()) {
        // @TODO: throw exception
    }

    vector<string>::iterator it = rows.begin(), ite = rows.end();

    for (; it != ite; ++it) {
        if (it != rows.begin()) {
            chunk << '\n';
        }

        chunk << *it;
    }

    chunk.close();

    return filename;
}

string Chunker::GetNextChunkName(void)
{
    string filename = string(_tmp_dir);
    filename += "\\_";
    filename += to_string(_current_index++);
    filename += ".chunk";
    return filename;
}