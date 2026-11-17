// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/details/SummaryMessageWriter.hpp
#pragma once

#include "../SummaryMessage.hpp"
#include <span>
#include <cstring>
#include <new>
#include <stdexcept>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

class summary_message_group_writer;
class summary_message_summary_md_entry_writer;

class summary_message_summary_md_entry_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    uint8_t count_ = 0;

public:
    summary_message_summary_md_entry_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    summary_message_summary_md_entry_writer& add_entry(const csm_marketdatafeed::summary_message_summary_md_entry_entry& entry) {
        if (pos_ + sizeof(entry) > end_)
            throw std::runtime_error("buffer overrun writing external-count group entry");
        std::memcpy(pos_, &entry, sizeof(entry));
        pos_ += sizeof(entry);
        ++count_;
        return *this;
    }

    std::span<std::byte> finish() {
        reinterpret_cast<csm_marketdatafeed::summary_message*>(msg_start_)->fields.no_entries.set(count_);
        reinterpret_cast<csm_marketdatafeed::message_header*>(msg_start_)->message_length.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class summary_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    summary_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    summary_message_summary_md_entry_writer start_summary_md_entry() {
        return { msg_start_, pos_, end_ };
    }
};


inline summary_message_group_writer start_group_write(summary_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + summary_message::tail_capacity };
}
}
