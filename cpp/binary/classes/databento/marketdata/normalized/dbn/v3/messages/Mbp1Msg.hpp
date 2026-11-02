#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../bitfields/Flags.hpp"
#include "../common/Decimal.hpp"
#include "../enums/Action.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"
#include "../structs/BidAskPair.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

class Visitor;

// Market by price implementation with a known book depth of 1; the record of the mbp-1 and
// tbbo schemas
class Mbp1Msg : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = Rtype::MarketByPrice1;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 64;

    Mbp1Msg() = default;
    Mbp1Msg(std::optional<Decimal> price, std::uint32_t size, Action action, Side side, const Flags& flags, std::uint8_t depth, std::optional<std::chrono::nanoseconds> ts_recv, std::int32_t ts_in_delta, std::uint32_t sequence, const BidAskPair& bid_ask_pair);

    // Price: The price where every 1 unit corresponds to 1e-9
    std::optional<Decimal> price() const;
    void set_price(std::optional<Decimal> value);

    // Size: The order quantity
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Action: The event action
    Action action() const;
    void set_action(Action value);

    // Side: The side that initiates the event
    Side side() const;
    void set_side(Side value);

    // Flags: A bit field indicating event end, message characteristics, and data quality;
    // declared least significant bit first
    const Flags& flags() const;
    Flags& flags();
    void set_flags(const Flags& value);

    // Depth: The book level where the update event occurred
    std::uint8_t depth() const;
    void set_depth(std::uint8_t value);

    // Ts Recv: The capture-server-received timestamp expressed as the number of nanoseconds
    // since the UNIX epoch
    std::optional<std::chrono::nanoseconds> ts_recv() const;
    void set_ts_recv(std::optional<std::chrono::nanoseconds> value);

    // Ts In Delta: The matching-engine-sending timestamp expressed as the number of
    // nanoseconds before ts_recv
    std::int32_t ts_in_delta() const;
    void set_ts_in_delta(std::int32_t value);

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

    bool operator==(const Mbp1Msg& other) const;
    bool operator!=(const Mbp1Msg& other) const;

  private:
    std::optional<Decimal> price_{};
    std::uint32_t size_{};
    Action action_{};
    Side side_{};
    Flags flags_{};
    std::uint8_t depth_{};
    std::optional<std::chrono::nanoseconds> ts_recv_{};
    std::int32_t ts_in_delta_{};
    std::uint32_t sequence_{};
    BidAskPair bid_ask_pair_{};
};

} // namespace databento::marketdata::normalized::dbn::v3
