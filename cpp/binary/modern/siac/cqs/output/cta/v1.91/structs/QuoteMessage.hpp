#pragma once

#include "../types/QuoteMessageType.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

struct QuoteMessage {

    QuoteMessageType quote_message_type;

    // parse method
    static QuoteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteMessage*>(buffer);
    }

    // parse method const
    static const QuoteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteMessage*>(buffer);
    }
};

#pragma pack(pop)
}
