#include "ExtendedSecurityNoCusipMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

ExtendedSecurityNoCusipMessage::ExtendedSecurityNoCusipMessage(std::uint32_t channel_seq_num, const std::string& symbol, std::uint64_t last_update_milli, SecurityAction security_action, std::uint32_t otc_issuer_id, const std::string& security_desc, const std::string& short_name, AssetClass asset_class, const std::string& security_type, const std::string& primary_market, std::uint32_t security_id, const SecurityFlags& security_flags, Tier tier, ReportingStatus reporting_status, DisclosureStatus disclosure_status, SecurityStatus security_status, Decimal par_value, Decimal coupon, std::uint64_t maturity_date_milli, std::uint64_t callable_date_milli, Decimal adr_ratio, const std::string& adr_level, const SecurityDetail& security_detail, const Issuer& issuer)
  : channel_seq_num_(channel_seq_num), symbol_(symbol), last_update_milli_(last_update_milli), security_action_(security_action), otc_issuer_id_(otc_issuer_id), security_desc_(security_desc), short_name_(short_name), asset_class_(asset_class), security_type_(security_type), primary_market_(primary_market), security_id_(security_id), security_flags_(security_flags), tier_(tier), reporting_status_(reporting_status), disclosure_status_(disclosure_status), security_status_(security_status), par_value_(par_value), coupon_(coupon), maturity_date_milli_(maturity_date_milli), callable_date_milli_(callable_date_milli), adr_ratio_(adr_ratio), adr_level_(adr_level), security_detail_(security_detail), issuer_(issuer) {}

std::uint32_t ExtendedSecurityNoCusipMessage::channel_seq_num() const { return channel_seq_num_; }
void ExtendedSecurityNoCusipMessage::set_channel_seq_num(std::uint32_t value) { channel_seq_num_ = value; }

const std::string& ExtendedSecurityNoCusipMessage::symbol() const { return symbol_; }
std::string& ExtendedSecurityNoCusipMessage::symbol() { return symbol_; }
void ExtendedSecurityNoCusipMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint64_t ExtendedSecurityNoCusipMessage::last_update_milli() const { return last_update_milli_; }
void ExtendedSecurityNoCusipMessage::set_last_update_milli(std::uint64_t value) { last_update_milli_ = value; }

SecurityAction ExtendedSecurityNoCusipMessage::security_action() const { return security_action_; }
void ExtendedSecurityNoCusipMessage::set_security_action(SecurityAction value) { security_action_ = value; }

std::uint32_t ExtendedSecurityNoCusipMessage::otc_issuer_id() const { return otc_issuer_id_; }
void ExtendedSecurityNoCusipMessage::set_otc_issuer_id(std::uint32_t value) { otc_issuer_id_ = value; }

const std::string& ExtendedSecurityNoCusipMessage::security_desc() const { return security_desc_; }
std::string& ExtendedSecurityNoCusipMessage::security_desc() { return security_desc_; }
void ExtendedSecurityNoCusipMessage::set_security_desc(const std::string& value) { security_desc_ = value; }

const std::string& ExtendedSecurityNoCusipMessage::short_name() const { return short_name_; }
std::string& ExtendedSecurityNoCusipMessage::short_name() { return short_name_; }
void ExtendedSecurityNoCusipMessage::set_short_name(const std::string& value) { short_name_ = value; }

AssetClass ExtendedSecurityNoCusipMessage::asset_class() const { return asset_class_; }
void ExtendedSecurityNoCusipMessage::set_asset_class(AssetClass value) { asset_class_ = value; }

const std::string& ExtendedSecurityNoCusipMessage::security_type() const { return security_type_; }
std::string& ExtendedSecurityNoCusipMessage::security_type() { return security_type_; }
void ExtendedSecurityNoCusipMessage::set_security_type(const std::string& value) { security_type_ = value; }

const std::string& ExtendedSecurityNoCusipMessage::primary_market() const { return primary_market_; }
std::string& ExtendedSecurityNoCusipMessage::primary_market() { return primary_market_; }
void ExtendedSecurityNoCusipMessage::set_primary_market(const std::string& value) { primary_market_ = value; }

std::uint32_t ExtendedSecurityNoCusipMessage::security_id() const { return security_id_; }
void ExtendedSecurityNoCusipMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

const SecurityFlags& ExtendedSecurityNoCusipMessage::security_flags() const { return security_flags_; }
SecurityFlags& ExtendedSecurityNoCusipMessage::security_flags() { return security_flags_; }
void ExtendedSecurityNoCusipMessage::set_security_flags(const SecurityFlags& value) { security_flags_ = value; }

