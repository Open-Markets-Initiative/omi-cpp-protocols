#include "OptionsSymbolDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

OptionsSymbolDirectoryMessage::OptionsSymbolDirectoryMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, const std::string& symbol_name, const std::string& long_name, const std::string& isin, const std::string& exchange, const std::string& instrument, const std::string& cfi_code, std::uint16_t expiry_year, ExpiryMonth expiry_month, OptionType option_type, Decimal strike, std::uint32_t underlying_tradeable_instrument_id, std::uint8_t price_display_decimals, std::uint32_t price_fractional_denominator, std::uint32_t price_minimum_tick, std::uint8_t strike_price_decimal_position, std::uint32_t strike_price_fractional_denominator, std::uint32_t strike_price_minimum_tick, std::uint32_t last_trading_date, Decimal prior_day_settlement, std::uint64_t volatility, const std::string& currency, std::uint64_t lot_size_or_face_value, std::uint8_t maturity_value, std::uint16_t coupon_rate, std::uint8_t payments_per_year, std::uint32_t block_lot_size, std::uint32_t expiry_date, const std::string& basis_of_quotation)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), symbol_name_(symbol_name), long_name_(long_name), isin_(isin), exchange_(exchange), instrument_(instrument), cfi_code_(cfi_code), expiry_year_(expiry_year), expiry_month_(expiry_month), option_type_(option_type), strike_(strike), underlying_tradeable_instrument_id_(underlying_tradeable_instrument_id), price_display_decimals_(price_display_decimals), price_fractional_denominator_(price_fractional_denominator), price_minimum_tick_(price_minimum_tick), strike_price_decimal_position_(strike_price_decimal_position), strike_price_fractional_denominator_(strike_price_fractional_denominator), strike_price_minimum_tick_(strike_price_minimum_tick), last_trading_date_(last_trading_date), prior_day_settlement_(prior_day_settlement), volatility_(volatility), currency_(currency), lot_size_or_face_value_(lot_size_or_face_value), maturity_value_(maturity_value), coupon_rate_(coupon_rate), payments_per_year_(payments_per_year), block_lot_size_(block_lot_size), expiry_date_(expiry_date), basis_of_quotation_(basis_of_quotation) {}

std::chrono::nanoseconds OptionsSymbolDirectoryMessage::nanoseconds() const { return nanoseconds_; }
void OptionsSymbolDirectoryMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t OptionsSymbolDirectoryMessage::trade_date() const { return trade_date_; }
void OptionsSymbolDirectoryMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t OptionsSymbolDirectoryMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void OptionsSymbolDirectoryMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

const std::string& OptionsSymbolDirectoryMessage::symbol_name() const { return symbol_name_; }
std::string& OptionsSymbolDirectoryMessage::symbol_name() { return symbol_name_; }
void OptionsSymbolDirectoryMessage::set_symbol_name(const std::string& value) { symbol_name_ = value; }

const std::string& OptionsSymbolDirectoryMessage::long_name() const { return long_name_; }
std::string& OptionsSymbolDirectoryMessage::long_name() { return long_name_; }
void OptionsSymbolDirectoryMessage::set_long_name(const std::string& value) { long_name_ = value; }

const std::string& OptionsSymbolDirectoryMessage::isin() const { return isin_; }
std::string& OptionsSymbolDirectoryMessage::isin() { return isin_; }
void OptionsSymbolDirectoryMessage::set_isin(const std::string& value) { isin_ = value; }

const std::string& OptionsSymbolDirectoryMessage::exchange() const { return exchange_; }
std::string& OptionsSymbolDirectoryMessage::exchange() { return exchange_; }
void OptionsSymbolDirectoryMessage::set_exchange(const std::string& value) { exchange_ = value; }

const std::string& OptionsSymbolDirectoryMessage::instrument() const { return instrument_; }
std::string& OptionsSymbolDirectoryMessage::instrument() { return instrument_; }
void OptionsSymbolDirectoryMessage::set_instrument(const std::string& value) { instrument_ = value; }

const std::string& OptionsSymbolDirectoryMessage::cfi_code() const { return cfi_code_; }
std::string& OptionsSymbolDirectoryMessage::cfi_code() { return cfi_code_; }
void OptionsSymbolDirectoryMessage::set_cfi_code(const std::string& value) { cfi_code_ = value; }

