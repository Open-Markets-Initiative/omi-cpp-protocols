#include "RepoUnderlyingsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

RepoUnderlyingsGroup::RepoUnderlyingsGroup(const std::string& underlying_symbol, std::optional<std::int32_t> underlying_security_id_optional, const std::string& underlying_security_alt_id, std::optional<UnderlyingSecurityAltIdSource> underlying_security_alt_id_source, const std::string& underlying_financial_instrument_full_name, const std::string& underlying_security_type, const std::string& underlying_country_of_issue, const std::string& underlying_issuer, std::optional<std::uint8_t> underlying_max_life_time, std::optional<std::uint16_t> underlying_min_days_to_maturity, std::optional<std::uint64_t> underlying_instrument_guid_optional, std::optional<std::uint16_t> underlying_maturity_date)
  : underlying_symbol_(underlying_symbol), underlying_security_id_optional_(underlying_security_id_optional), underlying_security_alt_id_(underlying_security_alt_id), underlying_security_alt_id_source_(underlying_security_alt_id_source), underlying_financial_instrument_full_name_(underlying_financial_instrument_full_name), underlying_security_type_(underlying_security_type), underlying_country_of_issue_(underlying_country_of_issue), underlying_issuer_(underlying_issuer), underlying_max_life_time_(underlying_max_life_time), underlying_min_days_to_maturity_(underlying_min_days_to_maturity), underlying_instrument_guid_optional_(underlying_instrument_guid_optional), underlying_maturity_date_(underlying_maturity_date) {}

const std::string& RepoUnderlyingsGroup::underlying_symbol() const { return underlying_symbol_; }
std::string& RepoUnderlyingsGroup::underlying_symbol() { return underlying_symbol_; }
void RepoUnderlyingsGroup::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

std::optional<std::int32_t> RepoUnderlyingsGroup::underlying_security_id_optional() const { return underlying_security_id_optional_; }
void RepoUnderlyingsGroup::set_underlying_security_id_optional(std::optional<std::int32_t> value) { underlying_security_id_optional_ = value; }

const std::string& RepoUnderlyingsGroup::underlying_security_alt_id() const { return underlying_security_alt_id_; }
std::string& RepoUnderlyingsGroup::underlying_security_alt_id() { return underlying_security_alt_id_; }
void RepoUnderlyingsGroup::set_underlying_security_alt_id(const std::string& value) { underlying_security_alt_id_ = value; }

std::optional<UnderlyingSecurityAltIdSource> RepoUnderlyingsGroup::underlying_security_alt_id_source() const { return underlying_security_alt_id_source_; }
void RepoUnderlyingsGroup::set_underlying_security_alt_id_source(std::optional<UnderlyingSecurityAltIdSource> value) { underlying_security_alt_id_source_ = value; }

const std::string& RepoUnderlyingsGroup::underlying_financial_instrument_full_name() const { return underlying_financial_instrument_full_name_; }
std::string& RepoUnderlyingsGroup::underlying_financial_instrument_full_name() { return underlying_financial_instrument_full_name_; }
void RepoUnderlyingsGroup::set_underlying_financial_instrument_full_name(const std::string& value) { underlying_financial_instrument_full_name_ = value; }

const std::string& RepoUnderlyingsGroup::underlying_security_type() const { return underlying_security_type_; }
std::string& RepoUnderlyingsGroup::underlying_security_type() { return underlying_security_type_; }
void RepoUnderlyingsGroup::set_underlying_security_type(const std::string& value) { underlying_security_type_ = value; }

const std::string& RepoUnderlyingsGroup::underlying_country_of_issue() const { return underlying_country_of_issue_; }
std::string& RepoUnderlyingsGroup::underlying_country_of_issue() { return underlying_country_of_issue_; }
void RepoUnderlyingsGroup::set_underlying_country_of_issue(const std::string& value) { underlying_country_of_issue_ = value; }

const std::string& RepoUnderlyingsGroup::underlying_issuer() const { return underlying_issuer_; }
std::string& RepoUnderlyingsGroup::underlying_issuer() { return underlying_issuer_; }
void RepoUnderlyingsGroup::set_underlying_issuer(const std::string& value) { underlying_issuer_ = value; }

std::optional<std::uint8_t> RepoUnderlyingsGroup::underlying_max_life_time() const { return underlying_max_life_time_; }
void RepoUnderlyingsGroup::set_underlying_max_life_time(std::optional<std::uint8_t> value) { underlying_max_life_time_ = value; }

std::optional<std::uint16_t> RepoUnderlyingsGroup::underlying_min_days_to_maturity() const { return underlying_min_days_to_maturity_; }
void RepoUnderlyingsGroup::set_underlying_min_days_to_maturity(std::optional<std::uint16_t> value) { underlying_min_days_to_maturity_ = value; }

std::optional<std::uint64_t> RepoUnderlyingsGroup::underlying_instrument_guid_optional() const { return underlying_instrument_guid_optional_; }
void RepoUnderlyingsGroup::set_underlying_instrument_guid_optional(std::optional<std::uint64_t> value) { underlying_instrument_guid_optional_ = value; }

