#pragma once

#include <iostream>
#include <string>
#include <cstring>

#include "pcap/Parser.hpp"
#include "statistics/Statistics.hpp"

// program settings
struct Settings {
    packet::Options pcap;
    statistics::Options statistics;
};

void print_usage(const char* program) {
    std::cout << "Usage: " << program << " [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -i, --input <file>   Input pcap file (required)" << std::endl;
    std::cout << "  -v, --verbose        Verbose output" << std::endl;
    std::cout << "  -h, --help           Show this help" << std::endl;
}

Settings args(const int argc, char** argv) {

    Settings settings;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--input" || arg == "-i") {
            if (i + 1 < argc) {
                settings.pcap.file = argv[++i];
            } else {
                std::cerr << "Error: --input requires a file path" << std::endl;
                exit(1);
            }
        }
        else if (arg == "--verbose" || arg == "-v") {
            settings.statistics.verbose = true;
        }
        else if (arg == "--help" || arg == "-h") {
            print_usage(argv[0]);
            exit(0);
        }
        else {
            std::cerr << "Unknown option: " << arg << std::endl;
            print_usage(argv[0]);
            exit(1);
        }
    }

    if (settings.pcap.file.empty()) {
        std::cerr << "Error: --input is required" << std::endl;
        print_usage(argv[0]);
        exit(1);
    }

    return settings;
}