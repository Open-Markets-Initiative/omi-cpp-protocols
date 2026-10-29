#pragma once

#include "../types/SecurityId.hpp"
#include "../types/ClosePrice.hpp"
#include "../types/PrevClosePrice.hpp"
#include "../types/UpperCktLimit.hpp"
#include "../types/LowerCktLimit.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published whenever there is a change in the daily price range of the instrument.
struct InstrumentInfoMessage {

    SecurityId security_id;
    ClosePrice close_price;
    PrevClosePrice prev_close_price;
    UpperCktLimit upper_ckt_limit;
    LowerCktLimit lower_ckt_limit;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13203;

    // parse method
    static InstrumentInfoMessage* parse(std::byte* buffer) {
        return reinterpret_cast<InstrumentInfoMessage*>(buffer);
    }

    // parse method const
    static const InstrumentInfoMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrumentInfoMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const InstrumentInfoMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const InstrumentInfoMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
