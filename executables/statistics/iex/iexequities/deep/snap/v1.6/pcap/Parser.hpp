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

        // packets read so far: 1 at the first, which is what a record cites
        std::uint64_t packet_number = 0;

        const packet::Options& options;

        explicit Parser(const packet::Options& options)
          : source{ specs_from(options) }, options{ options } {}

        // load the next pcap frame: after this, frame() is the frame advanced to
        bool next() {
            if (!source.advance()) { return false; }

            packet_number++;
            current_frame = packet::Frame{ source.data(), source.length() };
            return true;
        }

        // identify the loaded frame's protocol
        result identify() {
            if (current_frame.is_tcp()) {
                return result::iex_iexequities_deep_snap_v1_6;
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