#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Group.hpp"
#include "../enums/ShortSellingState.hpp"
#include "../messages/SequencedMessage.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

class SequencedMessageVisitor;

// Short Selling Price Restriction State Message indicates the current short selling price
// restriction state of an orderbook.
class ShortSellingPriceRestrictionStateMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::ShortSellingPriceRestrictionStateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 13;

    ShortSellingPriceRestrictionStateMessage() = default;
    ShortSellingPriceRestrictionStateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t orderbook_id, const std::string& group, ShortSellingState short_selling_state);

    // Nanoseconds: Number of nanoseconds since last Timestamp Seconds Message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Orderbook Id: 4 digit Quick code.
    std::uint32_t orderbook_id() const;
    void set_orderbook_id(std::uint32_t value);

    // Group: Orderbook group identifier.
    const std::string& group() const;
    std::string& group();
    void set_group(const std::string& value);

    // Short Selling State: Current short selling price restriction state; values: 0 = No price
    // restriction, 1 = Price restriction in effect.
    ShortSellingState short_selling_state() const;
    void set_short_selling_state(ShortSellingState value);

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const ShortSellingPriceRestrictionStateMessage& other) const;
    bool operator!=(const ShortSellingPriceRestrictionStateMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t orderbook_id_{};
    std::string group_{};
    ShortSellingState short_selling_state_{};
};

} // namespace jnx::jnxequities::pts::itch::v1_7
