#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/ExpirationYear.hpp"
#include "../types/ExpirationMonth.hpp"
#include "../types/ExpirationDay.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/OptionType.hpp"
#include "../types/Source.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/OptionClosingType.hpp"
#include "../types/Tradable.hpp"
#include "../types/Mpv.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

#pragma pack(push, 1)

// At the start of each trading day, the options system disseminates directory messages for all symbols eligible for the auction process in the options system.
struct OptionsDirectoryMessage {

    Nanoseconds nanoseconds;
    OptionId option_id;
    SecuritySymbol security_symbol;
    ExpirationYear expiration_year;
    ExpirationMonth expiration_month;
    ExpirationDay expiration_day;
    StrikePrice strike_price;
    OptionType option_type;
    Source source;
    UnderlyingSymbol underlying_symbol;
    OptionClosingType option_closing_type;
    Tradable tradable;
    Mpv mpv;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'D';

    // parse method
    static OptionsDirectoryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsDirectoryMessage*>(buffer);
    }

    // parse method const
    static const OptionsDirectoryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsDirectoryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsDirectoryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsDirectoryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
