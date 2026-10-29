#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Display.hpp"
#include "../enums/TimeInForce.hpp"
#include "../messages/UnsequencedMessage.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

class UnsequencedMessageVisitor;

// A Replace Order Message is used to modify an existing order
class ReplaceOrderMessage : public UnsequencedMessage {
  public:
    // The code that selects this message
    static constexpr UnsequencedMessageCode message_type = UnsequencedMessageType::ReplaceOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    ReplaceOrderMessage() = default;
    ReplaceOrderMessage(std::uint32_t existing_order_token, std::uint32_t replacement_order_token, std::uint32_t quantity, Decimal price, TimeInForce time_in_force, Display display, std::uint32_t minimum_quantity);

    // Existing Order Token: Must match current live order
    std::uint32_t existing_order_token() const;
    void set_existing_order_token(std::uint32_t value);

    // Replacement Order Token: Must be unique per Ouch account within a trading day and
    // increase on each subsequent transaction
    std::uint32_t replacement_order_token() const;
    void set_replacement_order_token(std::uint32_t value);

    // Quantity: Number of shares
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

    // Price: Order price
    Decimal price() const;
    void set_price(Decimal value);

    // Time In Force: How long the order remains in effect
    TimeInForce time_in_force() const;
    void set_time_in_force(TimeInForce value);

    // Display: Order handling instruction
    Display display() const;
    void set_display(Display value);

    // Minimum Quantity: Minimum acceptable quantity to execute
    std::uint32_t minimum_quantity() const;
    void set_minimum_quantity(std::uint32_t value);

    // UnsequencedMessage
    UnsequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(UnsequencedMessageVisitor& visitor) const override;
    std::unique_ptr<UnsequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const UnsequencedMessage& other) const override;

    bool operator==(const ReplaceOrderMessage& other) const;
    bool operator!=(const ReplaceOrderMessage& other) const;

  private:
    std::uint32_t existing_order_token_{};
    std::uint32_t replacement_order_token_{};
    std::uint32_t quantity_{};
    Decimal price_{ 0, -1 };
    TimeInForce time_in_force_{};
    Display display_{};
    std::uint32_t minimum_quantity_{};
};

} // namespace jnx::jnxequities::pts::ouch::v1_11
