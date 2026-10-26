#include "TradingSessionsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

TradingSessionsGroup::TradingSessionsGroup(std::optional<std::uint16_t> trade_date, std::optional<std::uint16_t> settl_date, std::optional<std::uint16_t> maturity_date, const std::string& security_alt_id)
  : trade_date_(trade_date), settl_date_(settl_date), maturity_date_(maturity_date), security_alt_id_(security_alt_id) {}

std::optional<std::uint16_t> TradingSessionsGroup::trade_date() const { return trade_date_; }
void TradingSessionsGroup::set_trade_date(std::optional<std::uint16_t> value) { trade_date_ = value; }

std::optional<std::uint16_t> TradingSessionsGroup::settl_date() const { return settl_date_; }
void TradingSessionsGroup::set_settl_date(std::optional<std::uint16_t> value) { settl_date_ = value; }

std::optional<std::uint16_t> TradingSessionsGroup::maturity_date() const { return maturity_date_; }
void TradingSessionsGroup::set_maturity_date(std::optional<std::uint16_t> value) { maturity_date_ = value; }

const std::string& TradingSessionsGroup::security_alt_id() const { return security_alt_id_; }
std::string& TradingSessionsGroup::security_alt_id() { return security_alt_id_; }
void TradingSessionsGroup::set_security_alt_id(const std::string& value) { security_alt_id_ = value; }

std::size_t TradingSessionsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradingSessionsGroup", wire_size, length);

    trade_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    settl_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    maturity_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    security_alt_id_ = wire::read_text(data + offset, 12, '\0');
    offset += 12;

    return offset;
}

std::size_t TradingSessionsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingSessionsGroup", wire_size, capacity);

    wire::write_u16_le(data + offset, trade_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_u16_le(data + offset, settl_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_u16_le(data + offset, maturity_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_text(data + offset, 12, '\0', security_alt_id_);
    offset += 12;

    return offset;
}

std::size_t TradingSessionsGroup::encoded_size() const {
    return wire_size;
}

void TradingSessionsGroup::print(std::ostream& out) const {
    out << "TradingSessionsGroup{";
    out << "trade_date=";
    print::optional(out, trade_date_);
    out << ", settl_date=";
    print::optional(out, settl_date_);
    out << ", maturity_date=";
    print::optional(out, maturity_date_);
    out << ", security_alt_id=";
    print::text(out, security_alt_id_);
    out << '}';
}

bool TradingSessionsGroup::operator==(const TradingSessionsGroup& other) const {
    return trade_date_ == other.trade_date_
        && settl_date_ == other.settl_date_
        && maturity_date_ == other.maturity_date_
        && security_alt_id_ == other.security_alt_id_;
}

bool TradingSessionsGroup::operator!=(const TradingSessionsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const TradingSessionsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
