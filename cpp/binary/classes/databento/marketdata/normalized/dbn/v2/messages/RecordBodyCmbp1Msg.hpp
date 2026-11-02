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
#include "../messages/GatewayMessage.hpp"
#include "../structs/ConsolidatedBidAskPair.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

class GatewayMessageVisitor;

// Consolidated market by price implementation with a known book depth of 1; the record of the
// cmbp-1 and tcbbo schemas
class RecordBodyCmbp1Msg : public GatewayMessage {
  public:
    // The code that selects this message
    static constexpr GatewayMessageCode message_type = Rtype::TradeWithConsolidatedBbo;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 64;

    RecordBodyCmbp1Msg() = default;
    RecordBodyCmbp1Msg(std::optional<Decimal> price, std::uint32_t size, Action action, Side side, const Flags& flags, const std::array<std::byte, 1>& reserved_1, std::optional<std::chrono::nanoseconds> ts_recv, std::int32_t ts_in_delta, const std::array<std::byte, 4>& reserved_4, const ConsolidatedBidAskPair& consolidated_bid_ask_pair);

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

    // Reserved 1: Reserved, 1 byte
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Ts Recv: The capture-server-received timestamp expressed as the number of nanoseconds
    // since the UNIX epoch
    std::optional<std::chrono::nanoseconds> ts_recv() const;
    void set_ts_recv(std::optional<std::chrono::nanoseconds> value);

    // Ts In Delta: The matching-engine-sending timestamp expressed as the number of
    // nanoseconds before ts_recv
    std::int32_t ts_in_delta() const;
    void set_ts_in_delta(std::int32_t value);

    // Reserved 4: Reserved, 4 bytes
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

    // Consolidated Bid Ask Pair: A price level consolidated from multiple venues
    const ConsolidatedBidAskPair& consolidated_bid_ask_pair() const;
    ConsolidatedBidAskPair& consolidated_bid_ask_pair();
    void set_consolidated_bid_ask_pair(const ConsolidatedBidAskPair& value);

    // GatewayMessage
    GatewayMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(GatewayMessageVisitor& visitor) const override;
    std::unique_ptr<GatewayMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const GatewayMessage& other) const override;

    bool operator==(const RecordBodyCmbp1Msg& other) const;
    bool operator!=(const RecordBodyCmbp1Msg& other) const;

  private:
    std::optional<Decimal> price_{};
    std::uint32_t size_{};
    Action action_{};
    Side side_{};
    Flags flags_{};
    std::array<std::byte, 1> reserved_1_{};
    std::optional<std::chrono::nanoseconds> ts_recv_{};
    std::int32_t ts_in_delta_{};
    std::array<std::byte, 4> reserved_4_{};
    ConsolidatedBidAskPair consolidated_bid_ask_pair_{};
};

} // namespace databento::marketdata::normalized::dbn::v2
