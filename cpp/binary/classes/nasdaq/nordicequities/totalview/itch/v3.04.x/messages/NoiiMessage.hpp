#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/CrossType.hpp"
#include "../enums/ImbalanceDirection.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

class Visitor;

// Net order imbalance indicator disseminated during a cross auction
class NoiiMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::NoiiMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 60;

    NoiiMessage() = default;
    NoiiMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t paired_quantity, std::uint64_t imbalance_quantity, ImbalanceDirection imbalance_direction, std::uint32_t order_book, Decimal equilibrium_price, CrossType cross_type, Decimal best_bid_price, std::uint64_t best_bid_quantity, Decimal best_ask_price, std::uint64_t best_ask_quantity);

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

    // Imbalance Quantity: Shares not paired at the reference price
    std::uint64_t imbalance_quantity() const;
    void set_imbalance_quantity(std::uint64_t value);

    // Imbalance Direction: The market side of the order imbalance
    ImbalanceDirection imbalance_direction() const;
    void set_imbalance_direction(ImbalanceDirection value);

    // Order Book: Order book id
    std::uint32_t order_book() const;
    void set_order_book(std::uint32_t value);

    // Equilibrium Price: Equilibrium price if the order book is crossed
    Decimal equilibrium_price() const;
    void set_equilibrium_price(Decimal value);

    // Cross Type: The cross session the message is generated for
    CrossType cross_type() const;
    void set_cross_type(CrossType value);

    // Best Bid Price: Best bid price, or zero if the book is crossed
    Decimal best_bid_price() const;
    void set_best_bid_price(Decimal value);

    // Best Bid Quantity: Bid volume at top of book
    std::uint64_t best_bid_quantity() const;
    void set_best_bid_quantity(std::uint64_t value);

    // Best Ask Price: Best ask price, or zero if the book is crossed
    Decimal best_ask_price() const;
    void set_best_ask_price(Decimal value);

    // Best Ask Quantity: Ask volume at top of book
    std::uint64_t best_ask_quantity() const;
    void set_best_ask_quantity(std::uint64_t value);

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

    bool operator==(const NoiiMessage& other) const;
    bool operator!=(const NoiiMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t tracking_number_{};
    std::uint64_t paired_quantity_{};
    std::uint64_t imbalance_quantity_{};
    ImbalanceDirection imbalance_direction_{};
    std::uint32_t order_book_{};
    Decimal equilibrium_price_{ 0, -4 };
    CrossType cross_type_{};
    Decimal best_bid_price_{ 0, -4 };
    std::uint64_t best_bid_quantity_{};
    Decimal best_ask_price_{ 0, -4 };
    std::uint64_t best_ask_quantity_{};
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
