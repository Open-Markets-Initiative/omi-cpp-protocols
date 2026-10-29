#pragma once

#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/StrategyType.hpp"
#include "../types/Source.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/NumberOfLegs.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

#pragma pack(push, 1)

// Whenever a complex order is added in the system for an underlying, the order is normalized and results in either the creation of a new complex strategy or is added to an existing strategy. A Complex Strategy Message containing the strategy definition will be sent.
struct ComplexStrategyDirectoryMessage {

    Timestamp timestamp;
    StrategyId strategy_id;
    StrategyType strategy_type;
    Source source;
    UnderlyingSymbol underlying_symbol;
    NumberOfLegs number_of_legs;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'R';

    // parse method
    static ComplexStrategyDirectoryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexStrategyDirectoryMessage*>(buffer);
    }

    // parse method const
    static const ComplexStrategyDirectoryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexStrategyDirectoryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ComplexStrategyDirectoryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ComplexStrategyDirectoryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
