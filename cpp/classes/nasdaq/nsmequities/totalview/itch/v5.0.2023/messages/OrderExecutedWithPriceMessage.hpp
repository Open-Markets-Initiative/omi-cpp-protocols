#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Printable.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class Visitor;

// This message is sent whenever an order on the book is executed in whole or in part at a
// price different from the initial display price
class OrderExecutedWithPriceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderExecutedWithPriceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 35;

    OrderExecutedWithPriceMessage() = default;
    OrderExecutedWithPriceMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, std::uint32_t executed_shares, std::uint64_t match_number, Printable printable, Decimal execution_price);

    // Stock Locate: Locate Code uniquely assigned to the security symbol for the day
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Order Reference Number: The unique reference number assigned to the new order at the
    // time of receipt
    std::uint64_t order_reference_number() const;
    void set_order_reference_number(std::uint64_t value);

    // Executed Shares: The number of shares executed
    std::uint32_t executed_shares() const;
    void set_executed_shares(std::uint32_t value);

    // Match Number: The Nasdaq generated day-unique Match Number of this execution
    std::uint64_t match_number() const;
    void set_match_number(std::uint64_t value);

    // Printable: Indicates if the execution should be reflected on time and sale displays and
    // volume calculations
    Printable printable() const;
    void set_printable(Printable value);

    // Execution Price: The price at which the order execution occurred
    Decimal execution_price() const;
    void set_execution_price(Decimal value);

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

    bool operator==(const OrderExecutedWithPriceMessage& other) const;
    bool operator!=(const OrderExecutedWithPriceMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t order_reference_number_{};
    std::uint32_t executed_shares_{};
    std::uint64_t match_number_{};
    Printable printable_{};
    Decimal execution_price_{ 0, -4 };
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
