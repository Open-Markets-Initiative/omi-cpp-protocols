#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/UnsequencedMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class UnsequencedMessageVisitor;

// Sent by MIAX Pearl Equities over the DoM Retransmission Interface (ESeSM Unsequenced Data
// Packet) carrying one Application Message that satisfies a previous Refresh Request.
class RefreshResponseMessage : public UnsequencedMessage {
  public:
    // The code that selects this message
    static constexpr UnsequencedMessageCode message_type = UnsequencedMessageType::RefreshResponseMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 8;

    RefreshResponseMessage() = default;
    RefreshResponseMessage(std::uint64_t sequence_number);

    // Sequence Number: For Symbol Update/Trading Status/System State refreshes this is the
    // original sequence number from the live feed; for Order Book refresh this is the last
    // sequence number on the live feed at the time of the refresh request.
    std::uint64_t sequence_number() const;
    void set_sequence_number(std::uint64_t value);

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
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
