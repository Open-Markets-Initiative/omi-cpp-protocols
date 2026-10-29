#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/CustomerIndicator.hpp"
#include "../enums/SideIndicator.hpp"
#include "../messages/Message.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

class Visitor;

// An Add Order message represents a newly accepted visible order on the Cboe book. Expanded
// version accommodates larger symbol sizes possible through the ISRA plan.
class AddOrderExpandedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AddOrderExpandedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 43;

    AddOrderExpandedMessage() = default;
    AddOrderExpandedMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity, const std::string& complex_instrument_id_8, Decimal price, const std::array<std::byte, 1>& reserved_1, const std::string& participant_id, CustomerIndicator customer_indicator, const std::string& client_id);

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

    // Complex Instrument Id 8: Complex Instrument Id right padded with spaces.
    const std::string& complex_instrument_id_8() const;
    std::string& complex_instrument_id_8();
    void set_complex_instrument_id_8(const std::string& value);

    // Price: The limit order price
    Decimal price() const;
    void set_price(Decimal value);

    // Reserved 1: Reserved
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Participant Id: Optionally specified. If specified the Executing Broker of firm
    // attributed to this quote.
    const std::string& participant_id() const;
    std::string& participant_id();
    void set_participant_id(const std::string& value);

    // Customer Indicator: Customer Indicator
    CustomerIndicator customer_indicator() const;
    void set_customer_indicator(CustomerIndicator value);

    // Client Id: Optional user specified value attributed to this quote. Space filled
    // otherwise.
    const std::string& client_id() const;
    std::string& client_id();
    void set_client_id(const std::string& value);

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
    std::string complex_instrument_id_8_{};
    Decimal price_{ 0, -4 };
    std::array<std::byte, 1> reserved_1_{};
    std::string participant_id_{};
    CustomerIndicator customer_indicator_{};
    std::string client_id_{};
};

} // namespace cboe::c1options::complex::pitch::v2_1_18
