#include "dummy_sorter.hpp"
#include "chunker.hpp"

using namespace sorter;

DummySorter::DummySorter(int memory_limit) : _memory_limit(memory_limit), _tmp_dir("tmp")
{
}

void DummySorter::Sort(const std::string& input_name, const std::string& output_name)
{
    _input_name = input_name;
    _output_name = output_name;

    Chunker chunker(_tmp_dir, _memory_limit);
    chunker.Chunk(_input_name);
}