std::uint16_t OptionsSymbolDirectoryMessage::expiry_year() const { return expiry_year_; }
void OptionsSymbolDirectoryMessage::set_expiry_year(std::uint16_t value) { expiry_year_ = value; }

ExpiryMonth OptionsSymbolDirectoryMessage::expiry_month() const { return expiry_month_; }
void OptionsSymbolDirectoryMessage::set_expiry_month(ExpiryMonth value) { expiry_month_ = value; }

OptionType OptionsSymbolDirectoryMessage::option_type() const { return option_type_; }
void OptionsSymbolDirectoryMessage::set_option_type(OptionType value) { option_type_ = value; }

Decimal OptionsSymbolDirectoryMessage::strike() const { return strike_; }
void OptionsSymbolDirectoryMessage::set_strike(Decimal value) { strike_ = value; }

std::uint32_t OptionsSymbolDirectoryMessage::underlying_tradeable_instrument_id() const { return underlying_tradeable_instrument_id_; }
void OptionsSymbolDirectoryMessage::set_underlying_tradeable_instrument_id(std::uint32_t value) { underlying_tradeable_instrument_id_ = value; }

std::uint8_t OptionsSymbolDirectoryMessage::price_display_decimals() const { return price_display_decimals_; }
void OptionsSymbolDirectoryMessage::set_price_display_decimals(std::uint8_t value) { price_display_decimals_ = value; }

std::uint32_t OptionsSymbolDirectoryMessage::price_fractional_denominator() const { return price_fractional_denominator_; }
void OptionsSymbolDirectoryMessage::set_price_fractional_denominator(std::uint32_t value) { price_fractional_denominator_ = value; }

std::uint32_t OptionsSymbolDirectoryMessage::price_minimum_tick() const { return price_minimum_tick_; }
void OptionsSymbolDirectoryMessage::set_price_minimum_tick(std::uint32_t value) { price_minimum_tick_ = value; }

std::uint8_t OptionsSymbolDirectoryMessage::strike_price_decimal_position() const { return strike_price_decimal_position_; }
void OptionsSymbolDirectoryMessage::set_strike_price_decimal_position(std::uint8_t value) { strike_price_decimal_position_ = value; }

std::uint32_t OptionsSymbolDirectoryMessage::strike_price_fractional_denominator() const { return strike_price_fractional_denominator_; }
void OptionsSymbolDirectoryMessage::set_strike_price_fractional_denominator(std::uint32_t value) { strike_price_fractional_denominator_ = value; }

std::uint32_t OptionsSymbolDirectoryMessage::strike_price_minimum_tick() const { return strike_price_minimum_tick_; }
void OptionsSymbolDirectoryMessage::set_strike_price_minimum_tick(std::uint32_t value) { strike_price_minimum_tick_ = value; }

std::uint32_t OptionsSymbolDirectoryMessage::last_trading_date() const { return last_trading_date_; }
void OptionsSymbolDirectoryMessage::set_last_trading_date(std::uint32_t value) { last_trading_date_ = value; }

Decimal OptionsSymbolDirectoryMessage::prior_day_settlement() const { return prior_day_settlement_; }
void OptionsSymbolDirectoryMessage::set_prior_day_settlement(Decimal value) { prior_day_settlement_ = value; }

std::uint64_t OptionsSymbolDirectoryMessage::volatility() const { return volatility_; }
void OptionsSymbolDirectoryMessage::set_volatility(std::uint64_t value) { volatility_ = value; }

const std::string& OptionsSymbolDirectoryMessage::currency() const { return currency_; }
std::string& OptionsSymbolDirectoryMessage::currency() { return currency_; }
void OptionsSymbolDirectoryMessage::set_currency(const std::string& value) { currency_ = value; }

std::uint64_t OptionsSymbolDirectoryMessage::lot_size_or_face_value() const { return lot_size_or_face_value_; }
void OptionsSymbolDirectoryMessage::set_lot_size_or_face_value(std::uint64_t value) { lot_size_or_face_value_ = value; }

std::uint8_t OptionsSymbolDirectoryMessage::maturity_value() const { return maturity_value_; }
void OptionsSymbolDirectoryMessage::set_maturity_value(std::uint8_t value) { maturity_value_ = value; }

std::uint16_t OptionsSymbolDirectoryMessage::coupon_rate() const { return coupon_rate_; }
void OptionsSymbolDirectoryMessage::set_coupon_rate(std::uint16_t value) { coupon_rate_ = value; }

