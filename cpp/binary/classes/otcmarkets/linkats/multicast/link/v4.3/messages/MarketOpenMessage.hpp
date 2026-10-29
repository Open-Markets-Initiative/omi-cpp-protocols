#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

class Visitor;

// This message is sent out at 6 AM on all channels. The message can also be sent mid-day if a
// technical outage caused a temporary closure of the market.
class MarketOpenMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::MarketOpenMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 20;

    MarketOpenMessage() = default;
    MarketOpenMessage(std::uint32_t channel_seq_num, std::chrono::milliseconds market_open, std::uint64_t market_close);

    // Channel Seq Num: Monotonically increasing message sequence number at the channel level.
    std::uint32_t channel_seq_num() const;
    void set_channel_seq_num(std::uint32_t value);

    // Market Open: Market open time in milliseconds since UTC epoch.
    std::chrono::milliseconds market_open() const;
    void set_market_open(std::chrono::milliseconds value);

    // Market Close: Anticipated market close time in milliseconds since UTC epoch.
    std::uint64_t market_close() const;
    void set_market_close(std::uint64_t value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const MarketOpenMessage& other) const;
    bool operator!=(const MarketOpenMessage& other) const;

  private:
    std::uint32_t channel_seq_num_{};
    std::chrono::milliseconds market_open_{};
    std::uint64_t market_close_{};
};

} // namespace otcmarkets::linkats::multicast::link::v4_3
