#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

class Visitor;

// The stock summary message is sent every 1 minute on a separate channel from the main trades
// feed.
class StockSummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::StockSummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    StockSummaryMessage() = default;
    StockSummaryMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::int32_t high_price, std::int32_t low_price, std::uint32_t open, std::uint32_t close, std::uint32_t total_volume);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Time Ns: The nanosecond offset from the Source Time
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Symbol Index: The ID of the symbol in the Symbol Index message
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // High Price: The High price of the stock for the day. Use the Price scale from the symbol
    // mapping index.
    std::int32_t high_price() const;
    void set_high_price(std::int32_t value);

    // Low Price: The Low price of the stock for the day. Use the Price scale from the symbol
    // mapping index.
    std::int32_t low_price() const;
    void set_low_price(std::int32_t value);

    // Open: The Opening price of the stock for the day. Use the Price scale from the symbol
    // mapping index.
    std::uint32_t open() const;
    void set_open(std::uint32_t value);

    // Close: The Closing price of the stock for the day. Use the Price scale from the symbol
    // mapping index.
    std::uint32_t close() const;
    void set_close(std::uint32_t value);

    // Total Volume: The cumulative volume for the stock throughout the day.
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
    std::int32_t high_price_{};
    std::int32_t low_price_{};
    std::uint32_t open_{};
    std::uint32_t close_{};
    std::uint32_t total_volume_{};
};

} // namespace nyse::nationalequities::trades::pillar::v2_6
