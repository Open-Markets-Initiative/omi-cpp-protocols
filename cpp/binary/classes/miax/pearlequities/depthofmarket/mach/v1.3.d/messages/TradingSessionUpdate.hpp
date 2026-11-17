// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/TradingSessionUpdate.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/TcpMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class TcpMessageVisitor;

// The ESesM server sends a Trading Session Update packet to inform the client that a new
// trading session is starting on the specified Matching Engine
class TradingSessionUpdate : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = EsesmPacketType::TradingSessionUpdate;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 2;

    TradingSessionUpdate() = default;
    TradingSessionUpdate(std::uint8_t matching_engine_id, std::uint8_t trading_session_id);

    // Matching Engine Id: Matching Engine that originated the packet
    std::uint8_t matching_engine_id() const;
    void set_matching_engine_id(std::uint8_t value);

    // Trading Session Id: The current trading session ID of the corresponding Matching Engine
    std::uint8_t trading_session_id() const;
    void set_trading_session_id(std::uint8_t value);

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

    bool operator==(const TradingSessionUpdate& other) const;
    bool operator!=(const TradingSessionUpdate& other) const;

  private:
    std::uint8_t matching_engine_id_{};
    std::uint8_t trading_session_id_{};
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
