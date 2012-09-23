#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>

#include "merger.hpp"
#include "stream_buffer_iterator.hpp"

using namespace sorter;

Merger::Merger(const std::string& output_name, const std::string& tmp_dir, const size_t& memory_limit)
    :
    output_name(output_name),
    tmp_dir(tmp_dir),
    memory_limit(memory_limit)
{
}

std::string Merger::Merge(const std::vector<std::string>& chunks)
{
    std::vector<std::string> new_chunks = chunks;

    chunk_id = 0;

    do {
        new_chunks = MergeChunks(new_chunks);
    } while(new_chunks.size() != 1);

    return new_chunks.front();
}

std::vector<std::string> Merger::MergeChunks(const std::vector<std::string>& chunks)
{
    std::vector<std::string> new_chunks;
    std::vector<std::string>::const_iterator it = chunks.begin(), ite = chunks.end();
    std::string new_chunk;

    for (; it != ite; ++it) {
        std::string right, left = *it;

        it++;

        if (it == ite) {
            new_chunks.push_back(left);
            break;
        }

        right = *it;

        std::ifstream left_stream(left), right_stream(right);

        if (!left_stream.good() || !right_stream.good()) {
            // @TODO: exception
        }

        new_chunk = GetNextChunkName();
        std::ofstream result_stream(new_chunk);

        if (!result_stream.good()) {
            // @TODO: exception
        }

        MergeStreams(left_stream, right_stream, result_stream);

        left_stream.close();
        right_stream.close();
        result_stream.close();

        remove(left.c_str());
        remove(right.c_str());

        new_chunks.push_back(new_chunk);
    }

    return new_chunks;
}

void Merger::MergeStreams(std::ifstream& input_left, std::ifstream& input_right, std::ofstream& output)
{
    std::string value_left, value_right;
    size_t memory_for_iterator = memory_limit / 2;

    StreamBufferIterator
        it_left(input_left, memory_for_iterator),
        ite_left = it_left.end(),
        it_right(input_right, memory_for_iterator),
        ite_right = it_right.end();

    bool first_line(true);

    while (it_left != ite_left && it_right != ite_right) {
        if (!first_line) {
            output << '\n';
        } else {
            first_line = false;
        }

        value_left = *it_left;
        value_right = *it_right;

        if (value_left.compare(value_right) < 0) {
            output << value_left;
            ++it_left;
        } else {
            output << value_right;
            ++it_right;
        }
    }

    for (; it_left != ite_left; ++it_left) {
        output << '\n' << *it_left;
    }

    for (; it_right != ite_right; ++it_right) {
        output << '\n' << *it_right;
    }
}

std::string Merger::GetNextChunkName(void)
{
    std::string filename = std::string(tmp_dir);
    filename += "\\__";
    filename += std::to_string(chunk_id++);
    filename += ".chunk";
    return filename;
}

void Merger::ReadStream(std::ifstream& stream, std::vector<std::string>& output_vector) const
{
    std::string tmp_string;

    while (std::getline(stream, tmp_string)) {
        output_vector.push_back(tmp_string);
    }
}