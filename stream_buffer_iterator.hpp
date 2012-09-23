#ifndef STREAM_BUFFER_ITERATOR_HPP_
#define STREAM_BUFFER_ITERATOR_HPP_

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <list>

namespace sorter {

    class StreamBufferIterator : public std::iterator<std::input_iterator_tag, std::string>
    {
    protected:
        std::list<std::string> buffer_list;
        std::list<std::string>::iterator it, ite;

        std::ifstream* input_stream;
        size_t buffer_size;
        bool is_empty;
        void LoadData(void);

    public:
        StreamBufferIterator(std::ifstream& input_stream, size_t buffer_size);
        StreamBufferIterator(std::ifstream& input_stream);
        StreamBufferIterator(void);

        StreamBufferIterator(const StreamBufferIterator& sbi) : input_stream(sbi.input_stream), buffer_size(sbi.buffer_size) {};

        StreamBufferIterator& operator++();
        StreamBufferIterator operator++(int);
        bool operator==(StreamBufferIterator& rhs);
        bool operator!=(StreamBufferIterator& rhs);
        std::string operator*();

        StreamBufferIterator end(void);
    };

}

#endif;