std::uint8_t OptionsSymbolDirectoryMessage::payments_per_year() const { return payments_per_year_; }
void OptionsSymbolDirectoryMessage::set_payments_per_year(std::uint8_t value) { payments_per_year_ = value; }

std::uint32_t OptionsSymbolDirectoryMessage::block_lot_size() const { return block_lot_size_; }
void OptionsSymbolDirectoryMessage::set_block_lot_size(std::uint32_t value) { block_lot_size_ = value; }

std::uint32_t OptionsSymbolDirectoryMessage::expiry_date() const { return expiry_date_; }
void OptionsSymbolDirectoryMessage::set_expiry_date(std::uint32_t value) { expiry_date_ = value; }

const std::string& OptionsSymbolDirectoryMessage::basis_of_quotation() const { return basis_of_quotation_; }
std::string& OptionsSymbolDirectoryMessage::basis_of_quotation() { return basis_of_quotation_; }
void OptionsSymbolDirectoryMessage::set_basis_of_quotation(const std::string& value) { basis_of_quotation_ = value; }

MessageCode OptionsSymbolDirectoryMessage::type() const { return message_type; }

std::string_view OptionsSymbolDirectoryMessage::name() const { return "Options Symbol Directory Message"; }

std::size_t OptionsSymbolDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsSymbolDirectoryMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    symbol_name_ = wire::read_text(data + offset, 32, ' ');
    offset += 32;

    long_name_ = wire::read_text(data + offset, 60, ' ');
    offset += 60;

    isin_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    exchange_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    instrument_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    cfi_code_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    expiry_year_ = wire::read_u16_be(data + offset);
    offset += 2;

    expiry_month_ = static_cast<ExpiryMonth>(wire::read_u8(data + offset));
    offset += 1;

    option_type_ = static_cast<OptionType>(wire::read_char(data + offset));
    offset += 1;

    strike_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    underlying_tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_display_decimals_ = wire::read_u8(data + offset);
    offset += 1;

    price_fractional_denominator_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_minimum_tick_ = wire::read_u32_be(data + offset);
    offset += 4;

    strike_price_decimal_position_ = wire::read_u8(data + offset);
    offset += 1;

    strike_price_fractional_denominator_ = wire::read_u32_be(data + offset);
    offset += 4;

    strike_price_minimum_tick_ = wire::read_u32_be(data + offset);
    offset += 4;

    last_trading_date_ = wire::read_u32_be(data + offset);
    offset += 4;

    prior_day_settlement_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    volatility_ = wire::read_u64_be(data + offset);
    offset += 8;

    currency_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    lot_size_or_face_value_ = wire::read_u64_be(data + offset);
    offset += 8;

    maturity_value_ = wire::read_u8(data + offset);
    offset += 1;

    coupon_rate_ = wire::read_u16_be(data + offset);
    offset += 2;

    payments_per_year_ = wire::read_u8(data + offset);
    offset += 1;

    block_lot_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    expiry_date_ = wire::read_u32_be(data + offset);
    offset += 4;

    basis_of_quotation_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    return offset;
}

