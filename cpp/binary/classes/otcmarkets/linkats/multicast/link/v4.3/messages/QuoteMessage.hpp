#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/ExtendedQuoteFlags.hpp"
#include "../bitfields/QuoteFlags.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

class Visitor;

// This message is sent on the Quote Book channel and the Quote Book with Global OTC data
// channel.
class QuoteMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::QuoteMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 63;

    QuoteMessage() = default;
    QuoteMessage(std::uint32_t channel_seq_num, std::uint32_t quote_id, std::uint8_t quote_action, const QuoteFlags& quote_flags, std::uint32_t security_id, const std::string& mpid, Decimal ask_price, std::uint32_t ask_size, std::int8_t ask_qap, std::uint64_t ask_time_milli, Decimal bid_price, std::uint32_t bid_size, std::int8_t bid_qap, std::uint64_t bid_time_milli, std::uint16_t quote_reference_id, const ExtendedQuoteFlags& extended_quote_flags);

    // Channel Seq Num: Monotonically increasing message sequence number at the channel level.
    std::uint32_t channel_seq_num() const;
    void set_channel_seq_num(std::uint32_t value);

    // Quote Id: Unique Quote ID.
    std::uint32_t quote_id() const;
    void set_quote_id(std::uint32_t value);

    // Quote Action: Quote action indicator.
    std::uint8_t quote_action() const;
    void set_quote_action(std::uint8_t value);

    // Quote Flags: Quote Information
    const QuoteFlags& quote_flags() const;
    QuoteFlags& quote_flags();
    void set_quote_flags(const QuoteFlags& value);

    // Security Id: Unique security ID issued by OTC Markets.
    std::uint32_t security_id() const;
    void set_security_id(std::uint32_t value);

    // Mpid: Market Participant ID owning the quote (always 4 characters).
    const std::string& mpid() const;
    std::string& mpid();
    void set_mpid(const std::string& value);

    // Ask Price: Ask price, with 6 decimal places assumed.
    Decimal ask_price() const;
    void set_ask_price(Decimal value);

    // Ask Size: Number of shares on the ask.
    std::uint32_t ask_size() const;
    void set_ask_size(std::uint32_t value);

    // Ask Qap: Specifies the access fee or rebate for the ask. Positive values (1 to 30)
    // indicate a rebate, negative values (-1 to -30) indicate an access fee, and 0 indicates
    // no rebate or access fee.
    std::int8_t ask_qap() const;
    void set_ask_qap(std::int8_t value);

    // Ask Time Milli: Ask timestamp in milliseconds from UTC epoch.
    std::uint64_t ask_time_milli() const;
    void set_ask_time_milli(std::uint64_t value);

    // Bid Price: Bid price, with 6 decimal places assumed.
    Decimal bid_price() const;
    void set_bid_price(Decimal value);

    // Bid Size: Number of shares on the bid.
    std::uint32_t bid_size() const;
    void set_bid_size(std::uint32_t value);

    // Bid Qap: Specifies the access fee or rebate for the bid. Positive values (1 to 30)
    // indicate a rebate, negative values (-1 to -30) indicate an access fee, and 0 indicates
    // no rebate or access fee.
    std::int8_t bid_qap() const;
    void set_bid_qap(std::int8_t value);

    // Bid Time Milli: Bid timestamp in milliseconds from UTC epoch.
    std::uint64_t bid_time_milli() const;
    void set_bid_time_milli(std::uint64_t value);

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

    bool operator==(const QuoteMessage& other) const;
    bool operator!=(const QuoteMessage& other) const;

  private:
    std::uint32_t channel_seq_num_{};
    std::uint32_t quote_id_{};
    std::uint8_t quote_action_{};
    QuoteFlags quote_flags_{};
    std::uint32_t security_id_{};
    std::string mpid_{};
    Decimal ask_price_{ 0, -6 };
    std::uint32_t ask_size_{};
    std::int8_t ask_qap_{};
    std::uint64_t ask_time_milli_{};
    Decimal bid_price_{ 0, -6 };
    std::uint32_t bid_size_{};
    std::int8_t bid_qap_{};
    std::uint64_t bid_time_milli_{};
    std::uint16_t quote_reference_id_{};
    ExtendedQuoteFlags extended_quote_flags_{};
};

} // namespace otcmarkets::linkats::multicast::link::v4_3
