// Databento.MarketData.Normalized.Dbn.v2: messages/RecordBodyMboMsg.hpp
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
#include "../messages/GatewayMessage.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

class GatewayMessageVisitor;

// A market-by-order (MBO) tick message
class RecordBodyMboMsg : public GatewayMessage {
  public:
    // The code that selects this message
    static constexpr GatewayMessageCode message_type = Rtype::MarketByOrder;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    RecordBodyMboMsg() = default;
    RecordBodyMboMsg(std::uint64_t order_id, std::optional<Decimal> price, std::uint32_t size, const Flags& flags, std::uint8_t channel_id, Action action, Side side, std::optional<std::chrono::nanoseconds> ts_recv, std::int32_t ts_in_delta, std::uint32_t sequence);

    // Order Id: The order ID assigned at the venue
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Price: The price where every 1 unit corresponds to 1e-9
    std::optional<Decimal> price() const;
    void set_price(std::optional<Decimal> value);

    // Size: The order quantity
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Flags: A bit field indicating event end, message characteristics, and data quality;
    // declared least significant bit first
    const Flags& flags() const;
    Flags& flags();
    void set_flags(const Flags& value);

    // Channel Id: The channel ID assigned by Databento as an incrementing integer starting at
    // zero
    std::uint8_t channel_id() const;
    void set_channel_id(std::uint8_t value);

    // Action: The event action
    Action action() const;
    void set_action(Action value);

    // Side: The side that initiates the event
    Side side() const;
    void set_side(Side value);

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

    bool operator==(const RecordBodyMboMsg& other) const;
    bool operator!=(const RecordBodyMboMsg& other) const;

  private:
    std::uint64_t order_id_{};
    std::optional<Decimal> price_{};
    std::uint32_t size_{};
    Flags flags_{};
    std::uint8_t channel_id_{};
    Action action_{};
    Side side_{};
    std::optional<std::chrono::nanoseconds> ts_recv_{};
    std::int32_t ts_in_delta_{};
    std::uint32_t sequence_{};
};

} // namespace databento::marketdata::normalized::dbn::v2
