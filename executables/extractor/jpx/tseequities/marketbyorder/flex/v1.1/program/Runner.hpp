#pragma once

#include "Settings.hpp"
#include "../extractor/Extractor.hpp"

namespace program {

// Drives the packet extractor against parsed program options.
struct Runner {
    const Options& options;

    explicit Runner(const Options& options) : options{ options } {}

    int run() const {
        return extractor::sample(options.pcap, options.output);
    }
};

} // namespace program
