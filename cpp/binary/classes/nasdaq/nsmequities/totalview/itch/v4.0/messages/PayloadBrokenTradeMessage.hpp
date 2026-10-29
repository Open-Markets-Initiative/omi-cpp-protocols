#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/PacketMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class PacketMessageVisitor;

// The Broken Trade Message is sent whenever an execution on NASDAQ is broken.
class PayloadBrokenTradeMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::BrokenTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 12;

    PayloadBrokenTradeMessage() = default;
    PayloadBrokenTradeMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t match_number);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Match Number: The NASDAQ generated day-unique Match Number of this execution. The match
    // number is also referenced in the Trade Break Message.
    std::uint64_t match_number() const;
    void set_match_number(std::uint64_t value);

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

    bool operator==(const PayloadBrokenTradeMessage& other) const;
    bool operator!=(const PayloadBrokenTradeMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t match_number_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
