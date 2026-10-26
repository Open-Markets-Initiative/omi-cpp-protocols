#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

class Visitor;

// The Trade Break message is sent whenever an execution on Cboe is broken. Trade breaks are
// rare and only affect applications that rely upon Cboe execution-based data. Applications
// that simply build a Cboe book can ignore Trade Break messages.
class TradeBreakMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeBreakMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 12;

    TradeBreakMessage() = default;
    TradeBreakMessage(std::chrono::nanoseconds time_offset, std::uint64_t execution_id);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Execution Id: Cboe generated day-unique execution identifier of this execution.
    // Execution Id is also referenced in the Trade Break message.
    std::uint64_t execution_id() const;
    void set_execution_id(std::uint64_t value);

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

    bool operator==(const TradeBreakMessage& other) const;
    bool operator!=(const TradeBreakMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t execution_id_{};
};

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
