#include "SeriesUpdate.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

SeriesUpdate::SeriesUpdate(std::chrono::nanoseconds nanoseconds, std::uint32_t product_id, const std::string& underlying_symbol, const std::string& security_symbol, const std::string& expiration_date, Decimal strike_price, CallOrPut call_or_put, const std::string& opening_time, const std::string& closing_time, RestrictedOption restricted_option, LongTermOption long_term_option, ActiveOnMiax active_on_miax, MiaxBboPostingIncrementIndicator miax_bbo_posting_increment_indicator, LiquidityAcceptanceIncrementIndicator liquidity_acceptance_increment_indicator, OpeningUnderlyingMarketCode opening_underlying_market_code, Decimal priority_quote_width, const std::array<std::byte, 8>& reserved_8)
  : nanoseconds_(nanoseconds), product_id_(product_id), underlying_symbol_(underlying_symbol), security_symbol_(security_symbol), expiration_date_(expiration_date), strike_price_(strike_price), call_or_put_(call_or_put), opening_time_(opening_time), closing_time_(closing_time), restricted_option_(restricted_option), long_term_option_(long_term_option), active_on_miax_(active_on_miax), miax_bbo_posting_increment_indicator_(miax_bbo_posting_increment_indicator), liquidity_acceptance_increment_indicator_(liquidity_acceptance_increment_indicator), opening_underlying_market_code_(opening_underlying_market_code), priority_quote_width_(priority_quote_width), reserved_8_(reserved_8) {}

std::chrono::nanoseconds SeriesUpdate::nanoseconds() const { return nanoseconds_; }
void SeriesUpdate::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t SeriesUpdate::product_id() const { return product_id_; }
void SeriesUpdate::set_product_id(std::uint32_t value) { product_id_ = value; }

const std::string& SeriesUpdate::underlying_symbol() const { return underlying_symbol_; }
std::string& SeriesUpdate::underlying_symbol() { return underlying_symbol_; }
void SeriesUpdate::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

const std::string& SeriesUpdate::security_symbol() const { return security_symbol_; }
std::string& SeriesUpdate::security_symbol() { return security_symbol_; }
void SeriesUpdate::set_security_symbol(const std::string& value) { security_symbol_ = value; }

const std::string& SeriesUpdate::expiration_date() const { return expiration_date_; }
std::string& SeriesUpdate::expiration_date() { return expiration_date_; }
void SeriesUpdate::set_expiration_date(const std::string& value) { expiration_date_ = value; }

Decimal SeriesUpdate::strike_price() const { return strike_price_; }
void SeriesUpdate::set_strike_price(Decimal value) { strike_price_ = value; }

CallOrPut SeriesUpdate::call_or_put() const { return call_or_put_; }
void SeriesUpdate::set_call_or_put(CallOrPut value) { call_or_put_ = value; }

const std::string& SeriesUpdate::opening_time() const { return opening_time_; }
std::string& SeriesUpdate::opening_time() { return opening_time_; }
void SeriesUpdate::set_opening_time(const std::string& value) { opening_time_ = value; }

const std::string& SeriesUpdate::closing_time() const { return closing_time_; }
std::string& SeriesUpdate::closing_time() { return closing_time_; }
void SeriesUpdate::set_closing_time(const std::string& value) { closing_time_ = value; }

RestrictedOption SeriesUpdate::restricted_option() const { return restricted_option_; }
void SeriesUpdate::set_restricted_option(RestrictedOption value) { restricted_option_ = value; }

LongTermOption SeriesUpdate::long_term_option() const { return long_term_option_; }
void SeriesUpdate::set_long_term_option(LongTermOption value) { long_term_option_ = value; }

ActiveOnMiax SeriesUpdate::active_on_miax() const { return active_on_miax_; }
void SeriesUpdate::set_active_on_miax(ActiveOnMiax value) { active_on_miax_ = value; }

MiaxBboPostingIncrementIndicator SeriesUpdate::miax_bbo_posting_increment_indicator() const { return miax_bbo_posting_increment_indicator_; }
void SeriesUpdate::set_miax_bbo_posting_increment_indicator(MiaxBboPostingIncrementIndicator value) { miax_bbo_posting_increment_indicator_ = value; }

LiquidityAcceptanceIncrementIndicator SeriesUpdate::liquidity_acceptance_increment_indicator() const { return liquidity_acceptance_increment_indicator_; }
void SeriesUpdate::set_liquidity_acceptance_increment_indicator(LiquidityAcceptanceIncrementIndicator value) { liquidity_acceptance_increment_indicator_ = value; }

OpeningUnderlyingMarketCode SeriesUpdate::opening_underlying_market_code() const { return opening_underlying_market_code_; }
void SeriesUpdate::set_opening_underlying_market_code(OpeningUnderlyingMarketCode value) { opening_underlying_market_code_ = value; }

Decimal SeriesUpdate::priority_quote_width() const { return priority_quote_width_; }
void SeriesUpdate::set_priority_quote_width(Decimal value) { priority_quote_width_ = value; }

const std::array<std::byte, 8>& SeriesUpdate::reserved_8() const { return reserved_8_; }
std::array<std::byte, 8>& SeriesUpdate::reserved_8() { return reserved_8_; }
void SeriesUpdate::set_reserved_8(const std::array<std::byte, 8>& value) { reserved_8_ = value; }

