#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/AggressorSide.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

class Visitor;

// ExecutionSummary_55Message
class ExecutionSummary55Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ExecutionSummary55Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 64;

    ExecutionSummary55Message() = default;
    ExecutionSummary55Message(std::uint64_t security_id, const std::array<std::byte, 2>& offset_8_padding_2, AggressorSide aggressor_side, const std::array<std::byte, 1>& offset_11_padding_1, Decimal last_px, std::int64_t fill_qty, std::optional<std::int64_t> traded_hidden_qty, std::optional<std::int64_t> cxl_qty, std::optional<std::chrono::nanoseconds> aggressor_time, std::optional<std::uint32_t> rpt_seq, std::optional<std::chrono::nanoseconds> md_entry_timestamp);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Offset 8 Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& offset_8_padding_2() const;
    std::array<std::byte, 2>& offset_8_padding_2();
    void set_offset_8_padding_2(const std::array<std::byte, 2>& value);

    // Aggressor Side: aggressorSide
    AggressorSide aggressor_side() const;
    void set_aggressor_side(AggressorSide value);

    // Offset 11 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_11_padding_1() const;
    std::array<std::byte, 1>& offset_11_padding_1();
    void set_offset_11_padding_1(const std::array<std::byte, 1>& value);

    // Last Px: lastPx
    Decimal last_px() const;
    void set_last_px(Decimal value);

    // Fill Qty: fillQty
    std::int64_t fill_qty() const;
    void set_fill_qty(std::int64_t value);

    // Traded Hidden Qty: tradedHiddenQty
    std::optional<std::int64_t> traded_hidden_qty() const;
    void set_traded_hidden_qty(std::optional<std::int64_t> value);

    // Cxl Qty: cxlQty
    std::optional<std::int64_t> cxl_qty() const;
    void set_cxl_qty(std::optional<std::int64_t> value);

    // Aggressor Time: aggressorTime
    std::optional<std::chrono::nanoseconds> aggressor_time() const;
    void set_aggressor_time(std::optional<std::chrono::nanoseconds> value);

    // Rpt Seq: rptSeq
    std::optional<std::uint32_t> rpt_seq() const;
    void set_rpt_seq(std::optional<std::uint32_t> value);

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

    bool operator==(const ExecutionSummary55Message& other) const;
    bool operator!=(const ExecutionSummary55Message& other) const;

  private:
    std::uint64_t security_id_{};
    std::array<std::byte, 2> offset_8_padding_2_{};
    AggressorSide aggressor_side_{};
    std::array<std::byte, 1> offset_11_padding_1_{};
    Decimal last_px_{ 0, -4 };
    std::int64_t fill_qty_{};
    std::optional<std::int64_t> traded_hidden_qty_{};
    std::optional<std::int64_t> cxl_qty_{};
    std::optional<std::chrono::nanoseconds> aggressor_time_{};
    std::optional<std::uint32_t> rpt_seq_{};
    std::optional<std::chrono::nanoseconds> md_entry_timestamp_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
