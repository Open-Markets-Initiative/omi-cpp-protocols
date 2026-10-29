#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/QuoteFlags.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

class Visitor;

// Quote update information for the Quote Inside channel and the Quote Inside with Global OTC
// data channel.
class InsideUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::InsideUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 30;

    InsideUpdateMessage() = default;
    InsideUpdateMessage(std::uint32_t channel_seq_num, std::uint32_t inside_id, const QuoteFlags& quote_flags, Decimal price, std::uint32_t size, std::uint64_t inside_time_milli, std::uint8_t num_priced_mp);

    // Channel Seq Num: Monotonically increasing message sequence number at the channel level.
    std::uint32_t channel_seq_num() const;
    void set_channel_seq_num(std::uint32_t value);

    // Inside Id: Unique Inside ID.
    std::uint32_t inside_id() const;
    void set_inside_id(std::uint32_t value);

    // Quote Flags: Quote Information
    const QuoteFlags& quote_flags() const;
    QuoteFlags& quote_flags();
    void set_quote_flags(const QuoteFlags& value);

    // Price: Price with 6 decimal places assumed.
    Decimal price() const;
    void set_price(Decimal value);

    // Size: Number of shares.
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Inside Time Milli: Inside timestamp in milliseconds from UTC epoch.
    std::uint64_t inside_time_milli() const;
    void set_inside_time_milli(std::uint64_t value);

    // Num Priced Mp: Number of market participants at the inside price level.
    std::uint8_t num_priced_mp() const;
    void set_num_priced_mp(std::uint8_t value);

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

    bool operator==(const InsideUpdateMessage& other) const;
    bool operator!=(const InsideUpdateMessage& other) const;

  private:
    std::uint32_t channel_seq_num_{};
    std::uint32_t inside_id_{};
    QuoteFlags quote_flags_{};
    Decimal price_{ 0, -6 };
    std::uint32_t size_{};
    std::uint64_t inside_time_milli_{};
    std::uint8_t num_priced_mp_{};
};

} // namespace otcmarkets::linkats::multicast::link::v4_3
