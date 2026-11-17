// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/MarketCloseMessage.hpp
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

// This message is sent out at 5 PM on all channels. The message can also be sent mid-day if a
// technical outage causes a temporary closure of the market.
class MarketCloseMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::MarketCloseMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    MarketCloseMessage() = default;
    MarketCloseMessage(std::uint32_t channel_seq_num, std::chrono::milliseconds market_close_time_milli, std::uint32_t market_msg_ct);

    // Channel Seq Num: Monotonically increasing message sequence number at the channel level.
    std::uint32_t channel_seq_num() const;
    void set_channel_seq_num(std::uint32_t value);

    // Market Close Time Milli: Market close time in milliseconds since UTC epoch midnight.
    std::chrono::milliseconds market_close_time_milli() const;
    void set_market_close_time_milli(std::chrono::milliseconds value);

    // Market Msg Ct: Total message count for the trading day.
    std::uint32_t market_msg_ct() const;
    void set_market_msg_ct(std::uint32_t value);

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

    bool operator==(const MarketCloseMessage& other) const;
    bool operator!=(const MarketCloseMessage& other) const;

  private:
    std::uint32_t channel_seq_num_{};
    std::chrono::milliseconds market_close_time_milli_{};
    std::uint32_t market_msg_ct_{};
};

} // namespace otcmarkets::linkats::multicast::link::v4_3
