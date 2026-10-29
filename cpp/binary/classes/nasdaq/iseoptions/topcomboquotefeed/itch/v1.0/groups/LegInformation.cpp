#include "LegInformation.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

LegInformation::LegInformation(std::uint32_t option_id, const std::string& security_symbol, std::uint8_t leg_id, std::uint8_t expiration_year, std::uint8_t expiration_month, std::uint8_t expiration_day, Decimal explicit_strike_price, OptionType option_type, Side side, std::uint32_t leg_ratio)
  : option_id_(option_id), security_symbol_(security_symbol), leg_id_(leg_id), expiration_year_(expiration_year), expiration_month_(expiration_month), expiration_day_(expiration_day), explicit_strike_price_(explicit_strike_price), option_type_(option_type), side_(side), leg_ratio_(leg_ratio) {}

std::uint32_t LegInformation::option_id() const { return option_id_; }
void LegInformation::set_option_id(std::uint32_t value) { option_id_ = value; }

const std::string& LegInformation::security_symbol() const { return security_symbol_; }
std::string& LegInformation::security_symbol() { return security_symbol_; }
void LegInformation::set_security_symbol(const std::string& value) { security_symbol_ = value; }

std::uint8_t LegInformation::leg_id() const { return leg_id_; }
void LegInformation::set_leg_id(std::uint8_t value) { leg_id_ = value; }

std::uint8_t LegInformation::expiration_year() const { return expiration_year_; }
void LegInformation::set_expiration_year(std::uint8_t value) { expiration_year_ = value; }

std::uint8_t LegInformation::expiration_month() const { return expiration_month_; }
void LegInformation::set_expiration_month(std::uint8_t value) { expiration_month_ = value; }

std::uint8_t LegInformation::expiration_day() const { return expiration_day_; }
void LegInformation::set_expiration_day(std::uint8_t value) { expiration_day_ = value; }

Decimal LegInformation::explicit_strike_price() const { return explicit_strike_price_; }
void LegInformation::set_explicit_strike_price(Decimal value) { explicit_strike_price_ = value; }

OptionType LegInformation::option_type() const { return option_type_; }
void LegInformation::set_option_type(OptionType value) { option_type_ = value; }

Side LegInformation::side() const { return side_; }
void LegInformation::set_side(Side value) { side_ = value; }

std::uint32_t LegInformation::leg_ratio() const { return leg_ratio_; }
void LegInformation::set_leg_ratio(std::uint32_t value) { leg_ratio_ = value; }

std::size_t LegInformation::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LegInformation", wire_size, length);

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    security_symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    leg_id_ = wire::read_u8(data + offset);
    offset += 1;

    expiration_year_ = wire::read_u8(data + offset);
    offset += 1;

    expiration_month_ = wire::read_u8(data + offset);
    offset += 1;

    expiration_day_ = wire::read_u8(data + offset);
    offset += 1;

    explicit_strike_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -8);
    offset += 8;

    option_type_ = static_cast<OptionType>(wire::read_char(data + offset));
    offset += 1;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    leg_ratio_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t LegInformation::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LegInformation", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', security_symbol_);
    offset += 6;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(leg_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(expiration_year_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(expiration_month_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(expiration_day_));
    offset += 1;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(explicit_strike_price_.mantissa()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(option_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(leg_ratio_));
    offset += 4;

    return offset;
}

std::size_t LegInformation::encoded_size() const {
    return wire_size;
}

void LegInformation::print(std::ostream& out) const {
    out << "LegInformation{";
    out << "option_id=";
    out << option_id_;
    out << ", security_symbol=";
    print::text(out, security_symbol_);
    out << ", leg_id=";
    out << static_cast<int>(leg_id_);
    out << ", expiration_year=";
    out << static_cast<int>(expiration_year_);
    out << ", expiration_month=";
    out << static_cast<int>(expiration_month_);
    out << ", expiration_day=";
    out << static_cast<int>(expiration_day_);
    out << ", explicit_strike_price=";
    out << explicit_strike_price_;
    out << ", option_type=";
    out << option_type_;
    out << ", side=";
    out << side_;
    out << ", leg_ratio=";
    out << leg_ratio_;
    out << '}';
}

bool LegInformation::operator==(const LegInformation& other) const {
    return option_id_ == other.option_id_
        && security_symbol_ == other.security_symbol_
        && leg_id_ == other.leg_id_
        && expiration_year_ == other.expiration_year_
        && expiration_month_ == other.expiration_month_
        && expiration_day_ == other.expiration_day_
        && explicit_strike_price_ == other.explicit_strike_price_
        && option_type_ == other.option_type_
        && side_ == other.side_
        && leg_ratio_ == other.leg_ratio_;
}

bool LegInformation::operator!=(const LegInformation& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const LegInformation& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
