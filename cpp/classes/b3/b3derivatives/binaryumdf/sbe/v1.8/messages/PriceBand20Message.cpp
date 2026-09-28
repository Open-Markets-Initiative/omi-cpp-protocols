#include "PriceBand20Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

PriceBand20Message::PriceBand20Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, std::optional<PriceBandType> price_band_type, std::optional<PriceLimitType> price_limit_type, std::optional<PriceBandMidpointPriceType> price_band_midpoint_price_type, std::optional<Decimal> low_limit_price, std::optional<Decimal> high_limit_price, std::optional<Decimal> trading_reference_price_legacy, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), price_band_type_(price_band_type), price_limit_type_(price_limit_type), price_band_midpoint_price_type_(price_band_midpoint_price_type), low_limit_price_(low_limit_price), high_limit_price_(high_limit_price), trading_reference_price_legacy_(trading_reference_price_legacy), md_entry_timestamp_(md_entry_timestamp), rpt_seq_(rpt_seq) {}

std::uint64_t PriceBand20Message::security_id() const { return security_id_; }
void PriceBand20Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& PriceBand20Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& PriceBand20Message::match_event_indicator() { return match_event_indicator_; }
void PriceBand20Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

std::optional<PriceBandType> PriceBand20Message::price_band_type() const { return price_band_type_; }
void PriceBand20Message::set_price_band_type(std::optional<PriceBandType> value) { price_band_type_ = value; }

std::optional<PriceLimitType> PriceBand20Message::price_limit_type() const { return price_limit_type_; }
void PriceBand20Message::set_price_limit_type(std::optional<PriceLimitType> value) { price_limit_type_ = value; }

std::optional<PriceBandMidpointPriceType> PriceBand20Message::price_band_midpoint_price_type() const { return price_band_midpoint_price_type_; }
void PriceBand20Message::set_price_band_midpoint_price_type(std::optional<PriceBandMidpointPriceType> value) { price_band_midpoint_price_type_ = value; }

std::optional<Decimal> PriceBand20Message::low_limit_price() const { return low_limit_price_; }
void PriceBand20Message::set_low_limit_price(std::optional<Decimal> value) { low_limit_price_ = value; }

std::optional<Decimal> PriceBand20Message::high_limit_price() const { return high_limit_price_; }
void PriceBand20Message::set_high_limit_price(std::optional<Decimal> value) { high_limit_price_ = value; }

std::optional<Decimal> PriceBand20Message::trading_reference_price_legacy() const { return trading_reference_price_legacy_; }
void PriceBand20Message::set_trading_reference_price_legacy(std::optional<Decimal> value) { trading_reference_price_legacy_ = value; }

std::optional<std::chrono::nanoseconds> PriceBand20Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void PriceBand20Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

std::optional<std::uint32_t> PriceBand20Message::rpt_seq() const { return rpt_seq_; }
void PriceBand20Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

MessageCode PriceBand20Message::type() const { return message_type; }

std::string_view PriceBand20Message::name() const { return "Price Band 20 Message"; }

std::size_t PriceBand20Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PriceBand20Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    price_band_type_ = wire::nullable_enum<PriceBandType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    price_limit_type_ = wire::nullable_enum<PriceLimitType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    price_band_midpoint_price_type_ = wire::nullable_enum<PriceBandMidpointPriceType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    low_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    high_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    trading_reference_price_legacy_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t PriceBand20Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PriceBand20Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, price_band_type_ ? static_cast<std::uint8_t>(*price_band_type_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, price_limit_type_ ? static_cast<std::uint8_t>(*price_limit_type_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, price_band_midpoint_price_type_ ? static_cast<std::uint8_t>(*price_band_midpoint_price_type_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_i64_le(data + offset, low_limit_price_ ? static_cast<std::int64_t>(low_limit_price_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_i64_le(data + offset, high_limit_price_ ? static_cast<std::int64_t>(high_limit_price_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_i64_le(data + offset, trading_reference_price_legacy_ ? static_cast<std::int64_t>(trading_reference_price_legacy_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t PriceBand20Message::encoded_size() const {
    return wire_size;
}

void PriceBand20Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> PriceBand20Message::clone() const {
    return std::make_unique<PriceBand20Message>(*this);
}

void PriceBand20Message::print(std::ostream& out) const {
    out << "PriceBand20Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", price_band_type=";
    print::optional(out, price_band_type_);
    out << ", price_limit_type=";
    print::optional(out, price_limit_type_);
    out << ", price_band_midpoint_price_type=";
    print::optional(out, price_band_midpoint_price_type_);
    out << ", low_limit_price=";
    print::optional(out, low_limit_price_);
    out << ", high_limit_price=";
    print::optional(out, high_limit_price_);
    out << ", trading_reference_price_legacy=";
    print::optional(out, trading_reference_price_legacy_);
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << '}';
}

bool PriceBand20Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const PriceBand20Message*>(&other);
    return that != nullptr && *this == *that;
}

bool PriceBand20Message::operator==(const PriceBand20Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && price_band_type_ == other.price_band_type_
        && price_limit_type_ == other.price_limit_type_
        && price_band_midpoint_price_type_ == other.price_band_midpoint_price_type_
        && low_limit_price_ == other.low_limit_price_
        && high_limit_price_ == other.high_limit_price_
        && trading_reference_price_legacy_ == other.trading_reference_price_legacy_
        && md_entry_timestamp_ == other.md_entry_timestamp_
        && rpt_seq_ == other.rpt_seq_;
}

bool PriceBand20Message::operator!=(const PriceBand20Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
