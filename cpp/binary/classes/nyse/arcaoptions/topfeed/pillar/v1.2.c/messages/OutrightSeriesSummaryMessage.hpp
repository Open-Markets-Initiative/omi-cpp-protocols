#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

class Visitor;

// The Series Summary message will provide the following trade statistics per series: high,
// low, open, close and total volume
class OutrightSeriesSummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OutrightSeriesSummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    OutrightSeriesSummaryMessage() = default;
    OutrightSeriesSummaryMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::int32_t high_price, std::int32_t low_price, std::int32_t open, std::int32_t close, std::uint32_t total_volume);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Time Ns: The nanosecond offset from the SourceTime
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Series Index: The unique ID of this series for all products within this market
    std::uint32_t series_index() const;
    void set_series_index(std::uint32_t value);

    // High Price: The Highest price of the series for the day. Use the Price scale from the
    // series mapping index.
    std::int32_t high_price() const;
    void set_high_price(std::int32_t value);

    // Low Price: The Lowest price of the series for the day. Use the Price scale from the
    // series mapping index.
    std::int32_t low_price() const;
    void set_low_price(std::int32_t value);

    // Open: The First price of the series for the day. Use the Price scale from the series
    // mapping index.
    std::int32_t open() const;
    void set_open(std::int32_t value);

    // Close: The Last price of the series for the day. Use the Price scale from the series
    // index mapping.
    std::int32_t close() const;
    void set_close(std::int32_t value);

    // Total Volume: The cumulative volume for the outright series throughout the day.
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

    bool operator==(const OutrightSeriesSummaryMessage& other) const;
    bool operator!=(const OutrightSeriesSummaryMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t series_index_{};
    std::int32_t high_price_{};
    std::int32_t low_price_{};
    std::int32_t open_{};
    std::int32_t close_{};
    std::uint32_t total_volume_{};
};

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
