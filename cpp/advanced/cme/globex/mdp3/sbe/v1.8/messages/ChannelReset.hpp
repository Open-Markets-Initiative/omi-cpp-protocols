#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/ApplId.hpp"
#include "../structs/GroupSize.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

#pragma pack(push, 1)
struct channel_reset_groups_entry {
    sbe_mdp3::appl_id appl_id;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Channel Reset
struct channel_reset {

    struct fields_type {
        sbe_mdp3::transact_time transact_time;
        sbe_mdp3::match_event_indicator match_event_indicator;
    };

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, template_id::enum_type::channel_reset, schema_id::enum_type::mktdata, version(8)};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_mdp3::message_header) - sizeof(fields_type) - sizeof(sbe_mdp3::message_size);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = message_size.get().value();
        return sz == sizeof(sbe_mdp3::message_header) + sizeof(fields_type) + sizeof(sbe_mdp3::message_size)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_mdp3::message_header) - sizeof(fields_type) - sizeof(sbe_mdp3::message_size));
    }

    // sequential access to variable-length regions
    sbe_group_iterator<channel_reset_groups_entry, group_size> channel_reset_groups() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static channel_reset* parse(std::byte* buffer) {
        return reinterpret_cast<channel_reset*>(buffer);
    }

    // parse method const
    static const channel_reset* parse(const std::byte* buffer) {
        return reinterpret_cast<const channel_reset*>(buffer);
    }

};

// layout verification
static_assert(offsetof(channel_reset::fields_type, transact_time) == 0, "unexpected offset of channel_reset::fields_type::transact_time");
static_assert(offsetof(channel_reset::fields_type, match_event_indicator) == 8, "unexpected offset of channel_reset::fields_type::match_event_indicator");
static_assert(sizeof(channel_reset::fields_type) == 9, "unexpected sizeof channel_reset::fields_type");

#pragma pack(pop)
}

#include "details/ChannelResetWriter.hpp"
#include "details/ChannelResetReader.hpp"
