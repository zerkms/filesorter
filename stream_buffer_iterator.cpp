#include "stream_buffer_iterator.hpp"

using namespace sorter;

StreamBufferIterator::StreamBufferIterator(std::ifstream& input_stream, size_t buffer_size)
    :
    input_stream(&input_stream),
    buffer_size(buffer_size)
{
    is_empty = false;
}

StreamBufferIterator::StreamBufferIterator(std::ifstream& input_stream)
    :
    input_stream(&input_stream),
    buffer_size(0)
{
    is_empty = true;
}

StreamBufferIterator::StreamBufferIterator(void)
{
    is_empty = true;
}

StreamBufferIterator& StreamBufferIterator::operator++()
{
    LoadData();

    if (!buffer_list.empty()) {
        buffer_list.pop_front();
    }

    return *this;
}

StreamBufferIterator StreamBufferIterator::operator++(int)
{
    StreamBufferIterator tmp(*this);
    operator++();
    return tmp;
}

bool StreamBufferIterator::operator==(StreamBufferIterator& rhs)
{
    if (rhs.is_empty) {
        LoadData();
        return buffer_list.empty();
    }

    return false;
}

bool StreamBufferIterator::operator!=(StreamBufferIterator& rhs)
{
    return !(*this == rhs);
}

std::string StreamBufferIterator::operator*()
{
    LoadData();

    if (!buffer_list.empty()) {
        return buffer_list.front();
    }

    // @TODO throw exception
    return "";
}

StreamBufferIterator StreamBufferIterator::end(void)
{
    return StreamBufferIterator();
}

void StreamBufferIterator::LoadData(void)
{
    if (buffer_list.empty()) {
        size_t current_size(0);
        std::string tmp_string;

        while (std::getline(*input_stream, tmp_string)) {
            current_size += tmp_string.size();
            buffer_list.push_back(tmp_string);

            if (current_size > buffer_size) {
                break;
            }
        }
    }
}