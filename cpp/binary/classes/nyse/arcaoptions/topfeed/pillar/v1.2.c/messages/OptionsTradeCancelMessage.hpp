#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

class Visitor;

// In the event that an earlier trade has been reported in error, an Options Trade Cancel
// message is sent
class OptionsTradeCancelMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OptionsTradeCancelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 20;

    OptionsTradeCancelMessage() = default;
    OptionsTradeCancelMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint32_t original_trade_id);

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

    // Series Seq Num: The unique ID of this message in the sequence of messages published for
    // this specific series
    std::uint32_t series_seq_num() const;
    void set_series_seq_num(std::uint32_t value);

    // Original Trade Id: The original TradeID of the Trade being cancelled.
    std::uint32_t original_trade_id() const;
    void set_original_trade_id(std::uint32_t value);

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

    bool operator==(const OptionsTradeCancelMessage& other) const;
    bool operator!=(const OptionsTradeCancelMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t series_index_{};
    std::uint32_t series_seq_num_{};
    std::uint32_t original_trade_id_{};
};

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
