#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

class Visitor;

// ChannelReset_11Message
class ChannelReset11Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ChannelReset11Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 12;

    ChannelReset11Message() = default;
    ChannelReset11Message(const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 3>& offset_1_padding_3, std::optional<std::chrono::nanoseconds> md_entry_timestamp);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Offset 1 Padding 3: 3 bytes padding
    const std::array<std::byte, 3>& offset_1_padding_3() const;
    std::array<std::byte, 3>& offset_1_padding_3();
    void set_offset_1_padding_3(const std::array<std::byte, 3>& value);

    // Md Entry Timestamp: mDEntryTimestamp
    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const;
    void set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value);

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

    bool operator==(const ChannelReset11Message& other) const;
    bool operator!=(const ChannelReset11Message& other) const;

  private:
    MatchEventIndicator match_event_indicator_{};
    std::array<std::byte, 3> offset_1_padding_3_{};
    std::optional<std::chrono::nanoseconds> md_entry_timestamp_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
