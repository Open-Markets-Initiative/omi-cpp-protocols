#include "TradeReport.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

TradeReport::TradeReport(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> transact_time, std::optional<Decimal> last_qty, std::optional<Decimal> last_px, std::optional<std::uint32_t> trd_match_id, std::optional<MatchType> match_type, std::optional<MatchSubType> match_sub_type, std::optional<AlgorithmicTradeIndicator> algorithmic_trade_indicator, const std::array<std::byte, 1>& pad1, std::optional<TradeCondition> trade_condition, const std::array<std::byte, 6>& pad6)
  : security_id_(security_id), transact_time_(transact_time), last_qty_(last_qty), last_px_(last_px), trd_match_id_(trd_match_id), match_type_(match_type), match_sub_type_(match_sub_type), algorithmic_trade_indicator_(algorithmic_trade_indicator), pad1_(pad1), trade_condition_(trade_condition), pad6_(pad6) {}

std::optional<std::int64_t> TradeReport::security_id() const { return security_id_; }
void TradeReport::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<std::chrono::nanoseconds> TradeReport::transact_time() const { return transact_time_; }
void TradeReport::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

std::optional<Decimal> TradeReport::last_qty() const { return last_qty_; }
void TradeReport::set_last_qty(std::optional<Decimal> value) { last_qty_ = value; }

std::optional<Decimal> TradeReport::last_px() const { return last_px_; }
void TradeReport::set_last_px(std::optional<Decimal> value) { last_px_ = value; }

std::optional<std::uint32_t> TradeReport::trd_match_id() const { return trd_match_id_; }
void TradeReport::set_trd_match_id(std::optional<std::uint32_t> value) { trd_match_id_ = value; }

std::optional<MatchType> TradeReport::match_type() const { return match_type_; }
void TradeReport::set_match_type(std::optional<MatchType> value) { match_type_ = value; }

std::optional<MatchSubType> TradeReport::match_sub_type() const { return match_sub_type_; }
void TradeReport::set_match_sub_type(std::optional<MatchSubType> value) { match_sub_type_ = value; }

std::optional<AlgorithmicTradeIndicator> TradeReport::algorithmic_trade_indicator() const { return algorithmic_trade_indicator_; }
void TradeReport::set_algorithmic_trade_indicator(std::optional<AlgorithmicTradeIndicator> value) { algorithmic_trade_indicator_ = value; }

const std::array<std::byte, 1>& TradeReport::pad1() const { return pad1_; }
std::array<std::byte, 1>& TradeReport::pad1() { return pad1_; }
void TradeReport::set_pad1(const std::array<std::byte, 1>& value) { pad1_ = value; }

std::optional<TradeCondition> TradeReport::trade_condition() const { return trade_condition_; }
void TradeReport::set_trade_condition(std::optional<TradeCondition> value) { trade_condition_ = value; }

const std::array<std::byte, 6>& TradeReport::pad6() const { return pad6_; }
std::array<std::byte, 6>& TradeReport::pad6() { return pad6_; }
void TradeReport::set_pad6(const std::array<std::byte, 6>& value) { pad6_ = value; }

MessageCode TradeReport::type() const { return message_type; }

std::string_view TradeReport::name() const { return "Trade Report"; }

std::size_t TradeReport::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeReport", wire_size, length);

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    last_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -4);
    offset += 8;

    last_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    trd_match_id_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0xFFFFFFFFULL));
    offset += 4;

    match_type_ = wire::nullable_enum<MatchType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    match_sub_type_ = wire::nullable_enum<MatchSubType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    algorithmic_trade_indicator_ = wire::nullable_enum<AlgorithmicTradeIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad1_.data(), 1);
    offset += 1;

    trade_condition_ = wire::nullable_enum<TradeCondition>(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    wire::read_bytes(data + offset, pad6_.data(), 6);
    offset += 6;

    return offset;
}

std::size_t TradeReport::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeReport", wire_size, capacity);

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, last_qty_ ? static_cast<std::int64_t>(last_qty_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, last_px_ ? static_cast<std::int64_t>(last_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_u32_le(data + offset, trd_match_id_.value_or(static_cast<std::uint32_t>(0xFFFFFFFFULL)));
    offset += 4;

    wire::write_u8(data + offset, match_type_ ? static_cast<std::uint8_t>(*match_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, match_sub_type_ ? static_cast<std::uint8_t>(*match_sub_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, algorithmic_trade_indicator_ ? static_cast<std::uint8_t>(*algorithmic_trade_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad1_.data(), 1);
    offset += 1;

    wire::write_u16_le(data + offset, trade_condition_ ? static_cast<std::uint16_t>(*trade_condition_) : static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    wire::write_bytes(data + offset, pad6_.data(), 6);
    offset += 6;

    return offset;
}

std::size_t TradeReport::encoded_size() const {
    return wire_size;
}

void TradeReport::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeReport::clone() const {
    return std::make_unique<TradeReport>(*this);
}

void TradeReport::print(std::ostream& out) const {
    out << "TradeReport{";
    out << "security_id=";
    print::optional(out, security_id_);
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << ", last_qty=";
    print::optional(out, last_qty_);
    out << ", last_px=";
    print::optional(out, last_px_);
    out << ", trd_match_id=";
    print::optional(out, trd_match_id_);
    out << ", match_type=";
    print::optional(out, match_type_);
    out << ", match_sub_type=";
    print::optional(out, match_sub_type_);
    out << ", algorithmic_trade_indicator=";
    print::optional(out, algorithmic_trade_indicator_);
    out << ", pad1=";
    print::hex(out, pad1_.data(), pad1_.size());
    out << ", trade_condition=";
    print::optional(out, trade_condition_);
    out << ", pad6=";
    print::hex(out, pad6_.data(), pad6_.size());
    out << '}';
}

bool TradeReport::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeReport*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeReport::operator==(const TradeReport& other) const {
    return security_id_ == other.security_id_
        && transact_time_ == other.transact_time_
        && last_qty_ == other.last_qty_
        && last_px_ == other.last_px_
        && trd_match_id_ == other.trd_match_id_
        && match_type_ == other.match_type_
        && match_sub_type_ == other.match_sub_type_
        && algorithmic_trade_indicator_ == other.algorithmic_trade_indicator_
        && pad1_ == other.pad1_
        && trade_condition_ == other.trade_condition_
        && pad6_ == other.pad6_;
}

bool TradeReport::operator!=(const TradeReport& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v15_0
