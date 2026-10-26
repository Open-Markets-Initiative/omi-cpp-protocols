#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/Message.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

class Visitor;

// A Time message is immediately generated and sent when there is a PITCH event for a given
// clock second.
class TimeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TimeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 8;

    TimeMessage() = default;
    TimeMessage(std::chrono::seconds time_reference, std::uint32_t epoch_time);

    // Time Reference: Number of whole seconds from midnight Central Time.
    std::chrono::seconds time_reference() const;
    void set_time_reference(std::chrono::seconds value);
    std::int64_t time_reference_utc(const calendar::Day& day) const;

    // Epoch Time: Number of whole seconds since the Epoch (Midnight January 1, 1970 UTC).
    std::uint32_t epoch_time() const;
    void set_epoch_time(std::uint32_t value);

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

    bool operator==(const TimeMessage& other) const;
    bool operator!=(const TimeMessage& other) const;

  private:
    std::chrono::seconds time_reference_{};
    std::uint32_t epoch_time_{};
};

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
