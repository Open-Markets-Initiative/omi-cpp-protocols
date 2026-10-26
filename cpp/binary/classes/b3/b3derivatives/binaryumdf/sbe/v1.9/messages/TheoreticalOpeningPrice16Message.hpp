#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MdUpdateAction.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

class Visitor;

// TheoreticalOpeningPrice_16Message
class TheoreticalOpeningPrice16Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::TheoreticalOpeningPrice16Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    TheoreticalOpeningPrice16Message() = default;
    TheoreticalOpeningPrice16Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, MdUpdateAction md_update_action, std::uint16_t trade_date, std::optional<Decimal> md_corporate_offset_price_optional, std::optional<std::int64_t> md_entry_size_quantity_optional, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Md Update Action: mDUpdateAction
    MdUpdateAction md_update_action() const;
    void set_md_update_action(MdUpdateAction value);

    // Trade Date: tradeDate
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Md Corporate Offset Price Optional: mDEntryPx
    std::optional<Decimal> md_corporate_offset_price_optional() const;
    void set_md_corporate_offset_price_optional(std::optional<Decimal> value);

    // Md Entry Size Quantity Optional: mDEntrySize
    std::optional<std::int64_t> md_entry_size_quantity_optional() const;
    void set_md_entry_size_quantity_optional(std::optional<std::int64_t> value);

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

    bool operator==(const TheoreticalOpeningPrice16Message& other) const;
    bool operator!=(const TheoreticalOpeningPrice16Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    MdUpdateAction md_update_action_{};
    std::uint16_t trade_date_{};
    std::optional<Decimal> md_corporate_offset_price_optional_{};
    std::optional<std::int64_t> md_entry_size_quantity_optional_{};
    std::optional<std::chrono::nanoseconds> md_entry_timestamp_{};
    std::optional<std::uint32_t> rpt_seq_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
