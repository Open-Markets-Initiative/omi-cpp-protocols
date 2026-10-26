#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/Printable.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

class Visitor;

// An order executed at a price different to its display price
class OrderExecutedWithPriceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderExecutedWithPriceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 39;

    OrderExecutedWithPriceMessage() = default;
    OrderExecutedWithPriceMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t order_reference_number, std::uint32_t executed_quantity, std::uint32_t match_number, Printable printable, Decimal trade_price, const std::string& mpid_owner, const std::string& mpid_counterparty);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Tracking Number: Nasdaq Nordic internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Order Reference Number: Unique reference number assigned to the new order
    std::uint64_t order_reference_number() const;
    void set_order_reference_number(std::uint64_t value);

    // Executed Quantity: The number of shares executed
    std::uint32_t executed_quantity() const;
    void set_executed_quantity(std::uint32_t value);

    // Match Number: Day unique match number of this execution
    std::uint32_t match_number() const;
    void set_match_number(std::uint32_t value);

    // Printable: Whether the execution should be reflected in statistics
    Printable printable() const;
    void set_printable(Printable value);

    // Trade Price: The price at which the order execution occurred
    Decimal trade_price() const;
    void set_trade_price(Decimal value);

    // Mpid Owner: The Mpid of the order, if public
    const std::string& mpid_owner() const;
    std::string& mpid_owner();
    void set_mpid_owner(const std::string& value);

    // Mpid Counterparty: The Mpid of the counterparty, if public
    const std::string& mpid_counterparty() const;
    std::string& mpid_counterparty();
    void set_mpid_counterparty(const std::string& value);

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
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t tracking_number_{};
    std::uint64_t order_reference_number_{};
    std::uint32_t executed_quantity_{};
    std::uint32_t match_number_{};
    Printable printable_{};
    Decimal trade_price_{ 0, -4 };
    std::string mpid_owner_{};
    std::string mpid_counterparty_{};
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
