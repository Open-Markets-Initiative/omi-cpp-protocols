#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/ChangeReason.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class PacketMessageVisitor;

// This message is sent whenever an order or a side of a quote is being updated for price and
// (or) contracts. The reference number associated with the order quote is unchanged.
class UdpPayloadSingleSideChangeMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::SingleSideChangeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    UdpPayloadSingleSideChangeMessage() = default;
    UdpPayloadSingleSideChangeMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t reference_number, ChangeReason change_reason, Decimal price_long, std::uint32_t volume_long);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Reference Number: The order/quote reference number associated with the executed order.
    std::uint64_t reference_number() const;
    void set_reference_number(std::uint64_t value);

    // Change Reason:
    ChangeReason change_reason() const;
    void set_change_reason(ChangeReason value);

    // Price Long: The display price of the new order being added to the book.
    Decimal price_long() const;
    void set_price_long(Decimal value);

    // Volume Long: The total number of contracts of the new order being added to the book.
    std::uint32_t volume_long() const;
    void set_volume_long(std::uint32_t value);

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

    bool operator==(const UdpPayloadSingleSideChangeMessage& other) const;
    bool operator!=(const UdpPayloadSingleSideChangeMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t reference_number_{};
    ChangeReason change_reason_{};
    Decimal price_long_{ 0, -4 };
    std::uint32_t volume_long_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
