#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/UnsequencedMessage.hpp"
#include "../structs/RefreshResponseMessageApplicationMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class UnsequencedMessageVisitor;

// Sent by MIAX Options over the ToM Retransmission Interface (SesM Unsequenced Data Packet)
// carrying one Application Message that satisfies a previous Refresh Request. Note: MIAX
// Options PDF assigns Response Type "R" (uppercase) to this message, colliding with the
// Request Type "R" byte; lowercase "r" is used here to match the Pearl convention for
// case-distinct discrimination.
class RefreshResponseMessage : public UnsequencedMessage {
  public:
    // The code that selects this message
    static constexpr UnsequencedMessageCode message_type = UnsequencedMessageType::RefreshResponseMessage;

    RefreshResponseMessage() = default;
    RefreshResponseMessage(std::uint64_t sequence_number, const RefreshResponseMessageApplicationMessage& application_message);

    // Sequence Number: Original sequence number from the live feed.
    std::uint64_t sequence_number() const;
    void set_sequence_number(std::uint64_t value);

    // Application Message:
    const RefreshResponseMessageApplicationMessage& application_message() const;
    RefreshResponseMessageApplicationMessage& application_message();
    void set_application_message(const RefreshResponseMessageApplicationMessage& value);

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

    bool operator==(const RefreshResponseMessage& other) const;
    bool operator!=(const RefreshResponseMessage& other) const;

  private:
    std::uint64_t sequence_number_{};
    RefreshResponseMessageApplicationMessage application_message_{};
};

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
