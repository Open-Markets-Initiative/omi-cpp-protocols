// Databento.MarketData.Normalized.Dbn.v1: messages/Mbp10Msg.hpp
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
#include "../enums/Action.hpp"
#include "../enums/Side.hpp"
#include "../groups/Mbp10MsgBidAskPair.hpp"
#include "../messages/Message.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

class Visitor;

// Market by price implementation with a known book depth of 10
class Mbp10Msg : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = Rtype::MarketByPrice10;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 352;

    Mbp10Msg() = default;
    Mbp10Msg(std::optional<Decimal> price, std::uint32_t size, Action action, Side side, const Flags& flags, std::uint8_t depth, std::optional<std::chrono::nanoseconds> ts_recv, std::int32_t ts_in_delta, std::uint32_t sequence, const std::array<Mbp10MsgBidAskPair, 10>& bid_ask_pair);

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
    const std::array<Mbp10MsgBidAskPair, 10>& bid_ask_pair() const;
    std::array<Mbp10MsgBidAskPair, 10>& bid_ask_pair();
    void set_bid_ask_pair(const std::array<Mbp10MsgBidAskPair, 10>& value);

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

    bool operator==(const Mbp10Msg& other) const;
    bool operator!=(const Mbp10Msg& other) const;

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
    std::array<Mbp10MsgBidAskPair, 10> bid_ask_pair_{};
};

} // namespace databento::marketdata::normalized::dbn::v1
