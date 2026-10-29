#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/CurrentRefreshPkt.hpp"
#include "../types/TotalRefreshPkts.hpp"
#include "../structs/FullRefreshHeader.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

namespace pillar_topfeed = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;


#pragma pack(push, 1)

// Refresh Header Message
struct refresh_header_message {

    struct fields_type {
        pillar_topfeed::current_refresh_pkt current_refresh_pkt;
        pillar_topfeed::total_refresh_pkts total_refresh_pkts;
    };

    pillar_topfeed::message_header header = {std::uint16_t(sizeof(pillar_topfeed::message_header) + sizeof(fields_type)), message_type::enum_type::refresh_header_message};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(pillar_topfeed::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_size.get().value();
        return sz == sizeof(pillar_topfeed::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(pillar_topfeed::message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    // optional fixed-size appendage accessors
    const pillar_topfeed::full_refresh_header* full_refresh_header() const {
        return reinterpret_cast<const pillar_topfeed::full_refresh_header*>(tail_begin());
    }


    // parse method
    static refresh_header_message* parse(std::byte* buffer) {
        return reinterpret_cast<refresh_header_message*>(buffer);
    }

    // parse method const
    static const refresh_header_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const refresh_header_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(refresh_header_message::fields_type, current_refresh_pkt) == 0, "unexpected offset of refresh_header_message::fields_type::current_refresh_pkt");
static_assert(offsetof(refresh_header_message::fields_type, total_refresh_pkts) == 2, "unexpected offset of refresh_header_message::fields_type::total_refresh_pkts");
static_assert(sizeof(refresh_header_message::fields_type) == 4, "unexpected sizeof refresh_header_message::fields_type");

#pragma pack(pop)
}
