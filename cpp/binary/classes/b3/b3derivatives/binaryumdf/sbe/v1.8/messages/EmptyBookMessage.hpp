#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

class Visitor;

// EmptyBook_9Message
class EmptyBookMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::EmptyBook9Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 20;

    EmptyBookMessage() = default;
    EmptyBookMessage(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 3>& offset_9_padding_3, std::optional<std::chrono::nanoseconds> md_entry_timestamp);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Offset 9 Padding 3: 3 bytes padding
    const std::array<std::byte, 3>& offset_9_padding_3() const;
    std::array<std::byte, 3>& offset_9_padding_3();
    void set_offset_9_padding_3(const std::array<std::byte, 3>& value);

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

    bool operator==(const EmptyBookMessage& other) const;
    bool operator!=(const EmptyBookMessage& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    std::array<std::byte, 3> offset_9_padding_3_{};
    std::optional<std::chrono::nanoseconds> md_entry_timestamp_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
