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

// Sent whenever an execution on CIX ATS is cancelled
class TradeCancelMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeCancelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 60;

    TradeCancelMessage() = default;
    TradeCancelMessage(std::uint16_t symbol_id, std::chrono::nanoseconds timestamp, std::uint64_t reserved_8, char reserved_1, Decimal shares, const std::string& symbol, Decimal price, std::uint64_t execution_id, const std::string& broker, const std::string& contra_broker);

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

    // Shares: Qty Executed - 6 implied decimals
    Decimal shares() const;
    void set_shares(Decimal value);

    // Symbol: Stock Symbol
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Price: Price - 6 implied decimals
    Decimal price() const;
    void set_price(Decimal value);

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

    bool operator==(const TradeCancelMessage& other) const;
    bool operator!=(const TradeCancelMessage& other) const;

  private:
    std::uint16_t symbol_id_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t reserved_8_{};
    char reserved_1_{};
    Decimal shares_{ 0, -6 };
    std::string symbol_{};
    Decimal price_{ 0, -6 };
    std::uint64_t execution_id_{};
    std::string broker_{};
    std::string contra_broker_{};
};

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
