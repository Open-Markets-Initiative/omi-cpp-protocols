// Cboe.EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29: statistics/Settings.hpp
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
