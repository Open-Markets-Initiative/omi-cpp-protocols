#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/ModifyOrderFlags.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

class Visitor;

// The Modify Order message is sent whenever an open order is visibly modified. The Order Id
// refers to the Order Id of the original Add Order message.
class ModifyOrderShortMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ModifyOrderShortMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    ModifyOrderShortMessage() = default;
    ModifyOrderShortMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint16_t quantity_short, Decimal price_short, const ModifyOrderFlags& modify_order_flags);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Quantity Short: Instrument quantity being added to the complex book (may be less than
    // the number entered).
    std::uint16_t quantity_short() const;
    void set_quantity_short(std::uint16_t value);

    // Price Short: The limit order price
    Decimal price_short() const;
    void set_price_short(Decimal value);

    // Modify Order Flags: Modify Order Flags
    const ModifyOrderFlags& modify_order_flags() const;
    ModifyOrderFlags& modify_order_flags();
    void set_modify_order_flags(const ModifyOrderFlags& value);

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
    std::uint16_t quantity_short_{};
    Decimal price_short_{ 0, -2 };
    ModifyOrderFlags modify_order_flags_{};
};

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29
