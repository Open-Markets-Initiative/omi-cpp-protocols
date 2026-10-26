#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/CurrentTradingState.hpp"
#include "../enums/SecurityClass.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

class Visitor;

// Nasdaq uses this administrative message to indicate the current trading status of a security
// to the trading community.
class StockTradingActionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::StockTradingActionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 22;

    StockTradingActionMessage() = default;
    StockTradingActionMessage(std::uint16_t tracking_number, std::chrono::nanoseconds time_stamp, const std::string& stock, SecurityClass security_class, CurrentTradingState current_trading_state, const std::string& reason);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Time Stamp: Timestamp
    std::chrono::nanoseconds time_stamp() const;
    void set_time_stamp(std::chrono::nanoseconds value);
    std::int64_t time_stamp_utc(const calendar::Day& day) const;

    // Stock: Denotes the security symbol for the issue in the execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Security Class: Indicates the primary listing market for the issue.
    SecurityClass security_class() const;
    void set_security_class(SecurityClass value);

    // Current Trading State: Reflects the current trading state for the issue.
    CurrentTradingState current_trading_state() const;
    void set_current_trading_state(CurrentTradingState value);

    // Reason: Reflects the Market Ops or MarketWatch code for the trading state change.
    const std::string& reason() const;
    std::string& reason();
    void set_reason(const std::string& value);

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

    bool operator==(const StockTradingActionMessage& other) const;
    bool operator!=(const StockTradingActionMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds time_stamp_{};
    std::string stock_{};
    SecurityClass security_class_{};
    CurrentTradingState current_trading_state_{};
    std::string reason_{};
};

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
