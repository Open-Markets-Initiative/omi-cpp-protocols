#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/QuoteCondition.hpp"
#include "../enums/RpiIndicator.hpp"
#include "../messages/Message.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

class Visitor;

// A quote message is sent when any event results in a new top of book value on either side of
// the market.
class QuoteMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::QuoteMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 34;

    QuoteMessage() = default;
    QuoteMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t ask_price, std::uint32_t ask_volume, std::uint32_t bid_price, std::uint32_t bid_volume, QuoteCondition quote_condition, RpiIndicator rpi_indicator, const std::array<std::byte, 4>& reserved_4);

    // Source Time Ns: The nanosecond offset from the SourceTime
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Symbol Index: The unique ID of this symbol for all products within this market. This ID
    // cannot be used to cross reference a security between markets.
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Symbol Seq Num: Reserved for future use. Ignore any content. This usage will become
    // standard across all products in future releases.
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Ask Price: The Ask price. Use the Price scale from the Symbol Index message.
    std::uint32_t ask_price() const;
    void set_ask_price(std::uint32_t value);

    // Ask Volume: The aggregate round lot size at the ask price, in shares.
    std::uint32_t ask_volume() const;
    void set_ask_volume(std::uint32_t value);

    // Bid Price: The Bid price. Use the Price scale from the Symbol Index message.
    std::uint32_t bid_price() const;
    void set_bid_price(std::uint32_t value);

    // Bid Volume: The aggregate round lot size at the bid price, in shares.
    std::uint32_t bid_volume() const;
    void set_bid_volume(std::uint32_t value);

    // Quote Condition: Quote condition values. For markets other than NYSE, only condition R
    // is applicable.
    QuoteCondition quote_condition() const;
    void set_quote_condition(QuoteCondition value);

    // Rpi Indicator: The side(s) where Retail Price Indication orders (RPI orders) exist.
    RpiIndicator rpi_indicator() const;
    void set_rpi_indicator(RpiIndicator value);

    // Reserved 4: Future use. Any field content should be ignored.
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

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
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint32_t ask_price_{};
    std::uint32_t ask_volume_{};
    std::uint32_t bid_price_{};
    std::uint32_t bid_volume_{};
    QuoteCondition quote_condition_{};
    RpiIndicator rpi_indicator_{};
    std::array<std::byte, 4> reserved_4_{};
};

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
