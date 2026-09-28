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
#include "../common/Decimal.hpp"
#include "../enums/MdEntryType.hpp"
#include "../enums/MdUpdateAction.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

class Visitor;

// Order_MBO_50Message
class OrderMbO50Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::OrderMbO50Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 72;

    OrderMbO50Message() = default;
    OrderMbO50Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, MdUpdateAction md_update_action, MdEntryType md_entry_type, const std::array<std::byte, 1>& offset_11_padding_1, std::optional<Decimal> md_corporate_offset_price_optional, std::int64_t md_entry_size_quantity, const std::array<std::byte, 4>& offset_28_padding_4, std::optional<std::uint32_t> entering_firm, std::optional<std::chrono::nanoseconds> md_insert_timestamp, std::uint64_t secondary_order_id, std::optional<std::uint32_t> rpt_seq, std::optional<std::uint64_t> transact_time, std::optional<std::int64_t> md_entry_prev_size);

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

    // Md Entry Type: mDEntryType
    MdEntryType md_entry_type() const;
    void set_md_entry_type(MdEntryType value);

    // Offset 11 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_11_padding_1() const;
    std::array<std::byte, 1>& offset_11_padding_1();
    void set_offset_11_padding_1(const std::array<std::byte, 1>& value);

    // Md Corporate Offset Price Optional: mDEntryPx
    std::optional<Decimal> md_corporate_offset_price_optional() const;
    void set_md_corporate_offset_price_optional(std::optional<Decimal> value);

    // Md Entry Size Quantity: mDEntrySize
    std::int64_t md_entry_size_quantity() const;
    void set_md_entry_size_quantity(std::int64_t value);

    // Offset 28 Padding 4: 4 bytes padding
    const std::array<std::byte, 4>& offset_28_padding_4() const;
    std::array<std::byte, 4>& offset_28_padding_4();
    void set_offset_28_padding_4(const std::array<std::byte, 4>& value);

    // Entering Firm: enteringFirm
    std::optional<std::uint32_t> entering_firm() const;
    void set_entering_firm(std::optional<std::uint32_t> value);

    // Md Insert Timestamp: mDInsertTimestamp
    std::optional<std::chrono::nanoseconds> md_insert_timestamp() const;
    void set_md_insert_timestamp(std::optional<std::chrono::nanoseconds> value);

    // Secondary Order Id: secondaryOrderID
    std::uint64_t secondary_order_id() const;
    void set_secondary_order_id(std::uint64_t value);

    // Rpt Seq: rptSeq
    std::optional<std::uint32_t> rpt_seq() const;
    void set_rpt_seq(std::optional<std::uint32_t> value);

    // Transact Time: transactTime
    std::optional<std::uint64_t> transact_time() const;
    void set_transact_time(std::optional<std::uint64_t> value);

    // Md Entry Prev Size: mDEntryPrevSize
    std::optional<std::int64_t> md_entry_prev_size() const;
    void set_md_entry_prev_size(std::optional<std::int64_t> value);

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

    bool operator==(const OrderMbO50Message& other) const;
    bool operator!=(const OrderMbO50Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    MdUpdateAction md_update_action_{};
    MdEntryType md_entry_type_{};
    std::array<std::byte, 1> offset_11_padding_1_{};
    std::optional<Decimal> md_corporate_offset_price_optional_{};
    std::int64_t md_entry_size_quantity_{};
    std::array<std::byte, 4> offset_28_padding_4_{};
    std::optional<std::uint32_t> entering_firm_{};
    std::optional<std::chrono::nanoseconds> md_insert_timestamp_{};
    std::uint64_t secondary_order_id_{};
    std::optional<std::uint32_t> rpt_seq_{};
    std::optional<std::uint64_t> transact_time_{};
    std::optional<std::int64_t> md_entry_prev_size_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
