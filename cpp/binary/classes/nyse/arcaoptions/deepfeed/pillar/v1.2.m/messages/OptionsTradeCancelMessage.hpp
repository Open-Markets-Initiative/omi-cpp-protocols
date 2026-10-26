#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

class Visitor;

// Published when an earlier trade has been reported in error.
class OptionsTradeCancelMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OptionsTradeCancelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    OptionsTradeCancelMessage() = default;
    OptionsTradeCancelMessage(std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint32_t trade_id);

    // Source Time Ns: The nanosecond offset (UTC Time) from the Time Reference message.
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Series Index: The unique ID of this series within this market.
    std::uint32_t series_index() const;
    void set_series_index(std::uint32_t value);

    // Series Seq Num: The sequence number of this message in the set of all messages for this
    // series
    std::uint32_t series_seq_num() const;
    void set_series_seq_num(std::uint32_t value);

    // Trade Id: Unique ID assigned by the matching engine to this execution.
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

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
    std::uint32_t source_time_ns_{};
    std::uint32_t series_index_{};
    std::uint32_t series_seq_num_{};
    std::uint32_t trade_id_{};
};

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
