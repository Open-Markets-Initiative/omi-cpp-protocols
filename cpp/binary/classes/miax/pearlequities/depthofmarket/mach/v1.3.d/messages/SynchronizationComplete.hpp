#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/TcpMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class TcpMessageVisitor;

// The ESesM server sends a Login response packet in response a Login request packet from the
// client
class SynchronizationComplete : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = EsesmPacketType::SynchronizationComplete;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 1;

    SynchronizationComplete() = default;
    SynchronizationComplete(std::uint8_t number_of_matching_engines);

    // Number Of Matching Engines: Count of all Matching Engines for the exchange
    std::uint8_t number_of_matching_engines() const;
    void set_number_of_matching_engines(std::uint8_t value);

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

    bool operator==(const SynchronizationComplete& other) const;
    bool operator!=(const SynchronizationComplete& other) const;

  private:
    std::uint8_t number_of_matching_engines_{};
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
