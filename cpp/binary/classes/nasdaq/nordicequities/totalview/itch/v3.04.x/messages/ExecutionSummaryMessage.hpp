#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/AggressingSide.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

class Visitor;

// Summary information disseminated before the individual trades
class ExecutionSummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ExecutionSummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 37;

    ExecutionSummaryMessage() = default;
    ExecutionSummaryMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint32_t order_book, AggressingSide aggressing_side, std::uint32_t quantity, std::uint32_t hidden_quantity, std::uint32_t stp_cancel_quantity, Decimal far_price, std::uint32_t add_quantity, std::uint16_t number_of_lit_executions);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Tracking Number: Nasdaq Nordic internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Order Book: Order book id
    std::uint32_t order_book() const;
    void set_order_book(std::uint32_t value);

    // Aggressing Side: Side of the incoming aggressive order
    AggressingSide aggressing_side() const;
    void set_aggressing_side(AggressingSide value);

    // Quantity: Total number of shares in the order
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

    // Hidden Quantity: Total hidden quantity matched
    std::uint32_t hidden_quantity() const;
    void set_hidden_quantity(std::uint32_t value);

    // Stp Cancel Quantity: Quantity deleted due to self trade prevention
    std::uint32_t stp_cancel_quantity() const;
    void set_stp_cancel_quantity(std::uint32_t value);

    // Far Price: Highest or lowest price of the match
    Decimal far_price() const;
    void set_far_price(Decimal value);

    // Add Quantity: Lit volume of the aggressive order added to the book
    std::uint32_t add_quantity() const;
    void set_add_quantity(std::uint32_t value);

    // Number Of Lit Executions: Total number of partial lit executions
    std::uint16_t number_of_lit_executions() const;
    void set_number_of_lit_executions(std::uint16_t value);

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

    bool operator==(const ExecutionSummaryMessage& other) const;
    bool operator!=(const ExecutionSummaryMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t tracking_number_{};
    std::uint32_t order_book_{};
    AggressingSide aggressing_side_{};
    std::uint32_t quantity_{};
    std::uint32_t hidden_quantity_{};
    std::uint32_t stp_cancel_quantity_{};
    Decimal far_price_{ 0, -4 };
    std::uint32_t add_quantity_{};
    std::uint16_t number_of_lit_executions_{};
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
