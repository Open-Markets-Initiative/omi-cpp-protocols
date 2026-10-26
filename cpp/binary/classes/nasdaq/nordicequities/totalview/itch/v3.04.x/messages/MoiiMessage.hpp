#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/CrossLevel.hpp"
#include "../enums/CrossType.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

class Visitor;

// Auction on demand order imbalance indicator
class MoiiMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::MoiiMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    MoiiMessage() = default;
    MoiiMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t paired_quantity, std::uint32_t order_book, Decimal equilibrium_price, CrossType cross_type, CrossLevel cross_level);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Tracking Number: Nasdaq Nordic internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Paired Quantity: Shares eligible to match at the reference price
    std::uint64_t paired_quantity() const;
    void set_paired_quantity(std::uint64_t value);

    // Order Book: Order book id
    std::uint32_t order_book() const;
    void set_order_book(std::uint32_t value);

    // Equilibrium Price: Equilibrium price if the order book is crossed
    Decimal equilibrium_price() const;
    void set_equilibrium_price(Decimal value);

    // Cross Type: The cross session the message is generated for
    CrossType cross_type() const;
    void set_cross_type(CrossType value);

    // Cross Level: The level the cross is being generated for
    CrossLevel cross_level() const;
    void set_cross_level(CrossLevel value);

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

    bool operator==(const MoiiMessage& other) const;
    bool operator!=(const MoiiMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t tracking_number_{};
    std::uint64_t paired_quantity_{};
    std::uint32_t order_book_{};
    Decimal equilibrium_price_{ 0, -4 };
    CrossType cross_type_{};
    CrossLevel cross_level_{};
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
