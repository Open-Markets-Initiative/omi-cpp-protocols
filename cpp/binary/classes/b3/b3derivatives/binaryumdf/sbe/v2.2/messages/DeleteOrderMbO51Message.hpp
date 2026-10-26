#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MdEntryType.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

class Visitor;

// DeleteOrder_MBO_51Message
class DeleteOrderMbO51Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::DeleteOrderMbO51Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 52;

    DeleteOrderMbO51Message() = default;
    DeleteOrderMbO51Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 1>& offset_9_padding_1, MdEntryType md_entry_type, const std::array<std::byte, 5>& offset_11_padding_5, std::int64_t md_entry_size_quantity, std::uint64_t secondary_order_id, std::optional<std::uint64_t> transact_time, std::optional<std::uint32_t> rpt_seq, std::optional<Decimal> md_corporate_offset_price_optional);

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

    // Md Entry Type: mDEntryType
    MdEntryType md_entry_type() const;
    void set_md_entry_type(MdEntryType value);

    // Offset 11 Padding 5: 5 bytes padding
    const std::array<std::byte, 5>& offset_11_padding_5() const;
    std::array<std::byte, 5>& offset_11_padding_5();
    void set_offset_11_padding_5(const std::array<std::byte, 5>& value);

    // Md Entry Size Quantity: mDEntrySize
    std::int64_t md_entry_size_quantity() const;
    void set_md_entry_size_quantity(std::int64_t value);

    // Secondary Order Id: secondaryOrderID
    std::uint64_t secondary_order_id() const;
    void set_secondary_order_id(std::uint64_t value);

    // Transact Time: transactTime
    std::optional<std::uint64_t> transact_time() const;
    void set_transact_time(std::optional<std::uint64_t> value);

    // Rpt Seq: rptSeq
    std::optional<std::uint32_t> rpt_seq() const;
    void set_rpt_seq(std::optional<std::uint32_t> value);

    // Md Corporate Offset Price Optional: mDEntryPx
    std::optional<Decimal> md_corporate_offset_price_optional() const;
    void set_md_corporate_offset_price_optional(std::optional<Decimal> value);

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

    bool operator==(const DeleteOrderMbO51Message& other) const;
    bool operator!=(const DeleteOrderMbO51Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    std::array<std::byte, 1> offset_9_padding_1_{};
    MdEntryType md_entry_type_{};
    std::array<std::byte, 5> offset_11_padding_5_{};
    std::int64_t md_entry_size_quantity_{};
    std::uint64_t secondary_order_id_{};
    std::optional<std::uint64_t> transact_time_{};
    std::optional<std::uint32_t> rpt_seq_{};
    std::optional<Decimal> md_corporate_offset_price_optional_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
