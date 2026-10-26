#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/SecurityIdOptional.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/NewsSource.hpp"
#include "../types/LanguageCode.hpp"
#include "../types/PartCount.hpp"
#include "../types/PartNumber.hpp"
#include "../types/NewsId.hpp"
#include "../types/OrigTime.hpp"
#include "../types/TotalTextLength.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_2;


#pragma pack(push, 1)

// News 5 Message
struct news_5_message {

    struct fields_type {
        sbe_binaryumdf::security_id_optional security_id_optional;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::news_source news_source;
        sbe_binaryumdf::language_code language_code;
        sbe_binaryumdf::part_count part_count;
        sbe_binaryumdf::part_number part_number;
        sbe_binaryumdf::news_id news_id;
        sbe_binaryumdf::orig_time orig_time;
        sbe_binaryumdf::total_text_length total_text_length;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_binaryumdf::framing_header) - sizeof(fields_type) - sizeof(sbe_binaryumdf::message_header);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_length.get().value();
        return sz == sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_binaryumdf::framing_header) - sizeof(fields_type) - sizeof(sbe_binaryumdf::message_header));
    }

    // sequential access to variable-length regions
    sbe_var_data headline() const {
        return { tail_begin(), tail_end() };
    }

    sbe_var_data text(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data url_link(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static news_5_message* parse(std::byte* buffer) {
        return reinterpret_cast<news_5_message*>(buffer);
    }

    // parse method const
    static const news_5_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const news_5_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(news_5_message::fields_type, security_id_optional) == 0, "unexpected offset of news_5_message::fields_type::security_id_optional");
static_assert(offsetof(news_5_message::fields_type, match_event_indicator) == 8, "unexpected offset of news_5_message::fields_type::match_event_indicator");
static_assert(offsetof(news_5_message::fields_type, news_source) == 9, "unexpected offset of news_5_message::fields_type::news_source");
static_assert(offsetof(news_5_message::fields_type, language_code) == 10, "unexpected offset of news_5_message::fields_type::language_code");
static_assert(offsetof(news_5_message::fields_type, part_count) == 12, "unexpected offset of news_5_message::fields_type::part_count");
static_assert(offsetof(news_5_message::fields_type, part_number) == 14, "unexpected offset of news_5_message::fields_type::part_number");
static_assert(offsetof(news_5_message::fields_type, news_id) == 16, "unexpected offset of news_5_message::fields_type::news_id");
static_assert(offsetof(news_5_message::fields_type, orig_time) == 24, "unexpected offset of news_5_message::fields_type::orig_time");
static_assert(offsetof(news_5_message::fields_type, total_text_length) == 32, "unexpected offset of news_5_message::fields_type::total_text_length");
static_assert(sizeof(news_5_message::fields_type) == 36, "unexpected sizeof news_5_message::fields_type");

#pragma pack(pop)
}

#include "details/News5MessageWriter.hpp"
#include "details/News5MessageReader.hpp"
