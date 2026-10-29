#include "ExecutionSummary.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

ExecutionSummary::ExecutionSummary(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> aggressor_time, std::optional<std::chrono::nanoseconds> request_time, std::optional<std::chrono::nanoseconds> exec_id, std::optional<std::int32_t> last_qty, std::optional<AggressorSide> aggressor_side, std::optional<TradeCondition> trade_condition, const std::array<std::byte, 2>& pad2, std::optional<Decimal> last_px, std::optional<std::int32_t> resting_hidden_qty, std::optional<std::int32_t> resting_cxl_qty)
  : security_id_(security_id), aggressor_time_(aggressor_time), request_time_(request_time), exec_id_(exec_id), last_qty_(last_qty), aggressor_side_(aggressor_side), trade_condition_(trade_condition), pad2_(pad2), last_px_(last_px), resting_hidden_qty_(resting_hidden_qty), resting_cxl_qty_(resting_cxl_qty) {}

std::optional<std::int64_t> ExecutionSummary::security_id() const { return security_id_; }
void ExecutionSummary::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<std::chrono::nanoseconds> ExecutionSummary::aggressor_time() const { return aggressor_time_; }
void ExecutionSummary::set_aggressor_time(std::optional<std::chrono::nanoseconds> value) { aggressor_time_ = value; }

std::optional<std::chrono::nanoseconds> ExecutionSummary::request_time() const { return request_time_; }
void ExecutionSummary::set_request_time(std::optional<std::chrono::nanoseconds> value) { request_time_ = value; }

std::optional<std::chrono::nanoseconds> ExecutionSummary::exec_id() const { return exec_id_; }
void ExecutionSummary::set_exec_id(std::optional<std::chrono::nanoseconds> value) { exec_id_ = value; }

std::optional<std::int32_t> ExecutionSummary::last_qty() const { return last_qty_; }
void ExecutionSummary::set_last_qty(std::optional<std::int32_t> value) { last_qty_ = value; }

std::optional<AggressorSide> ExecutionSummary::aggressor_side() const { return aggressor_side_; }
void ExecutionSummary::set_aggressor_side(std::optional<AggressorSide> value) { aggressor_side_ = value; }

std::optional<TradeCondition> ExecutionSummary::trade_condition() const { return trade_condition_; }
void ExecutionSummary::set_trade_condition(std::optional<TradeCondition> value) { trade_condition_ = value; }

const std::array<std::byte, 2>& ExecutionSummary::pad2() const { return pad2_; }
std::array<std::byte, 2>& ExecutionSummary::pad2() { return pad2_; }
void ExecutionSummary::set_pad2(const std::array<std::byte, 2>& value) { pad2_ = value; }

std::optional<Decimal> ExecutionSummary::last_px() const { return last_px_; }
void ExecutionSummary::set_last_px(std::optional<Decimal> value) { last_px_ = value; }

std::optional<std::int32_t> ExecutionSummary::resting_hidden_qty() const { return resting_hidden_qty_; }
void ExecutionSummary::set_resting_hidden_qty(std::optional<std::int32_t> value) { resting_hidden_qty_ = value; }

std::optional<std::int32_t> ExecutionSummary::resting_cxl_qty() const { return resting_cxl_qty_; }
void ExecutionSummary::set_resting_cxl_qty(std::optional<std::int32_t> value) { resting_cxl_qty_ = value; }

MessageCode ExecutionSummary::type() const { return message_type; }

std::string_view ExecutionSummary::name() const { return "Execution Summary"; }

std::size_t ExecutionSummary::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ExecutionSummary", wire_size, length);

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    aggressor_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    request_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    exec_id_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    last_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    aggressor_side_ = wire::nullable_enum<AggressorSide>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    trade_condition_ = wire::nullable_enum<TradeCondition>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    last_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    resting_hidden_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    resting_cxl_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    return offset;
}

std::size_t ExecutionSummary::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExecutionSummary", wire_size, capacity);

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_u64_le(data + offset, aggressor_time_ ? static_cast<std::uint64_t>(aggressor_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u64_le(data + offset, request_time_ ? static_cast<std::uint64_t>(request_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u64_le(data + offset, exec_id_ ? static_cast<std::uint64_t>(exec_id_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i32_le(data + offset, last_qty_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_u8(data + offset, aggressor_side_ ? static_cast<std::uint8_t>(*aggressor_side_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, trade_condition_ ? static_cast<std::uint8_t>(*trade_condition_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    wire::write_i64_le(data + offset, last_px_ ? static_cast<std::int64_t>(last_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i32_le(data + offset, resting_hidden_qty_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_i32_le(data + offset, resting_cxl_qty_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    return offset;
}

std::size_t ExecutionSummary::encoded_size() const {
    return wire_size;
}

void ExecutionSummary::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExecutionSummary::clone() const {
    return std::make_unique<ExecutionSummary>(*this);
}

void ExecutionSummary::print(std::ostream& out) const {
    out << "ExecutionSummary{";
    out << "security_id=";
    print::optional(out, security_id_);
    out << ", aggressor_time=";
    print::optional_duration(out, aggressor_time_);
    out << ", request_time=";
    print::optional_duration(out, request_time_);
    out << ", exec_id=";
    print::optional_duration(out, exec_id_);
    out << ", last_qty=";
    print::optional(out, last_qty_);
    out << ", aggressor_side=";
    print::optional(out, aggressor_side_);
    out << ", trade_condition=";
    print::optional(out, trade_condition_);
    out << ", pad2=";
    print::hex(out, pad2_.data(), pad2_.size());
    out << ", last_px=";
    print::optional(out, last_px_);
    out << ", resting_hidden_qty=";
    print::optional(out, resting_hidden_qty_);
    out << ", resting_cxl_qty=";
    print::optional(out, resting_cxl_qty_);
    out << '}';
}

bool ExecutionSummary::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExecutionSummary*>(&other);
    return that != nullptr && *this == *that;
}

bool ExecutionSummary::operator==(const ExecutionSummary& other) const {
    return security_id_ == other.security_id_
        && aggressor_time_ == other.aggressor_time_
        && request_time_ == other.request_time_
        && exec_id_ == other.exec_id_
        && last_qty_ == other.last_qty_
        && aggressor_side_ == other.aggressor_side_
        && trade_condition_ == other.trade_condition_
        && pad2_ == other.pad2_
        && last_px_ == other.last_px_
        && resting_hidden_qty_ == other.resting_hidden_qty_
        && resting_cxl_qty_ == other.resting_cxl_qty_;
}

bool ExecutionSummary::operator!=(const ExecutionSummary& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v6_0
