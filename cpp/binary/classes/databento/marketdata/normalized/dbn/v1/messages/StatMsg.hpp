#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/StatType.hpp"
#include "../enums/UpdateAction.hpp"
#include "../messages/Message.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

class Visitor;

// A statistics message; the record of the statistics schema
class StatMsg : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = Rtype::Statistics;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 48;

    StatMsg() = default;
    StatMsg(std::optional<std::chrono::nanoseconds> ts_recv, std::optional<std::chrono::nanoseconds> ts_ref, std::optional<Decimal> price, std::optional<std::int32_t> quantity, std::uint32_t sequence, std::int32_t ts_in_delta, StatType stat_type, std::uint16_t channel, UpdateAction update_action, std::uint8_t stat_flags, const std::array<std::byte, 6>& reserved_6);

    // Ts Recv: The capture-server-received timestamp expressed as the number of nanoseconds
    // since the UNIX epoch
    std::optional<std::chrono::nanoseconds> ts_recv() const;
    void set_ts_recv(std::optional<std::chrono::nanoseconds> value);

    // Ts Ref: The reference timestamp of the statistic value expressed as the number of
    // nanoseconds since the UNIX epoch
    std::optional<std::chrono::nanoseconds> ts_ref() const;
    void set_ts_ref(std::optional<std::chrono::nanoseconds> value);

    // Price: The price where every 1 unit corresponds to 1e-9
    std::optional<Decimal> price() const;
    void set_price(std::optional<Decimal> value);

    // Quantity: The value for non-price statistics
    std::optional<std::int32_t> quantity() const;
    void set_quantity(std::optional<std::int32_t> value);

    // Sequence: The message sequence number assigned at the venue
    std::uint32_t sequence() const;
    void set_sequence(std::uint32_t value);

    // Ts In Delta: The matching-engine-sending timestamp expressed as the number of
    // nanoseconds before ts_recv
    std::int32_t ts_in_delta() const;
    void set_ts_in_delta(std::int32_t value);

    // Stat Type: The type of statistic value contained in the message
    StatType stat_type() const;
    void set_stat_type(StatType value);

    // Channel: The channel ID assigned by Databento as an incrementing integer starting at
    // zero
    std::uint16_t channel() const;
    void set_channel(std::uint16_t value);

    // Update Action: Indicates if the statistic is newly added or deleted
    UpdateAction update_action() const;
    void set_update_action(UpdateAction value);

    // Stat Flags: Additional flags associated with certain stat types
    std::uint8_t stat_flags() const;
    void set_stat_flags(std::uint8_t value);

    // Reserved 6: Reserved, 6 bytes
    const std::array<std::byte, 6>& reserved_6() const;
    std::array<std::byte, 6>& reserved_6();
    void set_reserved_6(const std::array<std::byte, 6>& value);

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

    bool operator==(const StatMsg& other) const;
    bool operator!=(const StatMsg& other) const;

  private:
    std::optional<std::chrono::nanoseconds> ts_recv_{};
    std::optional<std::chrono::nanoseconds> ts_ref_{};
    std::optional<Decimal> price_{};
    std::optional<std::int32_t> quantity_{};
    std::uint32_t sequence_{};
    std::int32_t ts_in_delta_{};
    StatType stat_type_{};
    std::uint16_t channel_{};
    UpdateAction update_action_{};
    std::uint8_t stat_flags_{};
    std::array<std::byte, 6> reserved_6_{};
};

} // namespace databento::marketdata::normalized::dbn::v1
