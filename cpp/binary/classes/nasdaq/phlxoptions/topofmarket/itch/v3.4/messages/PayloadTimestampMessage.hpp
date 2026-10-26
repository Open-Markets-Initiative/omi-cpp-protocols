#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

class PacketMessageVisitor;

// The system event message type is used to signal a market or data feed handler event.
class PayloadTimestampMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::TimestampMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    PayloadTimestampMessage() = default;
    PayloadTimestampMessage(std::chrono::seconds second);

    // Second: Number of seconds since midnight (U.S. Eastern Time).
    std::chrono::seconds second() const;
    void set_second(std::chrono::seconds value);
    std::int64_t second_utc(const calendar::Day& day) const;

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

    bool operator==(const PayloadTimestampMessage& other) const;
    bool operator!=(const PayloadTimestampMessage& other) const;

  private:
    std::chrono::seconds second_{};
};

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
