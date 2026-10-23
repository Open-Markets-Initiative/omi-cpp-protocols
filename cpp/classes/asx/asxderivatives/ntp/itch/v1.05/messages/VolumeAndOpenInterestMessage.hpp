#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// This message disseminates Volume and Open Interest (VOI) information for each trade date
class VolumeAndOpenInterestMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::VolumeAndOpenInterestMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    VolumeAndOpenInterestMessage() = default;
    VolumeAndOpenInterestMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, std::uint64_t cumulative_volume, std::uint64_t open_interest, std::uint16_t voi_trade_date);

    // Nanoseconds: Nanoseconds portion of the Nanoseconds, accurate to 1,000 nanoseconds.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Trade Date: Trade Date. Represented as number of days since 1 January 1970.
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Tradeable Instrument Id: Identifier of the Order Book.
    std::uint32_t tradeable_instrument_id() const;
    void set_tradeable_instrument_id(std::uint32_t value);

    // Cumulative Volume: Volume traded for the specified VOI Trade Date.
    std::uint64_t cumulative_volume() const;
    void set_cumulative_volume(std::uint64_t value);

    // Open Interest: Number of open contracts at EOD for the specified VOI Trade Date.
    std::uint64_t open_interest() const;
    void set_open_interest(std::uint64_t value);

    // Voi Trade Date: Trade Date the VOI information is applicable to.
    std::uint16_t voi_trade_date() const;
    void set_voi_trade_date(std::uint16_t value);

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

    bool operator==(const VolumeAndOpenInterestMessage& other) const;
    bool operator!=(const VolumeAndOpenInterestMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    std::uint32_t tradeable_instrument_id_{};
    std::uint64_t cumulative_volume_{};
    std::uint64_t open_interest_{};
    std::uint16_t voi_trade_date_{};
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
