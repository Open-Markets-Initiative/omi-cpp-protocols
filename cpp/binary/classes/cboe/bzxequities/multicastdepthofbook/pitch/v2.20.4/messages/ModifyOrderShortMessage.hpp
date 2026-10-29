#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/ModifyFlags.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

class Visitor;

// Modify Order message (short)
class ModifyOrderShortMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ModifyOrderShortMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    ModifyOrderShortMessage() = default;
    ModifyOrderShortMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint16_t quantity_binary_2, Decimal price_binary_short_price_2, const ModifyFlags& modify_flags);

    // Time Offset: Nanosecond offset from last
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Quantity Binary 2: Number of shares/contracts being added to the book (may be less than
    // the number entered)
    std::uint16_t quantity_binary_2() const;
    void set_quantity_binary_2(std::uint16_t value);

    // Price Binary Short Price 2: The limit order price
    Decimal price_binary_short_price_2() const;
    void set_price_binary_short_price_2(Decimal value);

    // Modify Flags: Modify Flags
    const ModifyFlags& modify_flags() const;
    ModifyFlags& modify_flags();
    void set_modify_flags(const ModifyFlags& value);

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

    bool operator==(const ModifyOrderShortMessage& other) const;
    bool operator!=(const ModifyOrderShortMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
    std::uint16_t quantity_binary_2_{};
    Decimal price_binary_short_price_2_{ 0, -2 };
    ModifyFlags modify_flags_{};
};

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
