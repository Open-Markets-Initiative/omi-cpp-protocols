#pragma once

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "Result.hpp"
#include "../statistics/Settings.hpp"

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace packet {

    // pcap parser — wraps a PcapIterator so zip archives, glob patterns, and
    // multi-file merges all just work via one entry point.
    struct Parser {

        PcapIterator source;
        packet::Frame current_frame;

        const packet::Options& options;

        explicit Parser(const packet::Options& options)
          : source{ specs_from(options) }, options{ options } {}

        // load next pcap frame
        bool next() {
            return source.advance();
        }

        // parse frame and identify protocol
        result identify() {
            current_frame = packet::Frame{ source.data(), source.length() };

            if (current_frame.is_udp()) {
                return result::iex_iexequities_deep_iextp_v1_08;
            }

            return result::unknown;
        }

        // get current frame
        const Frame& frame() const {
            return current_frame;
        }

    private:

        static std::vector<std::pair<std::string, std::int64_t>>
        specs_from(const packet::Options& options) {
            return { { options.file, 0 } };
        }
    };
}