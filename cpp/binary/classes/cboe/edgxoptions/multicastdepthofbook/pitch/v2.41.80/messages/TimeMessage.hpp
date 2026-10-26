#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/Message.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

class Visitor;

// A Time message is immediately generated and sent when there is a PITCH event for a given
// clock second. If there is no PITCH event for a given clock second, then no Time message is
// sent for that second. The Time field is the number of seconds relative to midnight Eastern
// Time. All subsequent time offset fields for the same unit will use the new Time message
// value as the base until another Time message is received for the same unit.
class TimeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TimeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    TimeMessage() = default;
    TimeMessage(std::chrono::seconds time);

    // Time: Number of whole seconds elapsed since the start of the current Eastern Time
    // calendar day, derived by converting the current Eastern wall clock time (HH:MM:SS) to
    // seconds. On Daylight Saving Time transition days, Time reflects wall clock seconds and
    // does not adjust for the UTC offset change. On a DST spring-forward day, the maximum
    // value will be 82,799 (23 hours). On a DST fall-back day, values between 3,600 and 7,199
    // will appear twice. Recipients requiring unambiguous absolute timestamps should use Epoch
    // Time (where available) or Midnight Reference in the Time Reference message.
    std::chrono::seconds time() const;
    void set_time(std::chrono::seconds value);
    std::int64_t time_utc(const calendar::Day& day) const;

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
    std::chrono::seconds time_{};
};

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
