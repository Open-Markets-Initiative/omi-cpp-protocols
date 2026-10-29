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
#include "../enums/CustomerIndicator.hpp"
#include "../enums/SideIndicator.hpp"
#include "../messages/Message.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

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
    AddOrderExpandedMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t long_quantity, const std::string& expanded_symbol, Decimal long_price, const AddFlags& add_flags, const std::string& participant_id, CustomerIndicator customer_indicator);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Side Indicator: B = Buy Order S = Sell Order
    SideIndicator side_indicator() const;
    void set_side_indicator(SideIndicator value);

    // Long Quantity: Number of shares/contracts being added to the book (may be less than the
    // number entered).
    std::uint32_t long_quantity() const;
    void set_long_quantity(std::uint32_t value);

    // Expanded Symbol: Symbol right padded with spaces.
    const std::string& expanded_symbol() const;
    std::string& expanded_symbol();
    void set_expanded_symbol(const std::string& value);

    // Long Price: The limit order price
    Decimal long_price() const;
    void set_long_price(Decimal value);

    // Add Flags: Add Flags bitfield struct
    const AddFlags& add_flags() const;
    AddFlags& add_flags();
    void set_add_flags(const AddFlags& value);

    // Participant Id: Optionally specified. If specified, MPID (equities) or Executing Broker
    // (options) of firm attributed to this quote. Alternatively “RTAL” for retail specified
    // orders (equities). Space filled otherwise.
    const std::string& participant_id() const;
    std::string& participant_id();
    void set_participant_id(const std::string& value);

    // Customer Indicator: BZX/EDGX Options Only (space filled on C2 Options and all equities
    // markets). N = Non-Customer C = Customer
    CustomerIndicator customer_indicator() const;
    void set_customer_indicator(CustomerIndicator value);

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
    std::uint32_t long_quantity_{};
    std::string expanded_symbol_{};
    Decimal long_price_{ 0, -4 };
    AddFlags add_flags_{};
    std::string participant_id_{};
    CustomerIndicator customer_indicator_{};
};

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
