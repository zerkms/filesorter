// sorter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "dummy_sorter.hpp"

using namespace sorter;

int _tmain(int argc, _TCHAR* argv[])
{
    DummySorter sorter(100);

    sorter.Sort("tmp\\input_small", "tmp\\output");

	return 0;
}
