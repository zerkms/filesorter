#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "merger.hpp"

using namespace sorter;

Merger::Merger(const std::string& output_name, const std::string& tmp_dir) : output_name(output_name), tmp_dir(tmp_dir)
{
}

void Merger::Merge(const std::vector<std::string>& chunks)
{
    std::vector<std::string> new_chunks = chunks;

    chunk_id = 0;

    do {
        new_chunks = MergeChunks(new_chunks);
    } while(new_chunks.size() != 1);
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

        new_chunks.push_back(new_chunk);
    }

    return new_chunks;
}

void Merger::MergeStreams(std::ifstream& input_left, std::ifstream& input_right, std::ofstream& output)
{
    std::vector<std::string> left_lines, right_lines;
    ReadStream(input_left, left_lines);
    ReadStream(input_right, right_lines);

    std::string value_left, value_right;

    std::vector<std::string>::const_iterator it_left = left_lines.begin(),
        it_right = right_lines.begin(),
        ite_left = left_lines.end(),
        ite_right = right_lines.end();

    while (it_left != ite_left && it_right != ite_right) {
        if (it_left != left_lines.begin() || it_right != right_lines.begin()) {
            output << std::endl;
        }

        value_left = *it_left;
        value_right = *it_right;

        if (value_left.compare(value_right) < 0) {
            output << value_left;
            it_left++;
        } else {
            output << value_right;
            it_right++;
        }
    }

    for (; it_left != ite_left; ++it_left) {
        output << std::endl << *it_left;
    }

    for (; it_right != ite_right; ++it_right) {
        output << std::endl << *it_right;
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