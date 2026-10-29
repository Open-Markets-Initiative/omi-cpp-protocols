#include "ExecutionSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

ExecutionSummaryMessage::ExecutionSummaryMessage(std::int64_t security_id, std::optional<std::chrono::nanoseconds> aggressor_timestamp, std::chrono::nanoseconds exec_id, std::int64_t last_qty, AggressorSide aggressor_side, std::optional<TradeCondition> trade_condition, const std::array<std::byte, 6>& pad_6, Decimal last_px, std::optional<std::int64_t> resting_hidden_qty)
  : security_id_(security_id), aggressor_timestamp_(aggressor_timestamp), exec_id_(exec_id), last_qty_(last_qty), aggressor_side_(aggressor_side), trade_condition_(trade_condition), pad_6_(pad_6), last_px_(last_px), resting_hidden_qty_(resting_hidden_qty) {}

std::int64_t ExecutionSummaryMessage::security_id() const { return security_id_; }
void ExecutionSummaryMessage::set_security_id(std::int64_t value) { security_id_ = value; }

std::optional<std::chrono::nanoseconds> ExecutionSummaryMessage::aggressor_timestamp() const { return aggressor_timestamp_; }
void ExecutionSummaryMessage::set_aggressor_timestamp(std::optional<std::chrono::nanoseconds> value) { aggressor_timestamp_ = value; }

std::chrono::nanoseconds ExecutionSummaryMessage::exec_id() const { return exec_id_; }
void ExecutionSummaryMessage::set_exec_id(std::chrono::nanoseconds value) { exec_id_ = value; }

std::int64_t ExecutionSummaryMessage::last_qty() const { return last_qty_; }
void ExecutionSummaryMessage::set_last_qty(std::int64_t value) { last_qty_ = value; }

AggressorSide ExecutionSummaryMessage::aggressor_side() const { return aggressor_side_; }
void ExecutionSummaryMessage::set_aggressor_side(AggressorSide value) { aggressor_side_ = value; }

std::optional<TradeCondition> ExecutionSummaryMessage::trade_condition() const { return trade_condition_; }
void ExecutionSummaryMessage::set_trade_condition(std::optional<TradeCondition> value) { trade_condition_ = value; }

const std::array<std::byte, 6>& ExecutionSummaryMessage::pad_6() const { return pad_6_; }
std::array<std::byte, 6>& ExecutionSummaryMessage::pad_6() { return pad_6_; }
void ExecutionSummaryMessage::set_pad_6(const std::array<std::byte, 6>& value) { pad_6_ = value; }

Decimal ExecutionSummaryMessage::last_px() const { return last_px_; }
void ExecutionSummaryMessage::set_last_px(Decimal value) { last_px_ = value; }

std::optional<std::int64_t> ExecutionSummaryMessage::resting_hidden_qty() const { return resting_hidden_qty_; }
void ExecutionSummaryMessage::set_resting_hidden_qty(std::optional<std::int64_t> value) { resting_hidden_qty_ = value; }

MessageCode ExecutionSummaryMessage::type() const { return message_type; }

std::string_view ExecutionSummaryMessage::name() const { return "Execution Summary Message"; }

std::size_t ExecutionSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ExecutionSummaryMessage", wire_size, length);

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    aggressor_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    exec_id_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    last_qty_ = wire::read_i64_le(data + offset);
    offset += 8;

    aggressor_side_ = static_cast<AggressorSide>(wire::read_u8(data + offset));
    offset += 1;

    trade_condition_ = wire::nullable_enum<TradeCondition>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::read_bytes(data + offset, pad_6_.data(), 6);
    offset += 6;

    last_px_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    resting_hidden_qty_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    return offset;
}

std::size_t ExecutionSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExecutionSummaryMessage", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, aggressor_timestamp_ ? static_cast<std::uint64_t>(aggressor_timestamp_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(exec_id_.count()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(last_qty_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(aggressor_side_));
    offset += 1;

    wire::write_u8(data + offset, trade_condition_ ? static_cast<std::uint8_t>(*trade_condition_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_bytes(data + offset, pad_6_.data(), 6);
    offset += 6;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(last_px_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, resting_hidden_qty_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    return offset;
}

std::size_t ExecutionSummaryMessage::encoded_size() const {
    return wire_size;
}

void ExecutionSummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExecutionSummaryMessage::clone() const {
    return std::make_unique<ExecutionSummaryMessage>(*this);
}

void ExecutionSummaryMessage::print(std::ostream& out) const {
    out << "ExecutionSummaryMessage{";
    out << "security_id=";
    out << security_id_;
    out << ", aggressor_timestamp=";
    print::optional_duration(out, aggressor_timestamp_);
    out << ", exec_id=";
    out << exec_id_.count();
    out << ", last_qty=";
    out << last_qty_;
    out << ", aggressor_side=";
    out << aggressor_side_;
    out << ", trade_condition=";
    print::optional(out, trade_condition_);
    out << ", pad_6=";
    print::hex(out, pad_6_.data(), pad_6_.size());
    out << ", last_px=";
    out << last_px_;
    out << ", resting_hidden_qty=";
    print::optional(out, resting_hidden_qty_);
    out << '}';
}

bool ExecutionSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExecutionSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ExecutionSummaryMessage::operator==(const ExecutionSummaryMessage& other) const {
    return security_id_ == other.security_id_
        && aggressor_timestamp_ == other.aggressor_timestamp_
        && exec_id_ == other.exec_id_
        && last_qty_ == other.last_qty_
        && aggressor_side_ == other.aggressor_side_
        && trade_condition_ == other.trade_condition_
        && pad_6_ == other.pad_6_
        && last_px_ == other.last_px_
        && resting_hidden_qty_ == other.resting_hidden_qty_;
}

bool ExecutionSummaryMessage::operator!=(const ExecutionSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
