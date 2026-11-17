// Databento.MarketData.Normalized.Dbn.v2: messages/BboMsg.hpp
#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../bitfields/Flags.hpp"
#include "../common/Decimal.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"
#include "../structs/BidAskPair.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

class Visitor;

// Subsampled market by price with a known book depth of 1; the record of the bbo-1s and bbo-1m
// schemas
class BboMsg : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = Rtype::Bbo1Minute;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 64;

    BboMsg() = default;
    BboMsg(std::optional<Decimal> price, std::uint32_t size, const std::array<std::byte, 1>& reserved_1, Side side, const Flags& flags, const std::array<std::byte, 1>& second_reserved_1, std::optional<std::chrono::nanoseconds> ts_recv, const std::array<std::byte, 4>& reserved_4, std::uint32_t sequence, const BidAskPair& bid_ask_pair);

    // Price: The price where every 1 unit corresponds to 1e-9
    std::optional<Decimal> price() const;
    void set_price(std::optional<Decimal> value);

    // Size: The order quantity
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Reserved 1: Reserved, 1 byte
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Side: The side that initiates the event
    Side side() const;
    void set_side(Side value);

    // Flags: A bit field indicating event end, message characteristics, and data quality;
    // declared least significant bit first
    const Flags& flags() const;
    Flags& flags();
    void set_flags(const Flags& value);

    // Second Reserved 1: Reserved, 1 byte
    const std::array<std::byte, 1>& second_reserved_1() const;
    std::array<std::byte, 1>& second_reserved_1();
    void set_second_reserved_1(const std::array<std::byte, 1>& value);

    // Ts Recv: The capture-server-received timestamp expressed as the number of nanoseconds
    // since the UNIX epoch
    std::optional<std::chrono::nanoseconds> ts_recv() const;
    void set_ts_recv(std::optional<std::chrono::nanoseconds> value);

    // Reserved 4: Reserved, 4 bytes
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

    // Sequence: The message sequence number assigned at the venue
    std::uint32_t sequence() const;
    void set_sequence(std::uint32_t value);

    // Bid Ask Pair: A level
    const BidAskPair& bid_ask_pair() const;
    BidAskPair& bid_ask_pair();
    void set_bid_ask_pair(const BidAskPair& value);

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

    bool operator==(const BboMsg& other) const;
    bool operator!=(const BboMsg& other) const;

  private:
    std::optional<Decimal> price_{};
    std::uint32_t size_{};
    std::array<std::byte, 1> reserved_1_{};
    Side side_{};
    Flags flags_{};
    std::array<std::byte, 1> second_reserved_1_{};
    std::optional<std::chrono::nanoseconds> ts_recv_{};
    std::array<std::byte, 4> reserved_4_{};
    std::uint32_t sequence_{};
    BidAskPair bid_ask_pair_{};
};

} // namespace databento::marketdata::normalized::dbn::v2
