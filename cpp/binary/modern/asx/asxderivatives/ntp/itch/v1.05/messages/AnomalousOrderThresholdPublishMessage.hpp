#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/AotPrice.hpp"
#include "../types/AotUpperPrice.hpp"
#include "../types/AotLowerPrice.hpp"
#include "../types/EtrPrice.hpp"
#include "../types/EtrUpperPrice.hpp"
#include "../types/EtrLowerPrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message disseminates price band information to the market advising the setting, zeroing or adjusting of the Extreme Trade Range price, the Anomalous Order Threshold price and the associated ranges for a contract that requires Market Integrity Rules enforcement
struct AnomalousOrderThresholdPublishMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    AotPrice aot_price;
    AotUpperPrice aot_upper_price;
    AotLowerPrice aot_lower_price;
    EtrPrice etr_price;
    EtrUpperPrice etr_upper_price;
    EtrLowerPrice etr_lower_price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'W';

    // parse method
    static AnomalousOrderThresholdPublishMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AnomalousOrderThresholdPublishMessage*>(buffer);
    }

    // parse method const
    static const AnomalousOrderThresholdPublishMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AnomalousOrderThresholdPublishMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AnomalousOrderThresholdPublishMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AnomalousOrderThresholdPublishMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
