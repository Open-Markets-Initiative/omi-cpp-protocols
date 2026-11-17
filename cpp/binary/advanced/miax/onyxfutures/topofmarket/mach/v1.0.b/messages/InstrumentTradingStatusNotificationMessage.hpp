// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/InstrumentTradingStatusNotificationMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/MarketState.hpp"
#include "../types/MessageType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

namespace mach_topofmarket = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

#pragma pack(push, 1)

// Instrument Trading Status Notification Message
struct instrument_trading_status_notification_message {

    struct fields_type {
        mach_topofmarket::timestamp timestamp;
        mach_topofmarket::instrument_id instrument_id;
        mach_topofmarket::trading_status trading_status;
        mach_topofmarket::market_state market_state;
    };

    mach_topofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_topofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_topofmarket::message_type message_type = mach_topofmarket::message_type::enum_type::instrument_trading_status_notification_message;

    fields_type fields;

    // parse method
    static instrument_trading_status_notification_message* parse(std::byte* buffer) {
        return reinterpret_cast<instrument_trading_status_notification_message*>(buffer);
    }

    // parse method const
    static const instrument_trading_status_notification_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const instrument_trading_status_notification_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(instrument_trading_status_notification_message::fields_type, timestamp) == 0, "unexpected offset of instrument_trading_status_notification_message::fields_type::timestamp");
static_assert(offsetof(instrument_trading_status_notification_message::fields_type, instrument_id) == 8, "unexpected offset of instrument_trading_status_notification_message::fields_type::instrument_id");
static_assert(offsetof(instrument_trading_status_notification_message::fields_type, trading_status) == 12, "unexpected offset of instrument_trading_status_notification_message::fields_type::trading_status");
static_assert(offsetof(instrument_trading_status_notification_message::fields_type, market_state) == 13, "unexpected offset of instrument_trading_status_notification_message::fields_type::market_state");
static_assert(sizeof(instrument_trading_status_notification_message::fields_type) == 14, "unexpected sizeof instrument_trading_status_notification_message::fields_type");
static_assert(sizeof(instrument_trading_status_notification_message) == sizeof(mach_topofmarket::mach_packet_header) + sizeof(mach_topofmarket::message_type) + 14, "unexpected sizeof instrument_trading_status_notification_message");

#pragma pack(pop)
}
