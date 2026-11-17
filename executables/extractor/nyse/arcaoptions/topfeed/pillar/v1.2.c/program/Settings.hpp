// Nyse.ArcaOptions.TopFeed.Pillar.v1.2.c: program/Settings.hpp
#pragma once

#include <filesystem>
#include <string>

namespace program {

// Packet extractor command-line options.
struct Options {
    std::filesystem::path pcap;     // input pcap file
    std::filesystem::path output;   // output directory for sample pcaps
};

} // namespace program
