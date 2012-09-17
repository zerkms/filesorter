#include "dummy_sorter.hpp"
#include "chunker.hpp"

using namespace sorter;

DummySorter::DummySorter(int memoryLimit)
{
    _memoryLimit = memoryLimit;
    _tmdDir = "tmp";
}

void DummySorter::Sort(const std::string& input, const std::string& output)
{
    _inputName = input;
    _outputName = output;

    Chunker chunker(_tmdDir, _memoryLimit);
    chunker.Chunk(_inputName);
}