std::optional<std::uint16_t> RepoUnderlyingsGroup::underlying_maturity_date() const { return underlying_maturity_date_; }
void RepoUnderlyingsGroup::set_underlying_maturity_date(std::optional<std::uint16_t> value) { underlying_maturity_date_ = value; }

std::size_t RepoUnderlyingsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RepoUnderlyingsGroup", wire_size, length);

    underlying_symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    underlying_security_id_optional_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    underlying_security_alt_id_ = wire::read_text(data + offset, 12, '\0');
    offset += 12;

    underlying_security_alt_id_source_ = wire::nullable_enum<UnderlyingSecurityAltIdSource>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    underlying_financial_instrument_full_name_ = wire::read_text(data + offset, 35, '\0');
    offset += 35;

    underlying_security_type_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    underlying_country_of_issue_ = wire::read_text(data + offset, 2, '\0');
    offset += 2;

    underlying_issuer_ = wire::read_text(data + offset, 25, '\0');
    offset += 25;

    underlying_max_life_time_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    underlying_min_days_to_maturity_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    underlying_instrument_guid_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    underlying_maturity_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    return offset;
}

std::size_t RepoUnderlyingsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RepoUnderlyingsGroup", wire_size, capacity);

    wire::write_text(data + offset, 20, '\0', underlying_symbol_);
    offset += 20;

    wire::write_i32_le(data + offset, underlying_security_id_optional_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_text(data + offset, 12, '\0', underlying_security_alt_id_);
    offset += 12;

    wire::write_u8(data + offset, underlying_security_alt_id_source_ ? static_cast<std::uint8_t>(*underlying_security_alt_id_source_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_text(data + offset, 35, '\0', underlying_financial_instrument_full_name_);
    offset += 35;

    wire::write_text(data + offset, 6, '\0', underlying_security_type_);
    offset += 6;

    wire::write_text(data + offset, 2, '\0', underlying_country_of_issue_);
    offset += 2;

    wire::write_text(data + offset, 25, '\0', underlying_issuer_);
    offset += 25;

    wire::write_u8(data + offset, underlying_max_life_time_.value_or(static_cast<std::uint8_t>(255ULL)));
    offset += 1;

    wire::write_u16_le(data + offset, underlying_min_days_to_maturity_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_u64_le(data + offset, underlying_instrument_guid_optional_.value_or(static_cast<std::uint64_t>(18446744073709551615ULL)));
    offset += 8;

    wire::write_u16_le(data + offset, underlying_maturity_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    return offset;
}

std::size_t RepoUnderlyingsGroup::encoded_size() const {
    return wire_size;
}

void RepoUnderlyingsGroup::print(std::ostream& out) const {
    out << "RepoUnderlyingsGroup{";
    out << "underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << ", underlying_security_id_optional=";
    print::optional(out, underlying_security_id_optional_);
    out << ", underlying_security_alt_id=";
    print::text(out, underlying_security_alt_id_);
    out << ", underlying_security_alt_id_source=";
    print::optional(out, underlying_security_alt_id_source_);
    out << ", underlying_financial_instrument_full_name=";
    print::text(out, underlying_financial_instrument_full_name_);
    out << ", underlying_security_type=";
    print::text(out, underlying_security_type_);
    out << ", underlying_country_of_issue=";
    print::text(out, underlying_country_of_issue_);
    out << ", underlying_issuer=";
    print::text(out, underlying_issuer_);
    out << ", underlying_max_life_time=";
    print::optional(out, underlying_max_life_time_);
    out << ", underlying_min_days_to_maturity=";
    print::optional(out, underlying_min_days_to_maturity_);
    out << ", underlying_instrument_guid_optional=";
    print::optional(out, underlying_instrument_guid_optional_);
    out << ", underlying_maturity_date=";
    print::optional(out, underlying_maturity_date_);
    out << '}';
}

bool RepoUnderlyingsGroup::operator==(const RepoUnderlyingsGroup& other) const {
    return underlying_symbol_ == other.underlying_symbol_
        && underlying_security_id_optional_ == other.underlying_security_id_optional_
        && underlying_security_alt_id_ == other.underlying_security_alt_id_
        && underlying_security_alt_id_source_ == other.underlying_security_alt_id_source_
        && underlying_financial_instrument_full_name_ == other.underlying_financial_instrument_full_name_
        && underlying_security_type_ == other.underlying_security_type_
        && underlying_country_of_issue_ == other.underlying_country_of_issue_
        && underlying_issuer_ == other.underlying_issuer_
        && underlying_max_life_time_ == other.underlying_max_life_time_
        && underlying_min_days_to_maturity_ == other.underlying_min_days_to_maturity_
        && underlying_instrument_guid_optional_ == other.underlying_instrument_guid_optional_
        && underlying_maturity_date_ == other.underlying_maturity_date_;
}

bool RepoUnderlyingsGroup::operator!=(const RepoUnderlyingsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RepoUnderlyingsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
