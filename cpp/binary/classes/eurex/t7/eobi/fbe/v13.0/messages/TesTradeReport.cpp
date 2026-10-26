#include "TesTradeReport.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

TesTradeReport::TesTradeReport(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> transact_time, std::optional<Decimal> last_qty, std::optional<Decimal> last_px, std::optional<std::uint32_t> trd_match_id, std::optional<TrdType> trd_type, std::optional<TradeCondition> trade_condition, std::optional<MultiLegReportingType> multi_leg_reporting_type, std::optional<MultiLegPriceModel> multi_leg_price_model, const std::array<std::byte, 6>& pad6, std::optional<Decimal> non_disclosed_trade_volume, std::optional<std::chrono::nanoseconds> trans_bkd_time, std::optional<std::uint16_t> number_of_buy_sides, std::optional<std::uint16_t> number_of_sell_sides, const std::array<std::byte, 4>& pad4)
  : security_id_(security_id), transact_time_(transact_time), last_qty_(last_qty), last_px_(last_px), trd_match_id_(trd_match_id), trd_type_(trd_type), trade_condition_(trade_condition), multi_leg_reporting_type_(multi_leg_reporting_type), multi_leg_price_model_(multi_leg_price_model), pad6_(pad6), non_disclosed_trade_volume_(non_disclosed_trade_volume), trans_bkd_time_(trans_bkd_time), number_of_buy_sides_(number_of_buy_sides), number_of_sell_sides_(number_of_sell_sides), pad4_(pad4) {}

std::optional<std::int64_t> TesTradeReport::security_id() const { return security_id_; }
void TesTradeReport::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<std::chrono::nanoseconds> TesTradeReport::transact_time() const { return transact_time_; }
void TesTradeReport::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

std::optional<Decimal> TesTradeReport::last_qty() const { return last_qty_; }
void TesTradeReport::set_last_qty(std::optional<Decimal> value) { last_qty_ = value; }

std::optional<Decimal> TesTradeReport::last_px() const { return last_px_; }
void TesTradeReport::set_last_px(std::optional<Decimal> value) { last_px_ = value; }

std::optional<std::uint32_t> TesTradeReport::trd_match_id() const { return trd_match_id_; }
void TesTradeReport::set_trd_match_id(std::optional<std::uint32_t> value) { trd_match_id_ = value; }

std::optional<TrdType> TesTradeReport::trd_type() const { return trd_type_; }
void TesTradeReport::set_trd_type(std::optional<TrdType> value) { trd_type_ = value; }

std::optional<TradeCondition> TesTradeReport::trade_condition() const { return trade_condition_; }
void TesTradeReport::set_trade_condition(std::optional<TradeCondition> value) { trade_condition_ = value; }

std::optional<MultiLegReportingType> TesTradeReport::multi_leg_reporting_type() const { return multi_leg_reporting_type_; }
void TesTradeReport::set_multi_leg_reporting_type(std::optional<MultiLegReportingType> value) { multi_leg_reporting_type_ = value; }

std::optional<MultiLegPriceModel> TesTradeReport::multi_leg_price_model() const { return multi_leg_price_model_; }
void TesTradeReport::set_multi_leg_price_model(std::optional<MultiLegPriceModel> value) { multi_leg_price_model_ = value; }

const std::array<std::byte, 6>& TesTradeReport::pad6() const { return pad6_; }
std::array<std::byte, 6>& TesTradeReport::pad6() { return pad6_; }
void TesTradeReport::set_pad6(const std::array<std::byte, 6>& value) { pad6_ = value; }

std::optional<Decimal> TesTradeReport::non_disclosed_trade_volume() const { return non_disclosed_trade_volume_; }
void TesTradeReport::set_non_disclosed_trade_volume(std::optional<Decimal> value) { non_disclosed_trade_volume_ = value; }

std::optional<std::chrono::nanoseconds> TesTradeReport::trans_bkd_time() const { return trans_bkd_time_; }
void TesTradeReport::set_trans_bkd_time(std::optional<std::chrono::nanoseconds> value) { trans_bkd_time_ = value; }

std::optional<std::uint16_t> TesTradeReport::number_of_buy_sides() const { return number_of_buy_sides_; }
void TesTradeReport::set_number_of_buy_sides(std::optional<std::uint16_t> value) { number_of_buy_sides_ = value; }

std::optional<std::uint16_t> TesTradeReport::number_of_sell_sides() const { return number_of_sell_sides_; }
void TesTradeReport::set_number_of_sell_sides(std::optional<std::uint16_t> value) { number_of_sell_sides_ = value; }

