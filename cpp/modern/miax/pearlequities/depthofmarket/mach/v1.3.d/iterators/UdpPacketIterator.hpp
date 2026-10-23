#pragma once

#include "../definitions.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {
// UdpPacketIterator
struct UdpPacketIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    std::uint8_t mach_packet_type = 0;
    std::uint16_t mach_packet_length = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;

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

        if (current + sizeof(MachMessage) > end) {
            return false;
        }

        const auto* header = MachMessage::parse(current);
        message = current + sizeof(MachMessage);

        mach_packet_type = header->mach_packet_type.get();
        mach_packet_length = header->mach_packet_length.get();

        current += mach_packet_length;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        message = nullptr;
        mach_packet_type = 0;
        mach_packet_length = 0;
    }
};
}
