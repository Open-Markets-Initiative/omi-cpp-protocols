#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/PacketMessage.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

class PacketMessageVisitor;

// Reflects the number of seconds past midnight that the Timestamp message was generated.
class UdpPayloadSecondsMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::SecondsMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    UdpPayloadSecondsMessage() = default;
    UdpPayloadSecondsMessage(std::chrono::seconds seconds);

    // Seconds: Number of seconds since midnight of the day that the trading session started.
    std::chrono::seconds seconds() const;
    void set_seconds(std::chrono::seconds value);
    std::int64_t seconds_utc(const calendar::Day& day) const;

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

    bool operator==(const UdpPayloadSecondsMessage& other) const;
    bool operator!=(const UdpPayloadSecondsMessage& other) const;

  private:
    std::chrono::seconds seconds_{};
};

} // namespace jnx::jnxequities::pts::itch::v1_7
