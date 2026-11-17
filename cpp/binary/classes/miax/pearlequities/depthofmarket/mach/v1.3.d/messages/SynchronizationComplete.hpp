// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/SynchronizationComplete.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/TcpMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class TcpMessageVisitor;

// The ESesM server sends a Synchronization complete packet when it is done replaying all the
// old packets and is ready to start sending new packets from the Matching Engine
class SynchronizationComplete : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = EsesmPacketType::SynchronizationComplete;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 1;

    SynchronizationComplete() = default;
    SynchronizationComplete(std::uint8_t matching_engine_id);

    // Matching Engine Id: Matching Engine that originated the packet
    std::uint8_t matching_engine_id() const;
    void set_matching_engine_id(std::uint8_t value);

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
    std::uint8_t matching_engine_id_{};
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
