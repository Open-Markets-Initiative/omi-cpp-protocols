#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class PacketMessageVisitor;

// This message is sent whenever an order or one side of a quote on the book is replaced. The
// replacement has a new sequence number and replaces the prior sequence number.
class UdpPayloadSingleSideReplaceMessageShortForm : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::SingleSideReplaceMessageShortForm;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    UdpPayloadSingleSideReplaceMessageShortForm() = default;
    UdpPayloadSingleSideReplaceMessageShortForm(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t original_reference_number, std::uint64_t new_reference_number, Decimal price_short, std::uint16_t volume_short);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Original Reference Number: The original reference number associated with the order being
    // replaced.
    std::uint64_t original_reference_number() const;
    void set_original_reference_number(std::uint64_t value);

    // New Reference Number: The new reference number associated with the new order.
    std::uint64_t new_reference_number() const;
    void set_new_reference_number(std::uint64_t value);

    // Price Short: The display price of the new order being added to the book. NOTE: When
    // converted to a decimal format, this price is in fixed point format with 3 whole number
    // places followed by 2 decimal digits.
    Decimal price_short() const;
    void set_price_short(Decimal value);

    // Volume Short: The total number of contracts of the new order being added to the book.
    std::uint16_t volume_short() const;
    void set_volume_short(std::uint16_t value);

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

    bool operator==(const UdpPayloadSingleSideReplaceMessageShortForm& other) const;
    bool operator!=(const UdpPayloadSingleSideReplaceMessageShortForm& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t original_reference_number_{};
    std::uint64_t new_reference_number_{};
    Decimal price_short_{ 0, -4 };
    std::uint16_t volume_short_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
