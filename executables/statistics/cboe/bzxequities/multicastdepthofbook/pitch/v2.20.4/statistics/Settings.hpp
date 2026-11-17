// Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4: statistics/Settings.hpp
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
