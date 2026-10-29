#pragma once

#include "../types/SymbolIndex.hpp"
#include "../types/Symbol.hpp"
#include "../types/Reserved1.hpp"
#include "../types/MarketId.hpp"
#include "../types/SystemId.hpp"
#include "../types/ExchangeCode.hpp"
#include "../types/PriceScaleCode.hpp"
#include "../types/SecurityType.hpp"
#include "../types/LotSize.hpp"
#include "../types/PrevClosePrice.hpp"
#include "../types/PrevCloseVolume.hpp"
#include "../types/PriceResolution.hpp"
#include "../types/RoundLot.hpp"
#include "../types/Mpv.hpp"
#include "../types/UnitOfTrade.hpp"
#include "../types/Reserved2.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

#pragma pack(push, 1)

// This message is published over the real-time data channels at system startup or in the context of a refresh sequence after a Matching Engine or XDP Publisher failover. It provides referential data for a single specified symbol.
struct SymbolIndexMappingMessage {

    SymbolIndex symbol_index;
    Symbol symbol;
    Reserved1 reserved_1;
    MarketId market_id;
    SystemId system_id;
    ExchangeCode exchange_code;
    PriceScaleCode price_scale_code;
    SecurityType security_type;
    LotSize lot_size;
    PrevClosePrice prev_close_price;
    PrevCloseVolume prev_close_volume;
    PriceResolution price_resolution;
    RoundLot round_lot;
    Mpv mpv;
    UnitOfTrade unit_of_trade;
    Reserved2 reserved_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 3;

    // parse method
    static SymbolIndexMappingMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolIndexMappingMessage*>(buffer);
    }

    // parse method const
    static const SymbolIndexMappingMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolIndexMappingMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SymbolIndexMappingMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SymbolIndexMappingMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
