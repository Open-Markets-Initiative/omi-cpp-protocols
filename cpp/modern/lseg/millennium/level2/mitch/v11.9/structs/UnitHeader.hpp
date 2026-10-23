#pragma once

#include "../types/Length.hpp"
#include "../types/MessageCount.hpp"
#include "../types/MarketDataGroup.hpp"
#include "../types/SequenceNumber.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

struct UnitHeader {

    Length length;
    MessageCount message_count;
    MarketDataGroup market_data_group;
    SequenceNumber sequence_number;

    // parse method
    static UnitHeader* parse(std::byte* buffer) {
        return reinterpret_cast<UnitHeader*>(buffer);
    }

    // parse method const
    static const UnitHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnitHeader*>(buffer);
    }
};

#pragma pack(pop)
}
