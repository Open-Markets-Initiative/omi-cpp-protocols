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

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

class Visitor;

// OpenInterest_29Message
class OpenInterest29Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::OpenInterest29Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    OpenInterest29Message() = default;
    OpenInterest29Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 1>& offset_9_padding_1, std::uint16_t trade_date, std::int64_t md_entry_size_quantity, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Offset 9 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_9_padding_1() const;
    std::array<std::byte, 1>& offset_9_padding_1();
    void set_offset_9_padding_1(const std::array<std::byte, 1>& value);

    // Trade Date: tradeDate
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Md Entry Size Quantity: mDEntrySize
    std::int64_t md_entry_size_quantity() const;
    void set_md_entry_size_quantity(std::int64_t value);

    // Md Entry Timestamp: mDEntryTimestamp
    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const;
    void set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value);

    // Rpt Seq: rptSeq
    std::optional<std::uint32_t> rpt_seq() const;
    void set_rpt_seq(std::optional<std::uint32_t> value);

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

    bool operator==(const OpenInterest29Message& other) const;
    bool operator!=(const OpenInterest29Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    std::array<std::byte, 1> offset_9_padding_1_{};
    std::uint16_t trade_date_{};
    std::int64_t md_entry_size_quantity_{};
    std::optional<std::chrono::nanoseconds> md_entry_timestamp_{};
    std::optional<std::uint32_t> rpt_seq_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
