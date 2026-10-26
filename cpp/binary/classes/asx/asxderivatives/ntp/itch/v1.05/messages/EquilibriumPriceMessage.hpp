#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// This message is disseminated in response to changes in the equilibrium price for an order
// book during a pre-open period
class EquilibriumPriceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::EquilibriumPriceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 42;

    EquilibriumPriceMessage() = default;
    EquilibriumPriceMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, Decimal equilibrium_price, std::uint64_t matched_quantity, std::uint64_t bid_quantity, std::uint64_t ask_quantity);

    // Nanoseconds: Nanoseconds portion of the Nanoseconds, accurate to 1,000 nanoseconds.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Trade Date: Trade Date. Represented as number of days since 1 January 1970.
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Tradeable Instrument Id: Identifier of the Order Book.
    std::uint32_t tradeable_instrument_id() const;
    void set_tradeable_instrument_id(std::uint32_t value);

    // Equilibrium Price: Price at which matching will occur.
    Decimal equilibrium_price() const;
    void set_equilibrium_price(Decimal value);

    // Matched Quantity: The indicative auction volume.
    std::uint64_t matched_quantity() const;
    void set_matched_quantity(std::uint64_t value);

    // Bid Quantity: Total Bid Quantity available for execution.
    std::uint64_t bid_quantity() const;
    void set_bid_quantity(std::uint64_t value);

    // Ask Quantity: Total Ask Quantity available for execution.
    std::uint64_t ask_quantity() const;
    void set_ask_quantity(std::uint64_t value);

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

    bool operator==(const EquilibriumPriceMessage& other) const;
    bool operator!=(const EquilibriumPriceMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    std::uint32_t tradeable_instrument_id_{};
    Decimal equilibrium_price_{ 0, -2 };
    std::uint64_t matched_quantity_{};
    std::uint64_t bid_quantity_{};
    std::uint64_t ask_quantity_{};
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
