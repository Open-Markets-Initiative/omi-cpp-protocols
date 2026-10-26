#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/Printable.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class PacketMessageVisitor;

// These executions may be marked as non-printable. If the execution is marked as non-printed,
// it means that the contracts will be included into a later bulk print (e.g., in the case of
// auction executions). If a firm is looking to use the ITTO data in time-and-sales displays or
// volume calculations, NASDAQ recommends that firms ignore messages marked as non-printable to
// prevent double counting.
class UdpPayloadSingleSideExecutedWithPriceMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::SingleSideExecutedWithPriceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 33;

    UdpPayloadSingleSideExecutedWithPriceMessage() = default;
    UdpPayloadSingleSideExecutedWithPriceMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t reference_number, std::uint32_t cross_number, std::uint32_t match_number, Printable printable, Decimal price_long, std::uint32_t volume_long);

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

    // Cross Number: Trade Group Id. Ties together all trades of a given atomic transaction in
    // the matching engine.
    std::uint32_t cross_number() const;
    void set_cross_number(std::uint32_t value);

    // Match Number: Execution Id. Identifies the component of an execution. Unique for a given
    // day. The match number is also referenced in the Trade Break Message.
    std::uint32_t match_number() const;
    void set_match_number(std::uint32_t value);

    // Printable: Indicates if the execution should be reflected on time and sale displays and
    // volume calculations.
    Printable printable() const;
    void set_printable(Printable value);

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

    bool operator==(const UdpPayloadSingleSideExecutedWithPriceMessage& other) const;
    bool operator!=(const UdpPayloadSingleSideExecutedWithPriceMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t reference_number_{};
    std::uint32_t cross_number_{};
    std::uint32_t match_number_{};
    Printable printable_{};
    Decimal price_long_{ 0, -4 };
    std::uint32_t volume_long_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
