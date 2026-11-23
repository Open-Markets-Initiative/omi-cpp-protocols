// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/AssignCopNoOrdersMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class Visitor;

// Assign Cop No Orders Message
class AssignCopNoOrdersMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MsgType::AssignCopNoOrdersMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    AssignCopNoOrdersMessage() = default;
    AssignCopNoOrdersMessage(const std::string& symbol, std::optional<Decimal> calculated_opening_price, std::optional<std::chrono::nanoseconds> trading_system_time_stamp);

    // Symbol: A Unique Alphanumeric Identifier For A Security
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Calculated Opening Price: The Price At Which Orders Will Trade At The Open
    std::optional<Decimal> calculated_opening_price() const;
    void set_calculated_opening_price(std::optional<Decimal> value);

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

    bool operator==(const AssignCopNoOrdersMessage& other) const;
    bool operator!=(const AssignCopNoOrdersMessage& other) const;

  private:
    std::string symbol_{};
    std::optional<Decimal> calculated_opening_price_{};
    std::optional<std::chrono::nanoseconds> trading_system_time_stamp_{};
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
