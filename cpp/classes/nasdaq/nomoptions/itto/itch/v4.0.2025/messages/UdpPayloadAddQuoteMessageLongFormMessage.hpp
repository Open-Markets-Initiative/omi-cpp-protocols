#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/PacketMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class PacketMessageVisitor;

// For bandwidth efficiency reasons, this message can be published in either short or long
// format.
class UdpPayloadAddQuoteMessageLongFormMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::AddQuoteMessageLongFormMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 44;

    UdpPayloadAddQuoteMessageLongFormMessage() = default;
    UdpPayloadAddQuoteMessageLongFormMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t bid_reference_number, std::uint64_t ask_reference_number, std::uint32_t option_id, std::uint32_t bid, std::uint32_t bid_size_long, std::uint32_t ask, std::uint32_t ask_size_long);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Bid Reference Number: The bid reference number associated with the new quote.
    std::uint64_t bid_reference_number() const;
    void set_bid_reference_number(std::uint64_t value);

    // Ask Reference Number: The ask reference number associated with the new quote
    std::uint64_t ask_reference_number() const;
    void set_ask_reference_number(std::uint64_t value);

    // Option Id: Option ID assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Bid: The display bid price of the new quote.
    std::uint32_t bid() const;
    void set_bid(std::uint32_t value);

    // Bid Size Long: The bid contracts of the new quote.
    std::uint32_t bid_size_long() const;
    void set_bid_size_long(std::uint32_t value);

    // Ask: The display ask price of the new quote.
    std::uint32_t ask() const;
    void set_ask(std::uint32_t value);

    // Ask Size Long: The ask contracts of the new quote.
    std::uint32_t ask_size_long() const;
    void set_ask_size_long(std::uint32_t value);

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

    bool operator==(const UdpPayloadAddQuoteMessageLongFormMessage& other) const;
    bool operator!=(const UdpPayloadAddQuoteMessageLongFormMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t bid_reference_number_{};
    std::uint64_t ask_reference_number_{};
    std::uint32_t option_id_{};
    std::uint32_t bid_{};
    std::uint32_t bid_size_long_{};
    std::uint32_t ask_{};
    std::uint32_t ask_size_long_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
