// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: iterators/MachMessageIterator.hpp
#pragma once

#include "../definitions.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {
// MachMessageIterator
struct MachMessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const MachPacketHeader* mach_packet_header = nullptr;

    std::uint8_t mach_packet_type = 0;
    std::uint16_t mach_packet_length = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;
        mach_packet_header = nullptr;

        current = data;
        message = nullptr;

        mach_packet_type = 0;
        mach_packet_length = 0;
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
        mach_packet_header = header;
        message = current + sizeof(MachPacketHeader);

        mach_packet_type = header->mach_packet_type.get();
        mach_packet_length = header->mach_packet_length.get();

        current += mach_packet_length;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        mach_packet_header = nullptr;
        message = nullptr;
        mach_packet_type = 0;
        mach_packet_length = 0;
    }
};
}
