#pragma once

#include "../definitions.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {
// MachMessageIterator
struct MachMessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    std::uint8_t packet_type = 0;
    std::uint16_t packet_length = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;

        current = data;
        message = nullptr;

        packet_type = 0;
        packet_length = 0;
    }

    // next message
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(MachPacketHeader) > end) {
            return false;
        }

        const auto* header = MachPacketHeader::parse(current);
        message = current + sizeof(MachPacketHeader);

        packet_type = header->packet_type.get();
        packet_length = header->packet_length.get();

        current += packet_length;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        message = nullptr;
        packet_type = 0;
        packet_length = 0;
    }
};
}