std::size_t OptionsSymbolDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsSymbolDirectoryMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_));
    offset += 4;

    wire::write_text(data + offset, 32, ' ', symbol_name_);
    offset += 32;

    wire::write_text(data + offset, 60, ' ', long_name_);
    offset += 60;

    wire::write_text(data + offset, 12, ' ', isin_);
    offset += 12;

    wire::write_text(data + offset, 6, ' ', exchange_);
    offset += 6;

    wire::write_text(data + offset, 6, ' ', instrument_);
    offset += 6;

    wire::write_text(data + offset, 6, ' ', cfi_code_);
    offset += 6;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(expiry_year_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(expiry_month_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(option_type_));
    offset += 1;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(strike_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(underlying_tradeable_instrument_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_display_decimals_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_fractional_denominator_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_minimum_tick_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(strike_price_decimal_position_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(strike_price_fractional_denominator_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(strike_price_minimum_tick_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(last_trading_date_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(prior_day_settlement_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(volatility_));
    offset += 8;

    wire::write_text(data + offset, 3, ' ', currency_);
    offset += 3;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(lot_size_or_face_value_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(maturity_value_));
    offset += 1;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(coupon_rate_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(payments_per_year_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(block_lot_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(expiry_date_));
    offset += 4;

    wire::write_text(data + offset, 10, ' ', basis_of_quotation_);
    offset += 10;

    return offset;
}

std::size_t OptionsSymbolDirectoryMessage::encoded_size() const {
    return wire_size;
}

void OptionsSymbolDirectoryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsSymbolDirectoryMessage::clone() const {
    return std::make_unique<OptionsSymbolDirectoryMessage>(*this);
}

void OptionsSymbolDirectoryMessage::print(std::ostream& out) const {
    out << "OptionsSymbolDirectoryMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", tradeable_instrument_id=";
    out << tradeable_instrument_id_;
    out << ", symbol_name=";
    print::text(out, symbol_name_);
    out << ", long_name=";
    print::text(out, long_name_);
    out << ", isin=";
    print::text(out, isin_);
    out << ", exchange=";
    print::text(out, exchange_);
    out << ", instrument=";
    print::text(out, instrument_);
    out << ", cfi_code=";
    print::text(out, cfi_code_);
    out << ", expiry_year=";
    out << expiry_year_;
    out << ", expiry_month=";
    out << expiry_month_;
    out << ", option_type=";
    out << option_type_;
    out << ", strike=";
    out << strike_;
    out << ", underlying_tradeable_instrument_id=";
    out << underlying_tradeable_instrument_id_;
    out << ", price_display_decimals=";
    out << static_cast<int>(price_display_decimals_);
    out << ", price_fractional_denominator=";
    out << price_fractional_denominator_;
    out << ", price_minimum_tick=";
    out << price_minimum_tick_;
    out << ", strike_price_decimal_position=";
    out << static_cast<int>(strike_price_decimal_position_);
    out << ", strike_price_fractional_denominator=";
    out << strike_price_fractional_denominator_;
    out << ", strike_price_minimum_tick=";
    out << strike_price_minimum_tick_;
    out << ", last_trading_date=";
    out << last_trading_date_;
    out << ", prior_day_settlement=";
    out << prior_day_settlement_;
    out << ", volatility=";
    out << volatility_;
    out << ", currency=";
    print::text(out, currency_);
    out << ", lot_size_or_face_value=";
    out << lot_size_or_face_value_;
    out << ", maturity_value=";
    out << static_cast<int>(maturity_value_);
    out << ", coupon_rate=";
    out << coupon_rate_;
    out << ", payments_per_year=";
    out << static_cast<int>(payments_per_year_);
    out << ", block_lot_size=";
    out << block_lot_size_;
    out << ", expiry_date=";
    out << expiry_date_;
    out << ", basis_of_quotation=";
    print::text(out, basis_of_quotation_);
    out << '}';
}

bool OptionsSymbolDirectoryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsSymbolDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsSymbolDirectoryMessage::operator==(const OptionsSymbolDirectoryMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && symbol_name_ == other.symbol_name_
        && long_name_ == other.long_name_
        && isin_ == other.isin_
        && exchange_ == other.exchange_
        && instrument_ == other.instrument_
        && cfi_code_ == other.cfi_code_
        && expiry_year_ == other.expiry_year_
        && expiry_month_ == other.expiry_month_
        && option_type_ == other.option_type_
        && strike_ == other.strike_
        && underlying_tradeable_instrument_id_ == other.underlying_tradeable_instrument_id_
        && price_display_decimals_ == other.price_display_decimals_
        && price_fractional_denominator_ == other.price_fractional_denominator_
        && price_minimum_tick_ == other.price_minimum_tick_
        && strike_price_decimal_position_ == other.strike_price_decimal_position_
        && strike_price_fractional_denominator_ == other.strike_price_fractional_denominator_
        && strike_price_minimum_tick_ == other.strike_price_minimum_tick_
        && last_trading_date_ == other.last_trading_date_
        && prior_day_settlement_ == other.prior_day_settlement_
        && volatility_ == other.volatility_
        && currency_ == other.currency_
        && lot_size_or_face_value_ == other.lot_size_or_face_value_
        && maturity_value_ == other.maturity_value_
        && coupon_rate_ == other.coupon_rate_
        && payments_per_year_ == other.payments_per_year_
        && block_lot_size_ == other.block_lot_size_
        && expiry_date_ == other.expiry_date_
        && basis_of_quotation_ == other.basis_of_quotation_;
}

bool OptionsSymbolDirectoryMessage::operator!=(const OptionsSymbolDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
