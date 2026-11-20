// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/OrderCancelledTermsMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/OrderSide.hpp"
#include "../messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class Visitor;

// Order Cancelled Terms Message
class OrderCancelledTermsMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MsgType::OrderCancelledTermsMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    OrderCancelledTermsMessage() = default;
    OrderCancelledTermsMessage(const std::string& symbol, std::optional<std::uint16_t> broker_number, OrderSide order_side, std::optional<std::uint64_t> order_id, std::optional<std::chrono::microseconds> trading_system_time_stamp);

    // Symbol: A Unique Alphanumeric Identifier For A Security
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Broker Number: An Exchange Assigned Public Number Uniquely Identifying A Partici Pating
    // Organization
    std::optional<std::uint16_t> broker_number() const;
    void set_broker_number(std::optional<std::uint16_t> value);

    // Order Side: Market Side Of An Order
    OrderSide order_side() const;
    void set_order_side(OrderSide value);

    // Order Id: Public Numeric Identifier Assigned To An Order By The Trading System
    std::optional<std::uint64_t> order_id() const;
    void set_order_id(std::optional<std::uint64_t> value);

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

    bool operator==(const OrderCancelledTermsMessage& other) const;
    bool operator!=(const OrderCancelledTermsMessage& other) const;

  private:
    std::string symbol_{};
    std::optional<std::uint16_t> broker_number_{};
    OrderSide order_side_{};
    std::optional<std::uint64_t> order_id_{};
    std::optional<std::chrono::microseconds> trading_system_time_stamp_{};
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
