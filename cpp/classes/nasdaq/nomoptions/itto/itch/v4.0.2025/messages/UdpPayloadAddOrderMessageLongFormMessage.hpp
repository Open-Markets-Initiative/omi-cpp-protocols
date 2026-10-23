#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/MarketSide.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class PacketMessageVisitor;

// For bandwidth efficiency reasons, this message can be published in either short or long
// format.
class UdpPayloadAddOrderMessageLongFormMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::AddOrderMessageLongFormMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 29;

    UdpPayloadAddOrderMessageLongFormMessage() = default;
    UdpPayloadAddOrderMessageLongFormMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, MarketSide market_side, std::uint32_t option_id, Decimal price_long, std::uint32_t volume_long);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Order Reference Number: The unique reference number assigned to the new order. The order
    // reference number is Increasing, but not necessarily sequential.
    std::uint64_t order_reference_number() const;
    void set_order_reference_number(std::uint64_t value);

    // Market Side: The type of order being added.
    MarketSide market_side() const;
    void set_market_side(MarketSide value);

    // Option Id: Option ID assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

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

    bool operator==(const UdpPayloadAddOrderMessageLongFormMessage& other) const;
    bool operator!=(const UdpPayloadAddOrderMessageLongFormMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t order_reference_number_{};
    MarketSide market_side_{};
    std::uint32_t option_id_{};
    Decimal price_long_{ 0, -4 };
    std::uint32_t volume_long_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
