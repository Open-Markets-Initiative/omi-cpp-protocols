#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

class Visitor;

// Sent whenever an execution on CIX ATS is amended
class TradeCorrectMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeCorrectMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 84;

    TradeCorrectMessage() = default;
    TradeCorrectMessage(std::uint16_t symbol_id, std::chrono::nanoseconds timestamp, std::uint64_t reserved_8, char reserved_1, const std::string& symbol, std::uint64_t execution_id, const std::string& broker, const std::string& contra_broker, std::uint64_t original_execution_id, Decimal original_trade_price, Decimal original_trade_quantity, Decimal corrected_trade_price, Decimal corrected_trade_quantity);

    // Symbol Id: Symbol Index
    std::uint16_t symbol_id() const;
    void set_symbol_id(std::uint16_t value);

    // Timestamp: Nanoseconds Since Epoch (UTC)
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Reserved 8: Reserved for future use
    std::uint64_t reserved_8() const;
    void set_reserved_8(std::uint64_t value);

    // Reserved 1: Reserved for future use
    char reserved_1() const;
    void set_reserved_1(char value);

    // Symbol: Stock Symbol
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Execution Id: Market Issued Unique Execution ID
    std::uint64_t execution_id() const;
    void set_execution_id(std::uint64_t value);

    // Broker: Three digit number Broker Number or 001 for anonymous
    const std::string& broker() const;
    std::string& broker();
    void set_broker(const std::string& value);

    // Contra Broker: Three digit number Broker Number of the contra order or 001 for anonymous
    const std::string& contra_broker() const;
    std::string& contra_broker();
    void set_contra_broker(const std::string& value);

    // Original Execution Id: Execution ID of the original trade being corrected
    std::uint64_t original_execution_id() const;
    void set_original_execution_id(std::uint64_t value);

    // Original Trade Price: Price of the trade being corrected
    Decimal original_trade_price() const;
    void set_original_trade_price(Decimal value);

    // Original Trade Quantity: Quantity of the trade being corrected
    Decimal original_trade_quantity() const;
    void set_original_trade_quantity(Decimal value);

    // Corrected Trade Price: Price the trade is being amended/corrected to
    Decimal corrected_trade_price() const;
    void set_corrected_trade_price(Decimal value);

    // Corrected Trade Quantity: Quantity the trade is being amended/corrected to
    Decimal corrected_trade_quantity() const;
    void set_corrected_trade_quantity(Decimal value);

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

    bool operator==(const TradeCorrectMessage& other) const;
    bool operator!=(const TradeCorrectMessage& other) const;

  private:
    std::uint16_t symbol_id_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t reserved_8_{};
    char reserved_1_{};
    std::string symbol_{};
    std::uint64_t execution_id_{};
    std::string broker_{};
    std::string contra_broker_{};
    std::uint64_t original_execution_id_{};
    Decimal original_trade_price_{ 0, -6 };
    Decimal original_trade_quantity_{ 0, -6 };
    Decimal corrected_trade_price_{ 0, -6 };
    Decimal corrected_trade_quantity_{ 0, -6 };
};

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
