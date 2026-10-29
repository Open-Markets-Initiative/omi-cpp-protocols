#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/RpiIndicator.hpp"
#include "../messages/Message.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

class Visitor;

// Published when RPI interest (hidden retail price improvement interest) is added or removed
// between the best bid and best offer price. When all RPI interest for this security is
// removed from the book, An RPI message with RPIIndicator = ' ' (space character) is
// published.
class RetailPriceImprovementMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::RetailPriceImprovementMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 13;

    RetailPriceImprovementMessage() = default;
    RetailPriceImprovementMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, RpiIndicator rpi_indicator);

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

    // Rpi Indicator: The side(s) where Retail Price Improvement orders (RPI orders) exist.
    RpiIndicator rpi_indicator() const;
    void set_rpi_indicator(RpiIndicator value);

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

    bool operator==(const RetailPriceImprovementMessage& other) const;
    bool operator!=(const RetailPriceImprovementMessage& other) const;

  private:
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    RpiIndicator rpi_indicator_{};
};

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
