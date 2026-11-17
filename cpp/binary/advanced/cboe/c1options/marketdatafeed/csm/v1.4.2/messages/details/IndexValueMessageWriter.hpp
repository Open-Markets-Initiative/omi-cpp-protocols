// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/details/IndexValueMessageWriter.hpp
#pragma once

#include "../IndexValueMessage.hpp"
#include <span>
#include <cstring>
#include <new>
#include <stdexcept>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

class index_value_message_group_writer;
class index_value_message_after_symbol;
class index_value_message_index_value_md_entry_writer;

// Stub builder — siblings > 1 not yet implemented. Group: packet.message.payload.indexvaluemessage.indexvaluemdentry
class index_value_message_index_value_md_entry_writer {
    public:
    index_value_message_index_value_md_entry_writer() = default;
    index_value_message_index_value_md_entry_writer(std::byte*, std::byte*, std::byte*) {}
    index_value_message_index_value_md_entry_writer& add_entry(const index_value_message_index_value_md_entry_entry&) { return *this; }
    std::byte* finish() { return nullptr; }
};

class index_value_message_after_symbol {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    index_value_message_after_symbol(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    index_value_message_index_value_md_entry_writer start_index_value_md_entry() {
        return { msg_start_, pos_, end_ };
    }
};

class index_value_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    index_value_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    index_value_message_after_symbol symbol(std::string_view v) {
        if (pos_ + sizeof(std::uint8_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<std::uint8_t*>(pos_) = static_cast<std::uint8_t>(v.size());
        std::memcpy(pos_ + sizeof(std::uint8_t), v.data(), v.size());
        auto* next_pos = pos_ + sizeof(std::uint8_t) + v.size();
        return { msg_start_, next_pos, end_ };
    }
};


inline index_value_message_group_writer start_group_write(index_value_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + index_value_message::tail_capacity };
}
}
