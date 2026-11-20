// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/TradeCancelledTermsMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class Visitor;

// Trade Cancelled Terms Message
class TradeCancelledTermsMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MsgType::TradeCancelledTermsMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 21;

    TradeCancelledTermsMessage() = default;
    TradeCancelledTermsMessage(const std::string& symbol, std::optional<std::uint32_t> trade_number, std::optional<std::chrono::microseconds> trading_system_time_stamp);

    // Symbol: A Unique Alphanumeric Identifier For A Security
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Trade Number: A Unique Identifier Per Stock Assigned To Each Trade
    std::optional<std::uint32_t> trade_number() const;
    void set_trade_number(std::optional<std::uint32_t> value);

    // Trading System Time Stamp: The Time At Which The Event Being Reported Occurred In The
    // Trading Engine
    std::optional<std::chrono::microseconds> trading_system_time_stamp() const;
    void set_trading_system_time_stamp(std::optional<std::chrono::microseconds> value);

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

    bool operator==(const TradeCancelledTermsMessage& other) const;
    bool operator!=(const TradeCancelledTermsMessage& other) const;

  private:
    std::string symbol_{};
    std::optional<std::uint32_t> trade_number_{};
    std::optional<std::chrono::microseconds> trading_system_time_stamp_{};
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
