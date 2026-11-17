// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: statistics/Settings.hpp
#pragma once

#include <string>

namespace packet {

// pcap options
struct Options {
    std::string file;
};
}

namespace statistics {

// statistics options
struct Options {
    bool verbose = false;
};
}
