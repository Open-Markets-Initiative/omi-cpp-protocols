#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/ExtendedQuoteFlags.hpp"
#include "../bitfields/QuoteFlags.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

class Visitor;

// Quote update information for the Quote Book channel and the Quote Book with Global OTC data
// channel.
class QuoteUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::QuoteUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 33;

    QuoteUpdateMessage() = default;
    QuoteUpdateMessage(std::uint32_t channel_seq_num, std::uint32_t quote_id, const QuoteFlags& quote_flags, Decimal price, std::uint32_t size, std::int8_t qap, std::uint64_t quote_time_milli, std::uint16_t quote_reference_id, const ExtendedQuoteFlags& extended_quote_flags);

    // Channel Seq Num: Monotonically increasing message sequence number at the channel level.
    std::uint32_t channel_seq_num() const;
    void set_channel_seq_num(std::uint32_t value);

    // Quote Id: Unique Quote ID.
    std::uint32_t quote_id() const;
    void set_quote_id(std::uint32_t value);

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

    // Qap: Specifies the access fee or rebate for the bid/offer. Positive values (1 to 30)
    // indicate a rebate, negative values (-1 to -30) indicate an access fee, and 0 indicates
    // no rebate or access fee.
    std::int8_t qap() const;
    void set_qap(std::int8_t value);

    // Quote Time Milli: Quote timestamp in milliseconds from UTC epoch.
    std::uint64_t quote_time_milli() const;
    void set_quote_time_milli(std::uint64_t value);

    // Quote Reference Id: Numeric value (0–64,999) assigned by the quote owner (FIX Tag 9670),
    // used for correlation purposes.
    std::uint16_t quote_reference_id() const;
    void set_quote_reference_id(std::uint16_t value);

    // Extended Quote Flags: Extended Quote Information
    const ExtendedQuoteFlags& extended_quote_flags() const;
    ExtendedQuoteFlags& extended_quote_flags();
    void set_extended_quote_flags(const ExtendedQuoteFlags& value);

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

    bool operator==(const QuoteUpdateMessage& other) const;
    bool operator!=(const QuoteUpdateMessage& other) const;

  private:
    std::uint32_t channel_seq_num_{};
    std::uint32_t quote_id_{};
    QuoteFlags quote_flags_{};
    Decimal price_{ 0, -6 };
    std::uint32_t size_{};
    std::int8_t qap_{};
    std::uint64_t quote_time_milli_{};
    std::uint16_t quote_reference_id_{};
    ExtendedQuoteFlags extended_quote_flags_{};
};

} // namespace otcmarkets::linkats::multicast::link::v4_3
