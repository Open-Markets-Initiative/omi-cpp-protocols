#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/QuoteFlags.hpp"
#include "../common/Decimal.hpp"
#include "../enums/InsideAction.hpp"
#include "../messages/Message.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

class Visitor;

// This message is sent on the Quote Inside Channel and the Quote Inside with Global OTC data
// channel.
class InsideMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::InsideMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 56;

    InsideMessage() = default;
    InsideMessage(std::uint32_t channel_seq_num, std::uint32_t inside_id, InsideAction inside_action, const QuoteFlags& quote_flags, std::uint32_t security_id, Decimal ask_price, std::uint32_t ask_size, std::uint64_t ask_time_milli, Decimal bid_price, std::uint32_t bid_size, std::uint64_t bid_time_milli, std::uint8_t ask_num_priced_mp, std::uint8_t bid_num_priced_mp);

    // Channel Seq Num: Monotonically increasing message sequence number at the channel level.
    std::uint32_t channel_seq_num() const;
    void set_channel_seq_num(std::uint32_t value);

    // Inside Id: Unique Inside ID.
    std::uint32_t inside_id() const;
    void set_inside_id(std::uint32_t value);

    // Inside Action: Inside action indicator.
    InsideAction inside_action() const;
    void set_inside_action(InsideAction value);

    // Quote Flags: Quote Information
    const QuoteFlags& quote_flags() const;
    QuoteFlags& quote_flags();
    void set_quote_flags(const QuoteFlags& value);

    // Security Id: Unique security ID issued by OTC Markets.
    std::uint32_t security_id() const;
    void set_security_id(std::uint32_t value);

    // Ask Price: Ask price, with 6 decimal places assumed.
    Decimal ask_price() const;
    void set_ask_price(Decimal value);

    // Ask Size: Number of shares on the ask.
    std::uint32_t ask_size() const;
    void set_ask_size(std::uint32_t value);

    // Ask Time Milli: Ask timestamp in milliseconds from UTC epoch.
    std::uint64_t ask_time_milli() const;
    void set_ask_time_milli(std::uint64_t value);

    // Bid Price: Bid price, with 6 decimal places assumed.
    Decimal bid_price() const;
    void set_bid_price(Decimal value);

    // Bid Size: Number of shares on the bid.
    std::uint32_t bid_size() const;
    void set_bid_size(std::uint32_t value);

    // Bid Time Milli: Bid timestamp in milliseconds from UTC epoch.
    std::uint64_t bid_time_milli() const;
    void set_bid_time_milli(std::uint64_t value);

    // Ask Num Priced Mp: Number of market participants at the inside ask price level.
    std::uint8_t ask_num_priced_mp() const;
    void set_ask_num_priced_mp(std::uint8_t value);

    // Bid Num Priced Mp: Number of market participants at the inside bid price level.
    std::uint8_t bid_num_priced_mp() const;
    void set_bid_num_priced_mp(std::uint8_t value);

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

    bool operator==(const InsideMessage& other) const;
    bool operator!=(const InsideMessage& other) const;

  private:
    std::uint32_t channel_seq_num_{};
    std::uint32_t inside_id_{};
    InsideAction inside_action_{};
    QuoteFlags quote_flags_{};
    std::uint32_t security_id_{};
    Decimal ask_price_{ 0, -6 };
    std::uint32_t ask_size_{};
    std::uint64_t ask_time_milli_{};
    Decimal bid_price_{ 0, -6 };
    std::uint32_t bid_size_{};
    std::uint64_t bid_time_milli_{};
    std::uint8_t ask_num_priced_mp_{};
    std::uint8_t bid_num_priced_mp_{};
};

} // namespace otcmarkets::linkats::multicast::link::v4_3
