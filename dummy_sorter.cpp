#include "dummy_sorter.hpp"
#include "chunker.hpp"
#include "merger.hpp"

using namespace sorter;

DummySorter::DummySorter(int memory_limit) : _memory_limit(memory_limit), _tmp_dir("tmp")
{
}

void DummySorter::Sort(const std::string& input_name, const std::string& output_name)
{
    _input_name = input_name;
    _output_name = output_name;

    std::vector<std::string> chunks;

    Chunker chunker(_tmp_dir, _memory_limit);
    chunks = chunker.Chunk(_input_name);

    Merger merger(output_name, _tmp_dir, _memory_limit);
    std::string last_chunk = merger.Merge(chunks);

    rename(last_chunk.c_str(), output_name.c_str());
}

