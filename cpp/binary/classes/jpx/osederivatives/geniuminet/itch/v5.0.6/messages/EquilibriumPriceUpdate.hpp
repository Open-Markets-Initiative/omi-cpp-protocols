#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

class Visitor;

// Provides changes in equilibrium price during auctions.
class EquilibriumPriceUpdate : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::EquilibriumPriceUpdate;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 52;

    EquilibriumPriceUpdate() = default;
    EquilibriumPriceUpdate(std::chrono::nanoseconds nanoseconds, std::uint32_t order_book_id, std::uint64_t available_bid_quantity_at_equilibrium_price, std::uint64_t available_ask_quantity_at_equilibrium_price, std::int32_t equilibrium_price, const std::array<std::byte, 24>& reserved_24);

    // Nanoseconds: Nanoseconds portion
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Order Book Id: Primary identifier of an order book
    std::uint32_t order_book_id() const;
    void set_order_book_id(std::uint32_t value);

    // Available Bid Quantity At Equilibrium Price: Quantity at equilibrium price on the bid
    // side
    std::uint64_t available_bid_quantity_at_equilibrium_price() const;
    void set_available_bid_quantity_at_equilibrium_price(std::uint64_t value);

    // Available Ask Quantity At Equilibrium Price: Quantity at equilibrium price on the ask
    // side
    std::uint64_t available_ask_quantity_at_equilibrium_price() const;
    void set_available_ask_quantity_at_equilibrium_price(std::uint64_t value);

    // Equilibrium Price: Equilibrium Price
    std::int32_t equilibrium_price() const;
    void set_equilibrium_price(std::int32_t value);

    // Reserved 24: Reserved
    const std::array<std::byte, 24>& reserved_24() const;
    std::array<std::byte, 24>& reserved_24();
    void set_reserved_24(const std::array<std::byte, 24>& value);

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

    bool operator==(const EquilibriumPriceUpdate& other) const;
    bool operator!=(const EquilibriumPriceUpdate& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t order_book_id_{};
    std::uint64_t available_bid_quantity_at_equilibrium_price_{};
    std::uint64_t available_ask_quantity_at_equilibrium_price_{};
    std::int32_t equilibrium_price_{};
    std::array<std::byte, 24> reserved_24_{};
};

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
