// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/MarketStateUpdateMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../enums/MarketState.hpp"
#include "../messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class Visitor;

// Market State Update Message
class MarketStateUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MsgType::MarketStateUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 10;

    MarketStateUpdateMessage() = default;
    MarketStateUpdateMessage(MarketState market_state, std::optional<std::uint8_t> stock_group, std::optional<std::chrono::microseconds> trading_system_time_stamp);

    // Market State: Indicates The Current Market State
    MarketState market_state() const;
    void set_market_state(MarketState value);

    // Stock Group: An Identifier Of The Stock Group
    std::optional<std::uint8_t> stock_group() const;
    void set_stock_group(std::optional<std::uint8_t> value);

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

    bool operator==(const MarketStateUpdateMessage& other) const;
    bool operator!=(const MarketStateUpdateMessage& other) const;

  private:
    MarketState market_state_{};
    std::optional<std::uint8_t> stock_group_{};
    std::optional<std::chrono::microseconds> trading_system_time_stamp_{};
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