Tier ExtendedSecurityNoCusipMessage::tier() const { return tier_; }
void ExtendedSecurityNoCusipMessage::set_tier(Tier value) { tier_ = value; }

ReportingStatus ExtendedSecurityNoCusipMessage::reporting_status() const { return reporting_status_; }
void ExtendedSecurityNoCusipMessage::set_reporting_status(ReportingStatus value) { reporting_status_ = value; }

DisclosureStatus ExtendedSecurityNoCusipMessage::disclosure_status() const { return disclosure_status_; }
void ExtendedSecurityNoCusipMessage::set_disclosure_status(DisclosureStatus value) { disclosure_status_ = value; }

SecurityStatus ExtendedSecurityNoCusipMessage::security_status() const { return security_status_; }
void ExtendedSecurityNoCusipMessage::set_security_status(SecurityStatus value) { security_status_ = value; }

Decimal ExtendedSecurityNoCusipMessage::par_value() const { return par_value_; }
void ExtendedSecurityNoCusipMessage::set_par_value(Decimal value) { par_value_ = value; }

Decimal ExtendedSecurityNoCusipMessage::coupon() const { return coupon_; }
void ExtendedSecurityNoCusipMessage::set_coupon(Decimal value) { coupon_ = value; }

std::uint64_t ExtendedSecurityNoCusipMessage::maturity_date_milli() const { return maturity_date_milli_; }
void ExtendedSecurityNoCusipMessage::set_maturity_date_milli(std::uint64_t value) { maturity_date_milli_ = value; }

std::uint64_t ExtendedSecurityNoCusipMessage::callable_date_milli() const { return callable_date_milli_; }
void ExtendedSecurityNoCusipMessage::set_callable_date_milli(std::uint64_t value) { callable_date_milli_ = value; }

Decimal ExtendedSecurityNoCusipMessage::adr_ratio() const { return adr_ratio_; }
void ExtendedSecurityNoCusipMessage::set_adr_ratio(Decimal value) { adr_ratio_ = value; }

const std::string& ExtendedSecurityNoCusipMessage::adr_level() const { return adr_level_; }
std::string& ExtendedSecurityNoCusipMessage::adr_level() { return adr_level_; }
void ExtendedSecurityNoCusipMessage::set_adr_level(const std::string& value) { adr_level_ = value; }

const SecurityDetail& ExtendedSecurityNoCusipMessage::security_detail() const { return security_detail_; }
SecurityDetail& ExtendedSecurityNoCusipMessage::security_detail() { return security_detail_; }
void ExtendedSecurityNoCusipMessage::set_security_detail(const SecurityDetail& value) { security_detail_ = value; }

const Issuer& ExtendedSecurityNoCusipMessage::issuer() const { return issuer_; }
Issuer& ExtendedSecurityNoCusipMessage::issuer() { return issuer_; }
void ExtendedSecurityNoCusipMessage::set_issuer(const Issuer& value) { issuer_ = value; }

MessageCode ExtendedSecurityNoCusipMessage::type() const { return message_type; }

std::string_view ExtendedSecurityNoCusipMessage::name() const { return "Extended Security No Cusip Message"; }

std::size_t ExtendedSecurityNoCusipMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 4, length);
    channel_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 10, length);
    symbol_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 8, length);
    last_update_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 1, length);
    security_action_ = static_cast<SecurityAction>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 4, length);
    otc_issuer_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 25, length);
    security_desc_ = wire::read_text(data + offset, 25, ' ');
    offset += 25;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 25, length);
    short_name_ = wire::read_text(data + offset, 25, ' ');
    offset += 25;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 1, length);
    asset_class_ = static_cast<AssetClass>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 5, length);
    security_type_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 3, length);
    primary_market_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 4, length);
    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += security_flags_.decode(data + offset, length - offset);

    wire::require("ExtendedSecurityNoCusipMessage", offset + 1, length);
    tier_ = static_cast<Tier>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 1, length);
    reporting_status_ = static_cast<ReportingStatus>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 1, length);
    disclosure_status_ = static_cast<DisclosureStatus>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 1, length);
    security_status_ = static_cast<SecurityStatus>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 8, length);
    par_value_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 8, length);
    coupon_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 8, length);
    maturity_date_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 8, length);
    callable_date_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 8, length);
    adr_ratio_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    wire::require("ExtendedSecurityNoCusipMessage", offset + 15, length);
    adr_level_ = wire::read_text(data + offset, 15, ' ');
    offset += 15;

    offset += security_detail_.decode(data + offset, length - offset);

    offset += issuer_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ExtendedSecurityNoCusipMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExtendedSecurityNoCusipMessage", encoded_size(), capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(channel_seq_num_));
    offset += 4;

    wire::write_text(data + offset, 10, ' ', symbol_);
    offset += 10;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(last_update_milli_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_action_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(otc_issuer_id_));
    offset += 4;

    wire::write_text(data + offset, 25, ' ', security_desc_);
    offset += 25;

    wire::write_text(data + offset, 25, ' ', short_name_);
    offset += 25;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(asset_class_));
    offset += 1;

    wire::write_text(data + offset, 5, ' ', security_type_);
    offset += 5;

    wire::write_text(data + offset, 3, ' ', primary_market_);
    offset += 3;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(security_id_));
    offset += 4;

    offset += security_flags_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(tier_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(reporting_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(disclosure_status_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(security_status_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(par_value_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(coupon_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(maturity_date_milli_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(callable_date_milli_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(adr_ratio_.mantissa()));
    offset += 8;

    wire::write_text(data + offset, 15, ' ', adr_level_);
    offset += 15;

    offset += security_detail_.encode(data + offset, capacity - offset);

    offset += issuer_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ExtendedSecurityNoCusipMessage::encoded_size() const {
    return 4 + 10 + 8 + 1 + 4 + 25 + 25 + 1 + 5 + 3 + 4 + security_flags_.encoded_size() + 1 + 1 + 1 + 1 + 8 + 8 + 8 + 8 + 8 + 15 + security_detail_.encoded_size() + issuer_.encoded_size();
}

void ExtendedSecurityNoCusipMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExtendedSecurityNoCusipMessage::clone() const {
    return std::make_unique<ExtendedSecurityNoCusipMessage>(*this);
}

void ExtendedSecurityNoCusipMessage::print(std::ostream& out) const {
    out << "ExtendedSecurityNoCusipMessage{";
    out << "channel_seq_num=";
    out << channel_seq_num_;
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", last_update_milli=";
    out << last_update_milli_;
    out << ", security_action=";
    out << security_action_;
    out << ", otc_issuer_id=";
    out << otc_issuer_id_;
    out << ", security_desc=";
    print::text(out, security_desc_);
    out << ", short_name=";
    print::text(out, short_name_);
    out << ", asset_class=";
    out << asset_class_;
    out << ", security_type=";
    print::text(out, security_type_);
    out << ", primary_market=";
    print::text(out, primary_market_);
    out << ", security_id=";
    out << security_id_;
    out << ", security_flags=";
    security_flags_.print(out);
    out << ", tier=";
    out << tier_;
    out << ", reporting_status=";
    out << reporting_status_;
    out << ", disclosure_status=";
    out << disclosure_status_;
    out << ", security_status=";
    out << security_status_;
    out << ", par_value=";
    out << par_value_;
    out << ", coupon=";
    out << coupon_;
    out << ", maturity_date_milli=";
    out << maturity_date_milli_;
    out << ", callable_date_milli=";
    out << callable_date_milli_;
    out << ", adr_ratio=";
    out << adr_ratio_;
    out << ", adr_level=";
    print::text(out, adr_level_);
    out << ", security_detail=";
    security_detail_.print(out);
    out << ", issuer=";
    issuer_.print(out);
    out << '}';
}

bool ExtendedSecurityNoCusipMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExtendedSecurityNoCusipMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ExtendedSecurityNoCusipMessage::operator==(const ExtendedSecurityNoCusipMessage& other) const {
    return channel_seq_num_ == other.channel_seq_num_
        && symbol_ == other.symbol_
        && last_update_milli_ == other.last_update_milli_
        && security_action_ == other.security_action_
        && otc_issuer_id_ == other.otc_issuer_id_
        && security_desc_ == other.security_desc_
        && short_name_ == other.short_name_
        && asset_class_ == other.asset_class_
        && security_type_ == other.security_type_
        && primary_market_ == other.primary_market_
        && security_id_ == other.security_id_
        && security_flags_ == other.security_flags_
        && tier_ == other.tier_
        && reporting_status_ == other.reporting_status_
        && disclosure_status_ == other.disclosure_status_
        && security_status_ == other.security_status_
        && par_value_ == other.par_value_
        && coupon_ == other.coupon_
        && maturity_date_milli_ == other.maturity_date_milli_
        && callable_date_milli_ == other.callable_date_milli_
        && adr_ratio_ == other.adr_ratio_
        && adr_level_ == other.adr_level_
        && security_detail_ == other.security_detail_
        && issuer_ == other.issuer_;
}

bool ExtendedSecurityNoCusipMessage::operator!=(const ExtendedSecurityNoCusipMessage& other) const {
    return !(*this == other);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
