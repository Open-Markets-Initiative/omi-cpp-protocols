#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/QuoteCondition.hpp"
#include "../messages/Message.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

class Visitor;

// The Sell Market Depth message provides prices and aggregated volumes for each of the best
// three Sell levels.
class OutrightMarketDepthSellMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OutrightMarketDepthSellMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 44;

    OutrightMarketDepthSellMessage() = default;
    OutrightMarketDepthSellMessage(std::uint32_t source_time, std::uint32_t source_ns, std::uint32_t series_index, std::uint32_t symbol_seq_num, std::int32_t first_level_price, std::int32_t second_level_price, std::int32_t third_level_price, std::uint16_t first_volume, std::uint16_t second_volume, std::uint16_t third_volume, QuoteCondition quote_condition, const std::array<std::byte, 1>& reserved_1, std::uint16_t first_level_customer_volume, std::uint16_t second_level_customer_volume, std::uint16_t third_level_customer_volume, const std::array<std::byte, 2>& reserved_2);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Ns: The nanosecond offset from the SourceTime.
    std::uint32_t source_ns() const;
    void set_source_ns(std::uint32_t value);

    // Series Index: The unique ID of the symbol in the Series Index message
    std::uint32_t series_index() const;
    void set_series_index(std::uint32_t value);

    // Symbol Seq Num: Sequence number of messages for the Outright options symbol.
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // First Level Price: Price of first buy level
    std::int32_t first_level_price() const;
    void set_first_level_price(std::int32_t value);

    // Second Level Price: Price of second buy level
    std::int32_t second_level_price() const;
    void set_second_level_price(std::int32_t value);

    // Third Level Price: Price of third buy level
    std::int32_t third_level_price() const;
    void set_third_level_price(std::int32_t value);

    // First Volume: Total volume at First price level
    std::uint16_t first_volume() const;
    void set_first_volume(std::uint16_t value);

    // Second Volume: Total volume at Second price level
    std::uint16_t second_volume() const;
    void set_second_volume(std::uint16_t value);

    // Third Volume: Total volume at Third price level
    std::uint16_t third_volume() const;
    void set_third_volume(std::uint16_t value);

    // Quote Condition: QuoteCondition values
    QuoteCondition quote_condition() const;
    void set_quote_condition(QuoteCondition value);

    // Reserved 1: Filler
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // First Level Customer Volume: Total volume of customer orders at the first level
    std::uint16_t first_level_customer_volume() const;
    void set_first_level_customer_volume(std::uint16_t value);

    // Second Level Customer Volume: Total volume of customer orders at the second level
    std::uint16_t second_level_customer_volume() const;
    void set_second_level_customer_volume(std::uint16_t value);

    // Third Level Customer Volume: Total volume of customer orders at the third level
    std::uint16_t third_level_customer_volume() const;
    void set_third_level_customer_volume(std::uint16_t value);

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

    bool operator==(const OutrightMarketDepthSellMessage& other) const;
    bool operator!=(const OutrightMarketDepthSellMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_ns_{};
    std::uint32_t series_index_{};
    std::uint32_t symbol_seq_num_{};
    std::int32_t first_level_price_{};
    std::int32_t second_level_price_{};
    std::int32_t third_level_price_{};
    std::uint16_t first_volume_{};
    std::uint16_t second_volume_{};
    std::uint16_t third_volume_{};
    QuoteCondition quote_condition_{};
    std::array<std::byte, 1> reserved_1_{};
    std::uint16_t first_level_customer_volume_{};
    std::uint16_t second_level_customer_volume_{};
    std::uint16_t third_level_customer_volume_{};
    std::array<std::byte, 2> reserved_2_{};
};

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
