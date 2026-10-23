#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/OpenState.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

class PacketMessageVisitor;

// The options system uses this administrative message to indicate when an option has completed
// the opening process and is now available for auto execution or when the option has closed
// and is no longer available for auto execution.
class PayloadSecurityOpenClosedMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::SecurityOpenClosedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 9;

    PayloadSecurityOpenClosedMessage() = default;
    PayloadSecurityOpenClosedMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, OpenState open_state);

    // Nanoseconds: The sub-second portion of the time, in nanoseconds (0-999999999). The
    // second portion of the time is obtained from the most recent timestamp message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Option Id: Option ID for this option, assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Open State: Reflects the current eligibility for auto execution of the options security
    // in the options market.
    OpenState open_state() const;
    void set_open_state(OpenState value);

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

    bool operator==(const PayloadSecurityOpenClosedMessage& other) const;
    bool operator!=(const PayloadSecurityOpenClosedMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t option_id_{};
    OpenState open_state_{};
};

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
