// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: statistics/Settings.hpp
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
