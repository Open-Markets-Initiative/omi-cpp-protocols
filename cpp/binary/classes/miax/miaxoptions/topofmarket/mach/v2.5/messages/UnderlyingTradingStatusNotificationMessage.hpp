#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/EventReason.hpp"
#include "../enums/TradingStatus.hpp"
#include "../messages/Data.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class DataVisitor;

// This message format will be used to notify firms of changes to the trading status of all the
// options of an underlying.
class UnderlyingTradingStatusNotificationMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::UnderlyingTradingStatusNotificationMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    UnderlyingTradingStatusNotificationMessage() = default;
    UnderlyingTradingStatusNotificationMessage(std::chrono::nanoseconds nanoseconds, const std::string& underlying_symbol, TradingStatus trading_status, EventReason event_reason, std::uint32_t expected_event_time_seconds_part, std::uint32_t expected_event_time_nano_seconds_part);

    // Nanoseconds: Time at which this product is added/updated on MIAX system today.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Underlying Symbol: Stock Symbol for the option.
    const std::string& underlying_symbol() const;
    std::string& underlying_symbol();
    void set_underlying_symbol(const std::string& value);

    // Trading Status: Trading Status value
    TradingStatus trading_status() const;
    void set_trading_status(TradingStatus value);

    // Event Reason: Event Reason value
    EventReason event_reason() const;
    void set_event_reason(EventReason value);

    // Expected Event Time Seconds Part: Seconds portion of the expected time of the event.
    // Always use in conjunction with the Nano-seconds part field.
    std::uint32_t expected_event_time_seconds_part() const;
    void set_expected_event_time_seconds_part(std::uint32_t value);

    // Expected Event Time Nano Seconds Part: Nano-seconds portion of the expected time of the
    // event. Specifies number of nano-seconds since the seconds specified in "Expected Event
    // Time Seconds" field.
    std::uint32_t expected_event_time_nano_seconds_part() const;
    void set_expected_event_time_nano_seconds_part(std::uint32_t value);

    // Data
    DataCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(DataVisitor& visitor) const override;
    std::unique_ptr<Data> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Data& other) const override;

    bool operator==(const UnderlyingTradingStatusNotificationMessage& other) const;
    bool operator!=(const UnderlyingTradingStatusNotificationMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::string underlying_symbol_{};
    TradingStatus trading_status_{};
    EventReason event_reason_{};
    std::uint32_t expected_event_time_seconds_part_{};
    std::uint32_t expected_event_time_nano_seconds_part_{};
};

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
