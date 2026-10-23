#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/OrderBookType.hpp"
#include "../enums/SessionChangeReason.hpp"
#include "../enums/SourceVenue.hpp"
#include "../enums/TradingStatus.hpp"
#include "../messages/Message.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

class Visitor;

// Used to communicate scheduled and unscheduled session changes. When sent in the recovery
// channel, used to indicate the current trading status of an instrument.
class InstrumentStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::InstrumentStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 27;

    InstrumentStatusMessage() = default;
    InstrumentStatusMessage(std::chrono::nanoseconds timestamp, std::uint64_t instrument, SourceVenue source_venue, TradingStatus trading_status, SessionChangeReason session_change_reason, const std::string& new_end_time, OrderBookType order_book_type);

    // Timestamp: Time the message was generated.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Instrument: GTP Instrument identifier.
    std::uint64_t instrument() const;
    void set_instrument(std::uint64_t value);

    // Source Venue: Venue from which market data is received for the instrument.
    SourceVenue source_venue() const;
    void set_source_venue(SourceVenue value);

    // Trading Status: Current trading status of the instrument.
    TradingStatus trading_status() const;
    void set_trading_status(TradingStatus value);

    // Session Change Reason: Reason the trading session changed.
    SessionChangeReason session_change_reason() const;
    void set_session_change_reason(SessionChangeReason value);

    // New End Time: New time the session will end. The field will contain only spaces if
    // Session Change Reason is '0' or the Session Change Reason is not present. New End Time
    // will be in terms of the local time on the server (i.e., not UTC).
    const std::string& new_end_time() const;
    std::string& new_end_time();
    void set_new_end_time(const std::string& value);

    // Order Book Type: Order book the status applies to.
    OrderBookType order_book_type() const;
    void set_order_book_type(OrderBookType value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const InstrumentStatusMessage& other) const;
    bool operator!=(const InstrumentStatusMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t instrument_{};
    SourceVenue source_venue_{};
    TradingStatus trading_status_{};
    SessionChangeReason session_change_reason_{};
    std::string new_end_time_{};
    OrderBookType order_book_type_{};
};

} // namespace lseg::lse::level2mbo::gtp::v26_2
