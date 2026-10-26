#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/TcpMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class TcpMessageVisitor;

// The SesM client uses this packet to request a retransmission server to retransmit a range of
// packets
class RetransmissionRequest : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = SesmPacketType::RetransmissionRequest;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    RetransmissionRequest() = default;
    RetransmissionRequest(std::uint64_t start_sequence_number, std::uint64_t end_sequence_number);

    // Start Sequence Number: Sequence number of the first packet to be retransmitted
    std::uint64_t start_sequence_number() const;
    void set_start_sequence_number(std::uint64_t value);

    // End Sequence Number: Sequence number of the last packet to be retransmitted
    std::uint64_t end_sequence_number() const;
    void set_end_sequence_number(std::uint64_t value);

    // TcpMessage
    TcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(TcpMessageVisitor& visitor) const override;
    std::unique_ptr<TcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const TcpMessage& other) const override;

    bool operator==(const RetransmissionRequest& other) const;
    bool operator!=(const RetransmissionRequest& other) const;

  private:
    std::uint64_t start_sequence_number_{};
    std::uint64_t end_sequence_number_{};
};

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
