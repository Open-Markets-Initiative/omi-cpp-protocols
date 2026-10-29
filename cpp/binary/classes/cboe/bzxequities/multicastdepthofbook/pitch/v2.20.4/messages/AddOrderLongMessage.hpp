#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/AddFlags.hpp"
#include "../common/Decimal.hpp"
#include "../enums/SideIndicator.hpp"
#include "../messages/Message.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

class Visitor;

// Add Order message (long)
class AddOrderLongMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AddOrderLongMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    AddOrderLongMessage() = default;
    AddOrderLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity_binary_4, const std::string& symbol_short, Decimal price_binary_long_price_8, const AddFlags& add_flags);

    // Time Offset: Nanosecond offset from last
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Side Indicator: "B" = Buy Order "S" = Sell Order
    SideIndicator side_indicator() const;
    void set_side_indicator(SideIndicator value);

    // Quantity Binary 4: Number of shares/contracts being added to the book (may be less than
    // the number entered)
    std::uint32_t quantity_binary_4() const;
    void set_quantity_binary_4(std::uint32_t value);

    // Symbol Short: Symbol right padded with spaces
    const std::string& symbol_short() const;
    std::string& symbol_short();
    void set_symbol_short(const std::string& value);

    // Price Binary Long Price 8: The limit order price
    Decimal price_binary_long_price_8() const;
    void set_price_binary_long_price_8(Decimal value);

    // Add Flags: Add Flags
    const AddFlags& add_flags() const;
    AddFlags& add_flags();
    void set_add_flags(const AddFlags& value);

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
    std::uint32_t quantity_binary_4_{};
    std::string symbol_short_{};
    Decimal price_binary_long_price_8_{ 0, -4 };
    AddFlags add_flags_{};
};

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
