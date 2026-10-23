#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/PtModFlags.hpp"
#include "../enums/AuctionType.hpp"
#include "../messages/Message.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

class Visitor;

// Sent to report details of an auction
class AuctionTradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    AuctionTradeMessage() = default;
    AuctionTradeMessage(std::uint32_t nanosecond, std::uint32_t quantity, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, std::int64_t price, std::uint64_t trade_match_id, AuctionType auction_type, const PtModFlags& pt_mod_flags);

    // Nanosecond: Nanoseconds since last message, accurate to the nearest microsecond.
    std::uint32_t nanosecond() const;
    void set_nanosecond(std::uint32_t value);

    // Quantity: Displayed quantity of the order.
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

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

    // Trade Match Id: Unique identifier of the trade.
    std::uint64_t trade_match_id() const;
    void set_trade_match_id(std::uint64_t value);

    // Auction Type: Auction Type
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Pt Mod Flags: Indicates a trade cancellation or amendment
    const PtModFlags& pt_mod_flags() const;
    PtModFlags& pt_mod_flags();
    void set_pt_mod_flags(const PtModFlags& value);

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
    std::uint32_t nanosecond_{};
    std::uint32_t quantity_{};
    std::uint32_t instrument_id_{};
    std::array<std::byte, 1> reserved_a_{};
    std::array<std::byte, 1> reserved_b_{};
    std::int64_t price_{};
    std::uint64_t trade_match_id_{};
    AuctionType auction_type_{};
    PtModFlags pt_mod_flags_{};
};

} // namespace lseg::millennium::level2::mitch::v11_9
