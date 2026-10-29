#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/UnsequencedMessage.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

class UnsequencedMessageVisitor;

// A Cancel Order Message is used to request that an order be canceled
class CancelOrderMessage : public UnsequencedMessage {
  public:
    // The code that selects this message
    static constexpr UnsequencedMessageCode message_type = UnsequencedMessageType::CancelOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 8;

    CancelOrderMessage() = default;
    CancelOrderMessage(std::uint32_t order_token, std::uint32_t quantity);

    // Order Token: Must be unique per Ouch account within a trading day and increase on each
    // subsequent transaction
    std::uint32_t order_token() const;
    void set_order_token(std::uint32_t value);

    // Quantity: Number of shares
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

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

    bool operator==(const CancelOrderMessage& other) const;
    bool operator!=(const CancelOrderMessage& other) const;

  private:
    std::uint32_t order_token_{};
    std::uint32_t quantity_{};
};

} // namespace jnx::jnxequities::pts::ouch::v1_11