DataCode SeriesUpdate::type() const { return message_type; }

std::string_view SeriesUpdate::name() const { return "Series Update"; }

std::size_t SeriesUpdate::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SeriesUpdate", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    product_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    underlying_symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    security_symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    expiration_date_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    strike_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_le(data + offset)), -4);
    offset += 4;

    call_or_put_ = static_cast<CallOrPut>(wire::read_char(data + offset));
    offset += 1;

    opening_time_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    closing_time_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    restricted_option_ = static_cast<RestrictedOption>(wire::read_char(data + offset));
    offset += 1;

    long_term_option_ = static_cast<LongTermOption>(wire::read_char(data + offset));
    offset += 1;

    active_on_miax_ = static_cast<ActiveOnMiax>(wire::read_char(data + offset));
    offset += 1;

    miax_bbo_posting_increment_indicator_ = static_cast<MiaxBboPostingIncrementIndicator>(wire::read_char(data + offset));
    offset += 1;

    liquidity_acceptance_increment_indicator_ = static_cast<LiquidityAcceptanceIncrementIndicator>(wire::read_char(data + offset));
    offset += 1;

    opening_underlying_market_code_ = static_cast<OpeningUnderlyingMarketCode>(wire::read_char(data + offset));
    offset += 1;

    priority_quote_width_ = Decimal(static_cast<std::int64_t>(wire::read_u32_le(data + offset)), -4);
    offset += 4;

    wire::read_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    return offset;
}

std::size_t SeriesUpdate::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SeriesUpdate", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(product_id_));
    offset += 4;

    wire::write_text(data + offset, 11, ' ', underlying_symbol_);
    offset += 11;

    wire::write_text(data + offset, 6, ' ', security_symbol_);
    offset += 6;

    wire::write_text(data + offset, 8, ' ', expiration_date_);
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(strike_price_.mantissa()));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(call_or_put_));
    offset += 1;

    wire::write_text(data + offset, 8, ' ', opening_time_);
    offset += 8;

    wire::write_text(data + offset, 8, ' ', closing_time_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(restricted_option_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(long_term_option_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(active_on_miax_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(miax_bbo_posting_increment_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(liquidity_acceptance_increment_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(opening_underlying_market_code_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(priority_quote_width_.mantissa()));
    offset += 4;

    wire::write_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    return offset;
}

std::size_t SeriesUpdate::encoded_size() const {
    return wire_size;
}

void SeriesUpdate::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> SeriesUpdate::clone() const {
    return std::make_unique<SeriesUpdate>(*this);
}

void SeriesUpdate::print(std::ostream& out) const {
    out << "SeriesUpdate{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", product_id=";
    out << product_id_;
    out << ", underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << ", security_symbol=";
    print::text(out, security_symbol_);
    out << ", expiration_date=";
    print::text(out, expiration_date_);
    out << ", strike_price=";
    out << strike_price_;
    out << ", call_or_put=";
    out << call_or_put_;
    out << ", opening_time=";
    print::text(out, opening_time_);
    out << ", closing_time=";
    print::text(out, closing_time_);
    out << ", restricted_option=";
    out << restricted_option_;
    out << ", long_term_option=";
    out << long_term_option_;
    out << ", active_on_miax=";
    out << active_on_miax_;
    out << ", miax_bbo_posting_increment_indicator=";
    out << miax_bbo_posting_increment_indicator_;
    out << ", liquidity_acceptance_increment_indicator=";
    out << liquidity_acceptance_increment_indicator_;
    out << ", opening_underlying_market_code=";
    out << opening_underlying_market_code_;
    out << ", priority_quote_width=";
    out << priority_quote_width_;
    out << ", reserved_8=";
    print::hex(out, reserved_8_.data(), reserved_8_.size());
    out << '}';
}

bool SeriesUpdate::equals(const Data& other) const {
    const auto* that = dynamic_cast<const SeriesUpdate*>(&other);
    return that != nullptr && *this == *that;
}

bool SeriesUpdate::operator==(const SeriesUpdate& other) const {
    return nanoseconds_ == other.nanoseconds_
        && product_id_ == other.product_id_
        && underlying_symbol_ == other.underlying_symbol_
        && security_symbol_ == other.security_symbol_
        && expiration_date_ == other.expiration_date_
        && strike_price_ == other.strike_price_
        && call_or_put_ == other.call_or_put_
        && opening_time_ == other.opening_time_
        && closing_time_ == other.closing_time_
        && restricted_option_ == other.restricted_option_
        && long_term_option_ == other.long_term_option_
        && active_on_miax_ == other.active_on_miax_
        && miax_bbo_posting_increment_indicator_ == other.miax_bbo_posting_increment_indicator_
        && liquidity_acceptance_increment_indicator_ == other.liquidity_acceptance_increment_indicator_
        && opening_underlying_market_code_ == other.opening_underlying_market_code_
        && priority_quote_width_ == other.priority_quote_width_
        && reserved_8_ == other.reserved_8_;
}

bool SeriesUpdate::operator!=(const SeriesUpdate& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