const std::array<std::byte, 4>& TesTradeReport::pad4() const { return pad4_; }
std::array<std::byte, 4>& TesTradeReport::pad4() { return pad4_; }
void TesTradeReport::set_pad4(const std::array<std::byte, 4>& value) { pad4_ = value; }

MessageCode TesTradeReport::type() const { return message_type; }

std::string_view TesTradeReport::name() const { return "Tes Trade Report"; }

std::size_t TesTradeReport::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TesTradeReport", wire_size, length);

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

    trd_type_ = wire::nullable_enum<TrdType>(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    trade_condition_ = wire::nullable_enum<TradeCondition>(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    multi_leg_reporting_type_ = wire::nullable_enum<MultiLegReportingType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    multi_leg_price_model_ = wire::nullable_enum<MultiLegPriceModel>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad6_.data(), 6);
    offset += 6;

    non_disclosed_trade_volume_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -4);
    offset += 8;

    trans_bkd_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    number_of_buy_sides_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    number_of_sell_sides_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    wire::read_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t TesTradeReport::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TesTradeReport", wire_size, capacity);

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

    wire::write_u16_le(data + offset, trd_type_ ? static_cast<std::uint16_t>(*trd_type_) : static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    wire::write_u16_le(data + offset, trade_condition_ ? static_cast<std::uint16_t>(*trade_condition_) : static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    wire::write_u8(data + offset, multi_leg_reporting_type_ ? static_cast<std::uint8_t>(*multi_leg_reporting_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, multi_leg_price_model_ ? static_cast<std::uint8_t>(*multi_leg_price_model_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad6_.data(), 6);
    offset += 6;

    wire::write_i64_le(data + offset, non_disclosed_trade_volume_ ? static_cast<std::int64_t>(non_disclosed_trade_volume_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_u64_le(data + offset, trans_bkd_time_ ? static_cast<std::uint64_t>(trans_bkd_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u16_le(data + offset, number_of_buy_sides_.value_or(static_cast<std::uint16_t>(0xFFFFULL)));
    offset += 2;

    wire::write_u16_le(data + offset, number_of_sell_sides_.value_or(static_cast<std::uint16_t>(0xFFFFULL)));
    offset += 2;

    wire::write_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t TesTradeReport::encoded_size() const {
    return wire_size;
}

void TesTradeReport::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TesTradeReport::clone() const {
    return std::make_unique<TesTradeReport>(*this);
}

void TesTradeReport::print(std::ostream& out) const {
    out << "TesTradeReport{";
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
    out << ", trd_type=";
    print::optional(out, trd_type_);
    out << ", trade_condition=";
    print::optional(out, trade_condition_);
    out << ", multi_leg_reporting_type=";
    print::optional(out, multi_leg_reporting_type_);
    out << ", multi_leg_price_model=";
    print::optional(out, multi_leg_price_model_);
    out << ", pad6=";
    print::hex(out, pad6_.data(), pad6_.size());
    out << ", non_disclosed_trade_volume=";
    print::optional(out, non_disclosed_trade_volume_);
    out << ", trans_bkd_time=";
    print::optional_duration(out, trans_bkd_time_);
    out << ", number_of_buy_sides=";
    print::optional(out, number_of_buy_sides_);
    out << ", number_of_sell_sides=";
    print::optional(out, number_of_sell_sides_);
    out << ", pad4=";
    print::hex(out, pad4_.data(), pad4_.size());
    out << '}';
}

bool TesTradeReport::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TesTradeReport*>(&other);
    return that != nullptr && *this == *that;
}

bool TesTradeReport::operator==(const TesTradeReport& other) const {
    return security_id_ == other.security_id_
        && transact_time_ == other.transact_time_
        && last_qty_ == other.last_qty_
        && last_px_ == other.last_px_
        && trd_match_id_ == other.trd_match_id_
        && trd_type_ == other.trd_type_
        && trade_condition_ == other.trade_condition_
        && multi_leg_reporting_type_ == other.multi_leg_reporting_type_
        && multi_leg_price_model_ == other.multi_leg_price_model_
        && pad6_ == other.pad6_
        && non_disclosed_trade_volume_ == other.non_disclosed_trade_volume_
        && trans_bkd_time_ == other.trans_bkd_time_
        && number_of_buy_sides_ == other.number_of_buy_sides_
        && number_of_sell_sides_ == other.number_of_sell_sides_
        && pad4_ == other.pad4_;
}

bool TesTradeReport::operator!=(const TesTradeReport& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v13_0
