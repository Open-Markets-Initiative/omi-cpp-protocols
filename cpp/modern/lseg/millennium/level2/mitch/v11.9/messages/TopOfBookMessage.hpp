#pragma once

#include "../types/Nanosecond.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/BuyLimitPrice.hpp"
#include "../types/BuyLimitSize.hpp"
#include "../types/SellLimitPrice.hpp"
#include "../types/SellLimitSize.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// Used to disseminate top of book changes when the instrument is in a scheduled level 1 only auction.
struct TopOfBookMessage {

    Nanosecond nanosecond;
    InstrumentId instrument_id;
    BuyLimitPrice buy_limit_price;
    BuyLimitSize buy_limit_size;
    SellLimitPrice sell_limit_price;
    SellLimitSize sell_limit_size;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x71;

    // parse method
    static TopOfBookMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TopOfBookMessage*>(buffer);
    }

    // parse method const
    static const TopOfBookMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TopOfBookMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TopOfBookMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TopOfBookMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
