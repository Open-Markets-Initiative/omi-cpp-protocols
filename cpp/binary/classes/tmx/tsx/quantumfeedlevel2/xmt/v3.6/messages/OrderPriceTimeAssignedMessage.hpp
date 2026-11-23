// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/OrderPriceTimeAssignedMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/OrderSide.hpp"
#include "../messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class Visitor;

// Order Price Time Assigned Message
class OrderPriceTimeAssignedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MsgType::OrderPriceTimeAssignedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 51;

    OrderPriceTimeAssignedMessage() = default;
    OrderPriceTimeAssignedMessage(const std::string& symbol, std::optional<std::uint16_t> broker_number, OrderSide order_side, std::optional<std::uint64_t> order_id, std::optional<Decimal> price, std::optional<std::uint32_t> volume, std::optional<std::chrono::microseconds> priority_time_stamp, std::optional<std::chrono::nanoseconds> trading_system_time_stamp);

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

    // Price: The Price In A Valid Currency
    std::optional<Decimal> price() const;
    void set_price(std::optional<Decimal> value);

    // Volume: The Quantity Of Shares For An Order Or Fill
    std::optional<std::uint32_t> volume() const;
    void set_volume(std::optional<std::uint32_t> value);

    // Priority Time Stamp: Time Stamp Assigned By The Trading Engine To Specify Time Priority
    // Of An Order Orders Are Sequenced In The Order Book Based On Symbol Price And Priority
    // Time Stamp
    std::optional<std::chrono::microseconds> priority_time_stamp() const;
    void set_priority_time_stamp(std::optional<std::chrono::microseconds> value);

    // Trading System Time Stamp: The Time At Which The Event Being Reported Occurred In The
    // Trading Engine
    std::optional<std::chrono::nanoseconds> trading_system_time_stamp() const;
    void set_trading_system_time_stamp(std::optional<std::chrono::nanoseconds> value);

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

    bool operator==(const OrderPriceTimeAssignedMessage& other) const;
    bool operator!=(const OrderPriceTimeAssignedMessage& other) const;

  private:
    std::string symbol_{};
    std::optional<std::uint16_t> broker_number_{};
    OrderSide order_side_{};
    std::optional<std::uint64_t> order_id_{};
    std::optional<Decimal> price_{};
    std::optional<std::uint32_t> volume_{};
    std::optional<std::chrono::microseconds> priority_time_stamp_{};
    std::optional<std::chrono::nanoseconds> trading_system_time_stamp_{};
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
