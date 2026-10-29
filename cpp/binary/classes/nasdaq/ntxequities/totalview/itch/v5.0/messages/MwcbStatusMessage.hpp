#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/BreachedLevel.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

class Visitor;

// Informs data recipients when a MWCB has breached one of the established levels
class MwcbStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::MwcbStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 11;

    MwcbStatusMessage() = default;
    MwcbStatusMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, BreachedLevel breached_level);

    // Stock Locate: Always 0
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq Texas internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Breached Level: Denotes the MWCB Level that was breached.
    BreachedLevel breached_level() const;
    void set_breached_level(BreachedLevel value);

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

    bool operator==(const MwcbStatusMessage& other) const;
    bool operator!=(const MwcbStatusMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    BreachedLevel breached_level_{};
};

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
