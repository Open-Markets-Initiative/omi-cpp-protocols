#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

class Visitor;

// Auction Trade messages are used to disseminate executions resulting from a complex auction.
class AuctionTradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    AuctionTradeMessage() = default;
    AuctionTradeMessage(std::chrono::nanoseconds time_offset, std::uint64_t auction_id, std::uint64_t execution_id, Decimal price, std::uint32_t quantity);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Auction Id: Day specific identifier assigned to this auction.
    std::uint64_t auction_id() const;
    void set_auction_id(std::uint64_t value);

    // Execution Id: Cboe generated day-unique execution identifier of this execution.
    // Execution Id is also referenced in the Trade Break message
    std::uint64_t execution_id() const;
    void set_execution_id(std::uint64_t value);

    // Price: The limit order price
    Decimal price() const;
    void set_price(Decimal value);

    // Quantity: Instrument quantity added to the complex book (may be less than the number
    // entered).
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

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

    bool operator==(const AuctionTradeMessage& other) const;
    bool operator!=(const AuctionTradeMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t auction_id_{};
    std::uint64_t execution_id_{};
    Decimal price_{ 0, -4 };
    std::uint32_t quantity_{};
};

} // namespace cboe::c1options::complex::pitch::v2_1_18
