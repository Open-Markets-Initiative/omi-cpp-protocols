#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../bitfields/ImbalanceCondition.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../enums/MdUpdateAction.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

class Visitor;

// AuctionImbalance_19Message
class AuctionImbalance19Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::AuctionImbalance19Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    AuctionImbalance19Message() = default;
    AuctionImbalance19Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, MdUpdateAction md_update_action, const ImbalanceCondition& imbalance_condition, std::optional<std::int64_t> md_entry_size_quantity_optional, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq);

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

    // Imbalance Condition: ImbalanceCondition bit set
    const ImbalanceCondition& imbalance_condition() const;
    ImbalanceCondition& imbalance_condition();
    void set_imbalance_condition(const ImbalanceCondition& value);

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

    bool operator==(const AuctionImbalance19Message& other) const;
    bool operator!=(const AuctionImbalance19Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    MdUpdateAction md_update_action_{};
    ImbalanceCondition imbalance_condition_{};
    std::optional<std::int64_t> md_entry_size_quantity_optional_{};
    std::optional<std::chrono::nanoseconds> md_entry_timestamp_{};
    std::optional<std::uint32_t> rpt_seq_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
