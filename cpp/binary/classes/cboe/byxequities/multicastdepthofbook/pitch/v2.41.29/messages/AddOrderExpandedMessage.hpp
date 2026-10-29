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

// An Add Order message represents a newly accepted visible order on the Cboe book. Expanded
// version accommodates larger symbol sizes possible through the ISRA plan.
class AddOrderExpandedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AddOrderExpandedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 39;

    AddOrderExpandedMessage() = default;
    AddOrderExpandedMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity, const std::string& symbol_long, Decimal price, const AddOrderFlags& add_order_flags, const std::string& participant_id, char customer_indicator);

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

    // Symbol Long: Symbol
    const std::string& symbol_long() const;
    std::string& symbol_long();
    void set_symbol_long(const std::string& value);

    // Price: The limit order price
    Decimal price() const;
    void set_price(Decimal value);

    // Add Order Flags: Add Order Flags
    const AddOrderFlags& add_order_flags() const;
    AddOrderFlags& add_order_flags();
    void set_add_order_flags(const AddOrderFlags& value);

    // Participant Id: Optionally specified. If specified the Executing Broker of firm
    // attributed to this quote.
    const std::string& participant_id() const;
    std::string& participant_id();
    void set_participant_id(const std::string& value);

    // Customer Indicator: Customer Indicator
    char customer_indicator() const;
    void set_customer_indicator(char value);

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

    bool operator==(const AddOrderExpandedMessage& other) const;
    bool operator!=(const AddOrderExpandedMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
    SideIndicator side_indicator_{};
    std::uint32_t quantity_{};
    std::string symbol_long_{};
    Decimal price_{ 0, -4 };
    AddOrderFlags add_order_flags_{};
    std::string participant_id_{};
    char customer_indicator_{};
};

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
