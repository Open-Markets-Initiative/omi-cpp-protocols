#pragma once

#include "../types/SecurityIdOptional.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/NewsSource.hpp"
#include "../types/LanguageCode.hpp"
#include "../types/PartCount.hpp"
#include "../types/PartNumber.hpp"
#include "../types/NewsId.hpp"
#include "../types/OrigTime.hpp"
#include "../types/TotalTextLength.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

#pragma pack(push, 1)

// News_5Message
struct News5Message {

    SecurityIdOptional security_id_optional;
    MatchEventIndicator match_event_indicator;
    NewsSource news_source;
    LanguageCode language_code;
    PartCount part_count;
    PartNumber part_number;
    NewsId news_id;
    OrigTime orig_time;
    TotalTextLength total_text_length;

    // parse method
    static News5Message* parse(std::byte* buffer) {
        return reinterpret_cast<News5Message*>(buffer);
    }

    // parse method const
    static const News5Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const News5Message*>(buffer);
    }
};

#pragma pack(pop)
}
