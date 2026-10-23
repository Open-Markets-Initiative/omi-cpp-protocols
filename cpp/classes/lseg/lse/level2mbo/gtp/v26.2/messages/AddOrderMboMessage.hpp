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
#include "../enums/OrderBookType.hpp"
#include "../enums/Side.hpp"
#include "../enums/SourceVenue.hpp"
#include "../messages/Message.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

class Visitor;

// Indicates the first order of a given side of an MBO snapshot.
class AddOrderMboMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AddOrderMboMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 64;

    AddOrderMboMessage() = default;
    AddOrderMboMessage(std::chrono::nanoseconds timestamp, std::uint64_t order_id, Side side, Decimal size, std::uint64_t instrument, Decimal price, const std::array<std::byte, 8>& reserved_8, SourceVenue source_venue, OrderBookType order_book_type, const std::string& participant, std::uint8_t depth);

    // Timestamp: Time the message was generated.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Order Id: Unique identifier of the order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Side: Side of the order.
    Side side() const;
    void set_side(Side value);

    // Size: Displayed size of the order.
    Decimal size() const;
    void set_size(Decimal value);

    // Instrument: GTP Instrument identifier.
    std::uint64_t instrument() const;
    void set_instrument(std::uint64_t value);

    // Price: Limit price of the order.
    Decimal price() const;
    void set_price(Decimal value);

    // Reserved 8: Reserved for future use.
    const std::array<std::byte, 8>& reserved_8() const;
    std::array<std::byte, 8>& reserved_8();
    void set_reserved_8(const std::array<std::byte, 8>& value);

    // Source Venue: Venue from which market data is received for the instrument.
    SourceVenue source_venue() const;
    void set_source_venue(SourceVenue value);

    // Order Book Type: Order book the status applies to.
    OrderBookType order_book_type() const;
    void set_order_book_type(OrderBookType value);

    // Participant: Identity of trading participant that submitted the order.
    const std::string& participant() const;
    std::string& participant();
    void set_participant(const std::string& value);

    // Depth: Total number of orders disseminated including this one, on this side of the book
    // as indicated by Side field.
    std::uint8_t depth() const;
    void set_depth(std::uint8_t value);

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

    bool operator==(const AddOrderMboMessage& other) const;
    bool operator!=(const AddOrderMboMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t order_id_{};
    Side side_{};
    Decimal size_{ 0, -8 };
    std::uint64_t instrument_{};
    Decimal price_{ 0, -8 };
    std::array<std::byte, 8> reserved_8_{};
    SourceVenue source_venue_{};
    OrderBookType order_book_type_{};
    std::string participant_{};
    std::uint8_t depth_{};
};

} // namespace lseg::lse::level2mbo::gtp::v26_2
