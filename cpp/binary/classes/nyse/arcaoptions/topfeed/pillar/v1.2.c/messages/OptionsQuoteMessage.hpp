#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/QuoteCondition.hpp"
#include "../messages/Message.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

class Visitor;

// An Options quote message is sent when any event results in a new top of book value on either
// side of the market
class OptionsQuoteMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OptionsQuoteMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 38;

    OptionsQuoteMessage() = default;
    OptionsQuoteMessage(std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::int32_t ask_price, std::uint32_t ask_volume, std::int32_t bid_price, std::uint32_t bid_volume, QuoteCondition quote_condition, const std::array<std::byte, 1>& reserved_1, std::uint32_t ask_customer_volume, std::uint32_t bid_customer_volume);

    // Source Time Ns: The nanosecond offset from the SourceTime
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Series Index: The unique ID of this series for all products within this market
    std::uint32_t series_index() const;
    void set_series_index(std::uint32_t value);

    // Series Seq Num: The unique ID of this message in the sequence of messages published for
    // this specific series
    std::uint32_t series_seq_num() const;
    void set_series_seq_num(std::uint32_t value);

    // Ask Price: The Ask price. Use the Price scale from the Series Index message.
    std::int32_t ask_price() const;
    void set_ask_price(std::int32_t value);

    // Ask Volume: Total quantity available at the above Ask price
    std::uint32_t ask_volume() const;
    void set_ask_volume(std::uint32_t value);

    // Bid Price: The Bid price. Use the Price scale from the Series Index message.
    std::int32_t bid_price() const;
    void set_bid_price(std::int32_t value);

    // Bid Volume: Total quantity available at the above Bid price.
    std::uint32_t bid_volume() const;
    void set_bid_volume(std::uint32_t value);

    // Quote Condition: Quote Condition
    QuoteCondition quote_condition() const;
    void set_quote_condition(QuoteCondition value);

    // Reserved 1: This field is reserved for future use
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Ask Customer Volume: Total quantity of customer orders at the Ask price
    std::uint32_t ask_customer_volume() const;
    void set_ask_customer_volume(std::uint32_t value);

    // Bid Customer Volume: Total quantity of customer orders at the Bid price
    std::uint32_t bid_customer_volume() const;
    void set_bid_customer_volume(std::uint32_t value);

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

    bool operator==(const OptionsQuoteMessage& other) const;
    bool operator!=(const OptionsQuoteMessage& other) const;

  private:
    std::uint32_t source_time_ns_{};
    std::uint32_t series_index_{};
    std::uint32_t series_seq_num_{};
    std::int32_t ask_price_{};
    std::uint32_t ask_volume_{};
    std::int32_t bid_price_{};
    std::uint32_t bid_volume_{};
    QuoteCondition quote_condition_{};
    std::array<std::byte, 1> reserved_1_{};
    std::uint32_t ask_customer_volume_{};
    std::uint32_t bid_customer_volume_{};
};

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
