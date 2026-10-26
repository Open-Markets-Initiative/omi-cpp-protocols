#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class PacketMessageVisitor;

// For bandwidth efficiency reasons, this message can be published in either short or long
// format.
class UdpPayloadAddQuoteMessageShortFormMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::AddQuoteMessageShortFormMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    UdpPayloadAddQuoteMessageShortFormMessage() = default;
    UdpPayloadAddQuoteMessageShortFormMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t bid_reference_number, std::uint64_t ask_reference_number, std::uint32_t option_id, Decimal bid_price_short, std::uint16_t bid_size_short, Decimal ask_price_short, std::uint16_t ask_size_short);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Bid Reference Number: The bid reference number associated with the new quote.
    std::uint64_t bid_reference_number() const;
    void set_bid_reference_number(std::uint64_t value);

    // Ask Reference Number: The ask reference number associated with the new quote
    std::uint64_t ask_reference_number() const;
    void set_ask_reference_number(std::uint64_t value);

    // Option Id: Option ID assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Bid Price Short: The display bid price of the new quote. NOTE: When converted to a
    // decimal format, this price is in fixed point format with 3 whole number places followed
    // by 2 decimal digits.
    Decimal bid_price_short() const;
    void set_bid_price_short(Decimal value);

    // Bid Size Short: The bid contracts of the new quote.
    std::uint16_t bid_size_short() const;
    void set_bid_size_short(std::uint16_t value);

    // Ask Price Short: The display ask price of the new quote. NOTE: When converted to a
    // decimal format, this price is in fixed point format with 3 whole number places followed
    // by 2 decimal digits.
    Decimal ask_price_short() const;
    void set_ask_price_short(Decimal value);

    // Ask Size Short: The ask contracts of the new quote.
    std::uint16_t ask_size_short() const;
    void set_ask_size_short(std::uint16_t value);

    // PacketMessage
    PacketMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PacketMessageVisitor& visitor) const override;
    std::unique_ptr<PacketMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const PacketMessage& other) const override;

    bool operator==(const UdpPayloadAddQuoteMessageShortFormMessage& other) const;
    bool operator!=(const UdpPayloadAddQuoteMessageShortFormMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t bid_reference_number_{};
    std::uint64_t ask_reference_number_{};
    std::uint32_t option_id_{};
    Decimal bid_price_short_{ 0, -4 };
    std::uint16_t bid_size_short_{};
    Decimal ask_price_short_{ 0, -4 };
    std::uint16_t ask_size_short_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
