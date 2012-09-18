// sorter.cpp : Defines the entry point for the console application.
//

#include "dummy_sorter.hpp"

using namespace sorter;

int main(int argc, char** argv)
{
    DummySorter sorter(500);

    sorter.Sort("tmp\\input_small", "tmp\\output");

	return 0;
}
