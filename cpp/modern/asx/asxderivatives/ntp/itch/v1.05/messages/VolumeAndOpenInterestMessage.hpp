#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/CumulativeVolume.hpp"
#include "../types/OpenInterest.hpp"
#include "../types/VoiTradeDate.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message disseminates Volume and Open Interest (VOI) information for each trade date
struct VolumeAndOpenInterestMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    CumulativeVolume cumulative_volume;
    OpenInterest open_interest;
    VoiTradeDate voi_trade_date;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'V';

    // parse method
    static VolumeAndOpenInterestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<VolumeAndOpenInterestMessage*>(buffer);
    }

    // parse method const
    static const VolumeAndOpenInterestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const VolumeAndOpenInterestMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const VolumeAndOpenInterestMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const VolumeAndOpenInterestMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
