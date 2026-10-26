#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

class Visitor;

// Sent whenever an order on the book is executed in whole or in part
class OrderExecutedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderExecutedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 34;

    OrderExecutedMessage() = default;
    OrderExecutedMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t order_reference_number, std::uint32_t executed_quantity, std::uint32_t match_number, const std::string& mpid, const std::string& mpid_counterparty);

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

    // Mpid: The Mpid of the order, if public
    const std::string& mpid() const;
    std::string& mpid();
    void set_mpid(const std::string& value);

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

    bool operator==(const OrderExecutedMessage& other) const;
    bool operator!=(const OrderExecutedMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t tracking_number_{};
    std::uint64_t order_reference_number_{};
    std::uint32_t executed_quantity_{};
    std::uint32_t match_number_{};
    std::string mpid_{};
    std::string mpid_counterparty_{};
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
