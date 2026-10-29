#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/QuoteCondition.hpp"
#include "../messages/Message.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

class Visitor;

// The Refresh Complex Quote message is sent in the event no quote messages are published for
// the symbol for 2 consecutive minutes.
class RefreshComplexQuoteMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::RefreshComplexQuoteMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    RefreshComplexQuoteMessage() = default;
    RefreshComplexQuoteMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t complex_index, std::uint32_t symbol_seq_num, std::int32_t ask_price, std::int32_t bid_price, std::uint16_t ask_volume, std::uint16_t bid_volume, std::uint16_t ask_customer_volume, std::uint16_t bid_customer_volume, QuoteCondition quote_condition, const std::array<std::byte, 1>& reserved_1, const std::array<std::byte, 2>& reserved_2);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Time Ns: The nanosecond offset from the SourceTime.
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Complex Index: The unique ID of the symbol in the Complex Index msg
    std::uint32_t complex_index() const;
    void set_complex_index(std::uint32_t value);

    // Symbol Seq Num: Sequence number of messages for the complex symbol.
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Ask Price: Best Ask price*. Should be used with the Price Scale Code from the Underlying
    // Index Mapping message.
    std::int32_t ask_price() const;
    void set_ask_price(std::int32_t value);

    // Bid Price: Best Bid price*. Should be used with the Price Scale Code from the Underlying
    // Index Mapping message.
    std::int32_t bid_price() const;
    void set_bid_price(std::int32_t value);

    // Ask Volume: Total quantity available at the above Ask price.
    std::uint16_t ask_volume() const;
    void set_ask_volume(std::uint16_t value);

    // Bid Volume: Total quantity available at the above Bid price.
    std::uint16_t bid_volume() const;
    void set_bid_volume(std::uint16_t value);

    // Ask Customer Volume: Total quantity of ‘Customer’ orders available at the above Ask
    // price.
    std::uint16_t ask_customer_volume() const;
    void set_ask_customer_volume(std::uint16_t value);

    // Bid Customer Volume: Total quantity of ‘Customer’ orders available at the above Bid
    // price.
    std::uint16_t bid_customer_volume() const;
    void set_bid_customer_volume(std::uint16_t value);

    // Quote Condition: QuoteCondition value
    QuoteCondition quote_condition() const;
    void set_quote_condition(QuoteCondition value);

    // Reserved 1: Filler
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Reserved 2: Filler
    const std::array<std::byte, 2>& reserved_2() const;
    std::array<std::byte, 2>& reserved_2();
    void set_reserved_2(const std::array<std::byte, 2>& value);

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

    bool operator==(const RefreshComplexQuoteMessage& other) const;
    bool operator!=(const RefreshComplexQuoteMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t complex_index_{};
    std::uint32_t symbol_seq_num_{};
    std::int32_t ask_price_{};
    std::int32_t bid_price_{};
    std::uint16_t ask_volume_{};
    std::uint16_t bid_volume_{};
    std::uint16_t ask_customer_volume_{};
    std::uint16_t bid_customer_volume_{};
    QuoteCondition quote_condition_{};
    std::array<std::byte, 1> reserved_1_{};
    std::array<std::byte, 2> reserved_2_{};
};

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
