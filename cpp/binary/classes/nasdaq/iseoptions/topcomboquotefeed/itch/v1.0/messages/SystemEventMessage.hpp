#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/EventCode.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

class Visitor;

// The system event message type is used to signal a market or data feed handler event.
class SystemEventMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SystemEventMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 13;

    SystemEventMessage() = default;
    SystemEventMessage(std::chrono::nanoseconds timestamp, EventCode event_code, std::uint16_t current_year, std::uint8_t current_month, std::uint8_t current_day, std::uint8_t version, std::uint8_t sub_version);

    // Timestamp: The time, expressed as the number of nanoseconds after midnight.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Event Code: Refer to System Event Codes below
    EventCode event_code() const;
    void set_event_code(EventCode value);

    // Current Year: The current calendar year (example: 2016).
    std::uint16_t current_year() const;
    void set_current_year(std::uint16_t value);

    // Current Month: The current calendar month, with values 1 to 12 inclusive, January=1,
    // etc.
    std::uint8_t current_month() const;
    void set_current_month(std::uint8_t value);

    // Current Day: The current calendar day, with values 1 to 31 inclusive.
    std::uint8_t current_day() const;
    void set_current_day(std::uint8_t value);

    // Version: Version of this interface. Currently set to 1.
    std::uint8_t version() const;
    void set_version(std::uint8_t value);

    // Sub Version: Sub-version of this interface. Currently set to 0.
    std::uint8_t sub_version() const;
    void set_sub_version(std::uint8_t value);

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

    bool operator==(const SystemEventMessage& other) const;
    bool operator!=(const SystemEventMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    EventCode event_code_{};
    std::uint16_t current_year_{};
    std::uint8_t current_month_{};
    std::uint8_t current_day_{};
    std::uint8_t version_{};
    std::uint8_t sub_version_{};
};

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
