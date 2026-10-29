#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

class Visitor;

// A new resting order added to the book
class NewOrderAddMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::NewOrderAddMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 50;

    NewOrderAddMessage() = default;
    NewOrderAddMessage(std::chrono::nanoseconds timestamp, std::uint16_t symbol_id, std::uint64_t order_id, Side side, Decimal quantity, const std::string& symbol, Decimal price, const std::string& broker, char reserved_1);

    // Timestamp: Nanoseconds Since Epoch (UTC)
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol Id: Symbol Index
    std::uint16_t symbol_id() const;
    void set_symbol_id(std::uint16_t value);

    // Order Id: Market Issued Unique Order ID
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Side: Side of the order
    Side side() const;
    void set_side(Side value);

    // Quantity: Quantity - 6 implied decimals
    Decimal quantity() const;
    void set_quantity(Decimal value);

    // Symbol: Stock Symbol
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Price: Price - 6 implied decimals
    Decimal price() const;
    void set_price(Decimal value);

    // Broker: Three digit number Broker Number or 001 for anonymous
    const std::string& broker() const;
    std::string& broker();
    void set_broker(const std::string& value);

    // Reserved 1: Reserved for future use
    char reserved_1() const;
    void set_reserved_1(char value);

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

    bool operator==(const NewOrderAddMessage& other) const;
    bool operator!=(const NewOrderAddMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t symbol_id_{};
    std::uint64_t order_id_{};
    Side side_{};
    Decimal quantity_{ 0, -6 };
    std::string symbol_{};
    Decimal price_{ 0, -6 };
    std::string broker_{};
    char reserved_1_{};
};

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
