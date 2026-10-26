#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/OrderBookType.hpp"
#include "../enums/SourceVenue.hpp"
#include "../messages/Message.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

class Visitor;

// Sent to instruct recipients to remove all orders from the order book for the specified
// instrument.
class OrderBookClearMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderBookClearMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 19;

    OrderBookClearMessage() = default;
    OrderBookClearMessage(std::chrono::nanoseconds timestamp, SourceVenue source_venue, std::uint64_t instrument, OrderBookType order_book_type);

    // Timestamp: Time the message was generated.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Source Venue: Venue from which market data is received for the instrument.
    SourceVenue source_venue() const;
    void set_source_venue(SourceVenue value);

    // Instrument: GTP Instrument identifier.
    std::uint64_t instrument() const;
    void set_instrument(std::uint64_t value);

    // Order Book Type: Order book the status applies to.
    OrderBookType order_book_type() const;
    void set_order_book_type(OrderBookType value);

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

    bool operator==(const OrderBookClearMessage& other) const;
    bool operator!=(const OrderBookClearMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    SourceVenue source_venue_{};
    std::uint64_t instrument_{};
    OrderBookType order_book_type_{};
};

} // namespace lseg::lse::level2mbo::gtp::v26_2
