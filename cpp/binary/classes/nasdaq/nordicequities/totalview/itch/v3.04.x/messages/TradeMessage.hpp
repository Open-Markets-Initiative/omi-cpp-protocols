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
#include "../enums/TradeType.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

class Visitor;

// Execution details for a match involving non displayable order types
class TradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 43;

    TradeMessage() = default;
    TradeMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t order_reference_number, TradeType trade_type, std::uint32_t quantity, std::uint32_t order_book, std::uint32_t match_number, Decimal trade_price, const std::string& participant_id_buyer, const std::string& participant_id_seller);

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

    // Trade Type: Where a non displayed order has been executed
    TradeType trade_type() const;
    void set_trade_type(TradeType value);

    // Quantity: Total number of shares in the order
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

    // Order Book: Order book id
    std::uint32_t order_book() const;
    void set_order_book(std::uint32_t value);

    // Match Number: Day unique match number of this execution
    std::uint32_t match_number() const;
    void set_match_number(std::uint32_t value);

    // Trade Price: The price at which the order execution occurred
    Decimal trade_price() const;
    void set_trade_price(Decimal value);

    // Participant Id Buyer: The Mpid of the buyer, if public
    const std::string& participant_id_buyer() const;
    std::string& participant_id_buyer();
    void set_participant_id_buyer(const std::string& value);

    // Participant Id Seller: The Mpid of the seller, if public
    const std::string& participant_id_seller() const;
    std::string& participant_id_seller();
    void set_participant_id_seller(const std::string& value);

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

    bool operator==(const TradeMessage& other) const;
    bool operator!=(const TradeMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t tracking_number_{};
    std::uint64_t order_reference_number_{};
    TradeType trade_type_{};
    std::uint32_t quantity_{};
    std::uint32_t order_book_{};
    std::uint32_t match_number_{};
    Decimal trade_price_{ 0, -4 };
    std::string participant_id_buyer_{};
    std::string participant_id_seller_{};
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
