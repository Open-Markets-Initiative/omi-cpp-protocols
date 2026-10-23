#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/AuctionType.hpp"
#include "../messages/Message.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

class Visitor;

// 9 Used to disseminate the indicative auction price and the tradable quantity and imbalance
// at this price.
class AuctionInfoMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionInfoMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    AuctionInfoMessage() = default;
    AuctionInfoMessage(std::uint32_t nanosecond, std::uint32_t paired_quantity, const std::array<std::byte, 4>& reserved_4, const std::array<std::byte, 1>& reserved_1, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, std::int64_t price, AuctionType auction_type);

    // Nanosecond: Nanoseconds since last message, accurate to the nearest microsecond.
    std::uint32_t nanosecond() const;
    void set_nanosecond(std::uint32_t value);

    // Paired Quantity: Quantity that will be matched at the indicative price.
    std::uint32_t paired_quantity() const;
    void set_paired_quantity(std::uint32_t value);

    // Reserved 4: Reserved field
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

    // Reserved 1: Reserved field
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Instrument Id: Instrument's symbol.
    std::uint32_t instrument_id() const;
    void set_instrument_id(std::uint32_t value);

    // Reserved A: Reserved field
    const std::array<std::byte, 1>& reserved_a() const;
    std::array<std::byte, 1>& reserved_a();
    void set_reserved_a(const std::array<std::byte, 1>& value);

    // Reserved B: Reserved field
    const std::array<std::byte, 1>& reserved_b() const;
    std::array<std::byte, 1>& reserved_b();
    void set_reserved_b(const std::array<std::byte, 1>& value);

    // Price: Limit price of the order.
    std::int64_t price() const;
    void set_price(std::int64_t value);

    // Auction Type: Auction Type
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

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

    bool operator==(const AuctionInfoMessage& other) const;
    bool operator!=(const AuctionInfoMessage& other) const;

  private:
    std::uint32_t nanosecond_{};
    std::uint32_t paired_quantity_{};
    std::array<std::byte, 4> reserved_4_{};
    std::array<std::byte, 1> reserved_1_{};
    std::uint32_t instrument_id_{};
    std::array<std::byte, 1> reserved_a_{};
    std::array<std::byte, 1> reserved_b_{};
    std::int64_t price_{};
    AuctionType auction_type_{};
};

} // namespace lseg::millennium::level2::mitch::v11_9
