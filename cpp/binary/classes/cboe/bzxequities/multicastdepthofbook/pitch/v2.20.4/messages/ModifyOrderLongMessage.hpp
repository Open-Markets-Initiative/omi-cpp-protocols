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

// Modify Order message (long)
class ModifyOrderLongMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ModifyOrderLongMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    ModifyOrderLongMessage() = default;
    ModifyOrderLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint32_t quantity_binary_4, Decimal price_binary_long_price_8, const ModifyFlags& modify_flags);

    // Time Offset: Nanosecond offset from last
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Quantity Binary 4: Number of shares/contracts being added to the book (may be less than
    // the number entered)
    std::uint32_t quantity_binary_4() const;
    void set_quantity_binary_4(std::uint32_t value);

    // Price Binary Long Price 8: The limit order price
    Decimal price_binary_long_price_8() const;
    void set_price_binary_long_price_8(Decimal value);

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

    bool operator==(const ModifyOrderLongMessage& other) const;
    bool operator!=(const ModifyOrderLongMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
    std::uint32_t quantity_binary_4_{};
    Decimal price_binary_long_price_8_{ 0, -4 };
    ModifyFlags modify_flags_{};
};

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
