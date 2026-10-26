#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/CrossType.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

class Visitor;

// The cross process has completed for a specific security
class CrossTradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::CrossTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 31;

    CrossTradeMessage() = default;
    CrossTradeMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint32_t quantity, std::uint32_t order_book, Decimal cross_price, std::uint32_t match_number, CrossType cross_type, std::uint32_t number_of_trades);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Tracking Number: Nasdaq Nordic internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Quantity: Total number of shares in the order
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

    // Order Book: Order book id
    std::uint32_t order_book() const;
    void set_order_book(std::uint32_t value);

    // Cross Price: The price at which the cross occurred
    Decimal cross_price() const;
    void set_cross_price(Decimal value);

    // Match Number: Day unique match number of this execution
    std::uint32_t match_number() const;
    void set_match_number(std::uint32_t value);

    // Cross Type: The cross session the message is generated for
    CrossType cross_type() const;
    void set_cross_type(CrossType value);

    // Number Of Trades: Number of trades in the cross
    std::uint32_t number_of_trades() const;
    void set_number_of_trades(std::uint32_t value);

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

    bool operator==(const CrossTradeMessage& other) const;
    bool operator!=(const CrossTradeMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t tracking_number_{};
    std::uint32_t quantity_{};
    std::uint32_t order_book_{};
    Decimal cross_price_{ 0, -4 };
    std::uint32_t match_number_{};
    CrossType cross_type_{};
    std::uint32_t number_of_trades_{};
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
