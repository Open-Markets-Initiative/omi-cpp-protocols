#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/NoEntries.hpp"
#include "../types/MdEntryType.hpp"
#include "../structs/MdEntryPx.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)
struct index_value_message_index_value_md_entry_entry {
    csm_marketdatafeed::md_entry_type md_entry_type;
    csm_marketdatafeed::md_entry_px md_entry_px;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Index Value Message
struct index_value_message {

    struct fields_type {
        csm_marketdatafeed::no_entries no_entries;
    };

    csm_marketdatafeed::message_header header = {{}, template_id::enum_type::index_value_message, {}, {}};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(csm_marketdatafeed::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const { return tail + tail_capacity; }

    // sequential access to variable-length regions
    sbe_var_data symbol() const {
        return { tail_begin(), tail_end() };
    }

    external_count_iterator<index_value_message_index_value_md_entry_entry> index_value_md_entry(const std::byte* position) const {
        return { position, fields.no_entries.get().value(), tail_end() };
    }


    // parse method
    static index_value_message* parse(std::byte* buffer) {
        return reinterpret_cast<index_value_message*>(buffer);
    }

    // parse method const
    static const index_value_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const index_value_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(index_value_message::fields_type, no_entries) == 0, "unexpected offset of index_value_message::fields_type::no_entries");
static_assert(sizeof(index_value_message::fields_type) == 1, "unexpected sizeof index_value_message::fields_type");

#pragma pack(pop)
}
