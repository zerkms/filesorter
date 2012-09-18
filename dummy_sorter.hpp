#ifndef DUMMY_SORTER_HPP_
#define DUMMY_SORTER_HPP_

#include <string>

namespace sorter {

    class DummySorter
    {
    private:
        size_t _memory_limit;
        std::string _input_name, _output_name, _tmp_dir;

    public:
        DummySorter(int memory_limit);
        void Sort(const std::string& input, const std::string& output);
    };

}

#endif