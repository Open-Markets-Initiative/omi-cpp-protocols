#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/RefreshMessageType.hpp"
#include "../messages/UnsequencedMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class UnsequencedMessageVisitor;

// Sent by MIAX Options over the ToM Retransmission Interface (SesM Unsequenced Data Packet)
// when the refresh response is complete.
class EndOfRefreshNotificationMessage : public UnsequencedMessage {
  public:
    // The code that selects this message
    static constexpr UnsequencedMessageCode message_type = UnsequencedMessageType::EndOfRefreshNotificationMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 1;

    EndOfRefreshNotificationMessage() = default;
    EndOfRefreshNotificationMessage(RefreshMessageType refresh_message_type);

    // Refresh Message Type: Identifies the data set the firm is requesting a refresh of.
    RefreshMessageType refresh_message_type() const;
    void set_refresh_message_type(RefreshMessageType value);

    // UnsequencedMessage
    UnsequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(UnsequencedMessageVisitor& visitor) const override;
    std::unique_ptr<UnsequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const UnsequencedMessage& other) const override;

    bool operator==(const EndOfRefreshNotificationMessage& other) const;
    bool operator!=(const EndOfRefreshNotificationMessage& other) const;

  private:
    RefreshMessageType refresh_message_type_{};
};

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
