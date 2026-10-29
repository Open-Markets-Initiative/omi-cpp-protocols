#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Group.hpp"
#include "../enums/TradingState.hpp"
#include "../messages/PacketMessage.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

class PacketMessageVisitor;

// Trading State Message indicates the current trading state of an orderbook.
class UdpPayloadTradingStateMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::TradingStateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 13;

    UdpPayloadTradingStateMessage() = default;
    UdpPayloadTradingStateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t orderbook_id, const std::string& group, TradingState trading_state);

    // Nanoseconds: Number of nanoseconds since last Timestamp Seconds Message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Orderbook Id: 4 digit Quick code.
    std::uint32_t orderbook_id() const;
    void set_orderbook_id(std::uint32_t value);

    // Group: Orderbook group identifier.
    const std::string& group() const;
    std::string& group();
    void set_group(const std::string& value);

    // Trading State: Current trading state.
    TradingState trading_state() const;
    void set_trading_state(TradingState value);

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

    bool operator==(const UdpPayloadTradingStateMessage& other) const;
    bool operator!=(const UdpPayloadTradingStateMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t orderbook_id_{};
    std::string group_{};
    TradingState trading_state_{};
};

} // namespace jnx::jnxequities::pts::itch::v1_7
