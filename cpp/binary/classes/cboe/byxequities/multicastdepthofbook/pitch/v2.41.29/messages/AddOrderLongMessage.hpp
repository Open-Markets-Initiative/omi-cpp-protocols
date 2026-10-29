#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/AddOrderFlags.hpp"
#include "../common/Decimal.hpp"
#include "../enums/SideIndicator.hpp"
#include "../messages/Message.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

class Visitor;

// An Add Order message represents a newly accepted visible order on the Cboe book
class AddOrderLongMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AddOrderLongMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    AddOrderLongMessage() = default;
    AddOrderLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity, const std::string& symbol_short, Decimal price, const AddOrderFlags& add_order_flags);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Side Indicator: Order Side
    SideIndicator side_indicator() const;
    void set_side_indicator(SideIndicator value);

    // Quantity: Instrument quantity added to the complex book (may be less than the number
    // entered).
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

    // Symbol Short: Symbol
    const std::string& symbol_short() const;
    std::string& symbol_short();
    void set_symbol_short(const std::string& value);

    // Price: The limit order price
    Decimal price() const;
    void set_price(Decimal value);

    // Add Order Flags: Add Order Flags
    const AddOrderFlags& add_order_flags() const;
    AddOrderFlags& add_order_flags();
    void set_add_order_flags(const AddOrderFlags& value);

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

    bool operator==(const AddOrderLongMessage& other) const;
    bool operator!=(const AddOrderLongMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
    SideIndicator side_indicator_{};
    std::uint32_t quantity_{};
    std::string symbol_short_{};
    Decimal price_{ 0, -4 };
    AddOrderFlags add_order_flags_{};
};

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
