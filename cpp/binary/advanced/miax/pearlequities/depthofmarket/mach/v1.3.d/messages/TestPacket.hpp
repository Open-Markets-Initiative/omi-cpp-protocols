// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/TestPacket.hpp
#pragma once

#include <cstddef>
#include "../structs/EsesmPacketHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;


#pragma pack(push, 1)

// Test Packet
struct test_packet {

    struct fields_type {
    };

    mach_depthofmarket::esesm_packet_header header = {std::uint16_t(sizeof(mach_depthofmarket::esesm_packet_header) - 2), esesm_packet_type::enum_type::test_packet};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(mach_depthofmarket::esesm_packet_header);

    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.esesm_packet_length.get().value();
        return (sz + 2) == sizeof(mach_depthofmarket::esesm_packet_header)
            ? tail + tail_capacity
            : tail + ((sz + 2) - sizeof(mach_depthofmarket::esesm_packet_header));
    }

    // sequential access to variable-length regions
    external_var_data test_text() const {
        return { tail_begin(), static_cast<std::size_t>(header.esesm_packet_length.get().value() - 1), tail_end() };
    }


    // parse method
    static test_packet* parse(std::byte* buffer) {
        return reinterpret_cast<test_packet*>(buffer);
    }

    // parse method const
    static const test_packet* parse(const std::byte* buffer) {
        return reinterpret_cast<const test_packet*>(buffer);
    }

};

// layout verification
static_assert(sizeof(test_packet::fields_type) == 1, "unexpected sizeof test_packet::fields_type");

#pragma pack(pop)
}

#include "details/TestPacketWriter.hpp"
#include "details/TestPacketReader.hpp"
