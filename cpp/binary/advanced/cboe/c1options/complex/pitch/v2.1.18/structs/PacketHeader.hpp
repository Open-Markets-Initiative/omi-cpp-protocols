#pragma once

#include <cstddef>
#include "../types/Length.hpp"
#include "../types/MessageCount.hpp"
#include "../types/Unit.hpp"
#include "../types/Sequence.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

#pragma pack(push, 1)

struct packet_header {

    pitch_complex::length length;
    pitch_complex::message_count message_count;
    pitch_complex::unit unit;
    pitch_complex::sequence sequence;

    // parse method
    static packet_header* parse(std::byte* buffer) {
        return reinterpret_cast<packet_header*>(buffer);
    }

    // parse method const
    static const packet_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const packet_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(packet_header, length) == 0, "unexpected offset of packet_header::length");
static_assert(offsetof(packet_header, message_count) == 2, "unexpected offset of packet_header::message_count");
static_assert(offsetof(packet_header, unit) == 3, "unexpected offset of packet_header::unit");
static_assert(offsetof(packet_header, sequence) == 4, "unexpected offset of packet_header::sequence");
static_assert(sizeof(packet_header) == 8, "unexpected sizeof packet_header");

#pragma pack(pop)
}
