#ifndef DUMMY_SORTER_HPP_
#define DUMMY_SORTER_HPP_

#include <string>

namespace sorter {

    class DummySorter
    {
    private:
        size_t _memoryLimit;
        std::string _inputName, _outputName, _tmdDir;

    public:
        DummySorter(int memoryLimit);
        void Sort(const std::string& input, const std::string& output);
    };

}

#endif