#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

class Visitor;

// On a separate channel from the main feed, the Stock Summary channel, a Stock Summary message
// per symbol is sent every 60 seconds. The message is sent regardless of whether there has
// been a change to the symbol in the last 60 seconds or not.
class StockSummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::StockSummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    StockSummaryMessage() = default;
    StockSummaryMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t high_price, std::uint32_t low_price, std::uint32_t open, std::uint32_t close, std::uint32_t total_volume);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Time Ns: The nanosecond offset from the SourceTime
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Symbol Index: The unique ID of this symbol for all products within this market. This ID
    // cannot be used to cross reference a security between markets.
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // High Price: The exchange high price of this stock for the day. Use the Price Scale in
    // the symbol index msg.
    std::uint32_t high_price() const;
    void set_high_price(std::uint32_t value);

    // Low Price: The exchange Low price of this stock for the day. Use the Price Scale in the
    // symbol index msg.
    std::uint32_t low_price() const;
    void set_low_price(std::uint32_t value);

    // Open: The exchange Opening price of this stock for the day. Use the Price Scale in the
    // symbol index msg.
    std::uint32_t open() const;
    void set_open(std::uint32_t value);

    // Close: The exchange Closing price of this stock for the day. Use the Price Scale in the
    // symbol index msg.
    std::uint32_t close() const;
    void set_close(std::uint32_t value);

    // Total Volume: The exchange cumulative volume for the stock throughout the day.
    std::uint32_t total_volume() const;
    void set_total_volume(std::uint32_t value);

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

    bool operator==(const StockSummaryMessage& other) const;
    bool operator!=(const StockSummaryMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t high_price_{};
    std::uint32_t low_price_{};
    std::uint32_t open_{};
    std::uint32_t close_{};
    std::uint32_t total_volume_{};
};

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
