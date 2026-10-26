#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OptionId.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/ExpirationYear.hpp"
#include "../types/ExpirationMonth.hpp"
#include "../types/ExpirationDate.hpp"
#include "../types/ExplicitStrikePrice.hpp"
#include "../types/OptionType.hpp"
#include "../types/Source.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/OptionsClosingType.hpp"
#include "../types/Tradable.hpp"
#include "../types/Mpv.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// At the start of each trading day, NASDAQ disseminates options symbol directory messages for all active options symbols in the NASDAQ option system.
struct OptionsDirectoryMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    OptionId option_id;
    SecuritySymbol security_symbol;
    ExpirationYear expiration_year;
    ExpirationMonth expiration_month;
    ExpirationDate expiration_date;
    ExplicitStrikePrice explicit_strike_price;
    OptionType option_type;
    Source source;
    UnderlyingSymbol underlying_symbol;
    OptionsClosingType options_closing_type;
    Tradable tradable;
    Mpv mpv;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'R';

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
