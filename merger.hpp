#ifndef MERGER_HPP_
#define MERGER_HPP_

#include <vector>
#include <fstream>

namespace sorter {

    class Merger
    {
    protected:
        std::string output_name, tmp_dir;
        size_t chunk_id, memory_limit;

        std::string GetNextChunkName(void);
        std::vector<std::string> MergeChunks(const std::vector<std::string>& chunks);
        void MergeStreams(std::ifstream& input_left, std::ifstream& input_right, std::ofstream& output);
        void ReadStream(std::ifstream& stream, std::vector<std::string>& output_vector) const;

    public:
        Merger(const std::string& output_name, const std::string& tmp_dir, const size_t& memory_limit);
        std::string Merge(const std::vector<std::string>& chunks);
    };

}

#endif;