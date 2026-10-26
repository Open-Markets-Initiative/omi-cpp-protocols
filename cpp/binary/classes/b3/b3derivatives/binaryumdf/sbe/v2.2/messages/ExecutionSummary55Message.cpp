#include "ExecutionSummary55Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

ExecutionSummary55Message::ExecutionSummary55Message(std::uint64_t security_id, const std::array<std::byte, 2>& offset_8_padding_2, AggressorSide aggressor_side, const std::array<std::byte, 1>& offset_11_padding_1, Decimal last_px, std::int64_t fill_qty, std::optional<std::int64_t> traded_hidden_qty, std::optional<std::int64_t> cxl_qty, std::optional<std::chrono::nanoseconds> aggressor_time, std::optional<std::uint32_t> rpt_seq, std::optional<std::uint64_t> transact_time)
  : security_id_(security_id), offset_8_padding_2_(offset_8_padding_2), aggressor_side_(aggressor_side), offset_11_padding_1_(offset_11_padding_1), last_px_(last_px), fill_qty_(fill_qty), traded_hidden_qty_(traded_hidden_qty), cxl_qty_(cxl_qty), aggressor_time_(aggressor_time), rpt_seq_(rpt_seq), transact_time_(transact_time) {}

std::uint64_t ExecutionSummary55Message::security_id() const { return security_id_; }
void ExecutionSummary55Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const std::array<std::byte, 2>& ExecutionSummary55Message::offset_8_padding_2() const { return offset_8_padding_2_; }
std::array<std::byte, 2>& ExecutionSummary55Message::offset_8_padding_2() { return offset_8_padding_2_; }
void ExecutionSummary55Message::set_offset_8_padding_2(const std::array<std::byte, 2>& value) { offset_8_padding_2_ = value; }

AggressorSide ExecutionSummary55Message::aggressor_side() const { return aggressor_side_; }
void ExecutionSummary55Message::set_aggressor_side(AggressorSide value) { aggressor_side_ = value; }

const std::array<std::byte, 1>& ExecutionSummary55Message::offset_11_padding_1() const { return offset_11_padding_1_; }
std::array<std::byte, 1>& ExecutionSummary55Message::offset_11_padding_1() { return offset_11_padding_1_; }
void ExecutionSummary55Message::set_offset_11_padding_1(const std::array<std::byte, 1>& value) { offset_11_padding_1_ = value; }

Decimal ExecutionSummary55Message::last_px() const { return last_px_; }
void ExecutionSummary55Message::set_last_px(Decimal value) { last_px_ = value; }

std::int64_t ExecutionSummary55Message::fill_qty() const { return fill_qty_; }
void ExecutionSummary55Message::set_fill_qty(std::int64_t value) { fill_qty_ = value; }

std::optional<std::int64_t> ExecutionSummary55Message::traded_hidden_qty() const { return traded_hidden_qty_; }
void ExecutionSummary55Message::set_traded_hidden_qty(std::optional<std::int64_t> value) { traded_hidden_qty_ = value; }

std::optional<std::int64_t> ExecutionSummary55Message::cxl_qty() const { return cxl_qty_; }
void ExecutionSummary55Message::set_cxl_qty(std::optional<std::int64_t> value) { cxl_qty_ = value; }

std::optional<std::chrono::nanoseconds> ExecutionSummary55Message::aggressor_time() const { return aggressor_time_; }
void ExecutionSummary55Message::set_aggressor_time(std::optional<std::chrono::nanoseconds> value) { aggressor_time_ = value; }

std::optional<std::uint32_t> ExecutionSummary55Message::rpt_seq() const { return rpt_seq_; }
void ExecutionSummary55Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

std::optional<std::uint64_t> ExecutionSummary55Message::transact_time() const { return transact_time_; }
void ExecutionSummary55Message::set_transact_time(std::optional<std::uint64_t> value) { transact_time_ = value; }

MessageCode ExecutionSummary55Message::type() const { return message_type; }

std::string_view ExecutionSummary55Message::name() const { return "Execution Summary 55 Message"; }

std::size_t ExecutionSummary55Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ExecutionSummary55Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::read_bytes(data + offset, offset_8_padding_2_.data(), 2);
    offset += 2;

    aggressor_side_ = static_cast<AggressorSide>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, offset_11_padding_1_.data(), 1);
    offset += 1;

    last_px_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    fill_qty_ = wire::read_i64_le(data + offset);
    offset += 8;

    traded_hidden_qty_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    cxl_qty_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    aggressor_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    transact_time_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t ExecutionSummary55Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExecutionSummary55Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_bytes(data + offset, offset_8_padding_2_.data(), 2);
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(aggressor_side_));
    offset += 1;

    wire::write_bytes(data + offset, offset_11_padding_1_.data(), 1);
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(last_px_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(fill_qty_));
    offset += 8;

    wire::write_i64_le(data + offset, traded_hidden_qty_.value_or(static_cast<std::int64_t>(-9223372036854775807LL - 1)));
    offset += 8;

    wire::write_i64_le(data + offset, cxl_qty_.value_or(static_cast<std::int64_t>(-9223372036854775807LL - 1)));
    offset += 8;

    wire::write_u64_le(data + offset, aggressor_time_ ? static_cast<std::uint64_t>(aggressor_time_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, transact_time_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    return offset;
}

std::size_t ExecutionSummary55Message::encoded_size() const {
    return wire_size;
}

void ExecutionSummary55Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExecutionSummary55Message::clone() const {
    return std::make_unique<ExecutionSummary55Message>(*this);
}

void ExecutionSummary55Message::print(std::ostream& out) const {
    out << "ExecutionSummary55Message{";
    out << "security_id=";
    out << security_id_;
    out << ", offset_8_padding_2=";
    print::hex(out, offset_8_padding_2_.data(), offset_8_padding_2_.size());
    out << ", aggressor_side=";
    out << aggressor_side_;
    out << ", offset_11_padding_1=";
    print::hex(out, offset_11_padding_1_.data(), offset_11_padding_1_.size());
    out << ", last_px=";
    out << last_px_;
    out << ", fill_qty=";
    out << fill_qty_;
    out << ", traded_hidden_qty=";
    print::optional(out, traded_hidden_qty_);
    out << ", cxl_qty=";
    print::optional(out, cxl_qty_);
    out << ", aggressor_time=";
    print::optional_duration(out, aggressor_time_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << ", transact_time=";
    print::optional(out, transact_time_);
    out << '}';
}

bool ExecutionSummary55Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExecutionSummary55Message*>(&other);
    return that != nullptr && *this == *that;
}

bool ExecutionSummary55Message::operator==(const ExecutionSummary55Message& other) const {
    return security_id_ == other.security_id_
        && offset_8_padding_2_ == other.offset_8_padding_2_
        && aggressor_side_ == other.aggressor_side_
        && offset_11_padding_1_ == other.offset_11_padding_1_
        && last_px_ == other.last_px_
        && fill_qty_ == other.fill_qty_
        && traded_hidden_qty_ == other.traded_hidden_qty_
        && cxl_qty_ == other.cxl_qty_
        && aggressor_time_ == other.aggressor_time_
        && rpt_seq_ == other.rpt_seq_
        && transact_time_ == other.transact_time_;
}

bool ExecutionSummary55Message::operator!=(const ExecutionSummary55Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
