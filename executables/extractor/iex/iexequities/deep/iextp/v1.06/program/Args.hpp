#pragma once

#include "Settings.hpp"

#include <stdexcept>
#include <string>

namespace program {

// Parse argv into program::Options.
inline Options args(int argc, char** argv) {
    if (argc != 3) {
        throw std::runtime_error(std::string("usage: ") + argv[0] + " <input.pcap> <output-dir>");
    }
    return Options{ argv[1], argv[2] };
}

} // namespace program
