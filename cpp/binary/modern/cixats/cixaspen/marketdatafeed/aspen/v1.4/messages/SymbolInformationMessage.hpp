#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SymbolId.hpp"
#include "../types/Symbol.hpp"
#include "../types/ListingMarket.hpp"
#include "../types/BoardLotSize.hpp"
#include "../structs/MessageHeader.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

#pragma pack(push, 1)

// Reference data for each symbol that may be traded
struct SymbolInformationMessage {

    Timestamp timestamp;
    SymbolId symbol_id;
    Symbol symbol;
    ListingMarket listing_market;
    BoardLotSize board_lot_size;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'B';

    // parse method
    static SymbolInformationMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolInformationMessage*>(buffer);
    }

    // parse method const
    static const SymbolInformationMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolInformationMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SymbolInformationMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SymbolInformationMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
