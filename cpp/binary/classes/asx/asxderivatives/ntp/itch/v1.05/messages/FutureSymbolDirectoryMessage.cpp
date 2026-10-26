#include "FutureSymbolDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

FutureSymbolDirectoryMessage::FutureSymbolDirectoryMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, const std::string& symbol_name, const std::string& long_name, const std::string& isin, const std::string& exchange, const std::string& instrument, const std::string& cfi_code, std::uint16_t expiry_year, ExpiryMonth expiry_month, std::uint8_t price_display_decimals, std::uint32_t price_fractional_denominator, std::uint32_t price_minimum_tick, std::uint32_t last_trading_date, Decimal prior_day_settlement, const std::string& currency, std::uint64_t lot_size_or_face_value, std::uint8_t maturity_value, std::uint16_t coupon_rate, std::uint8_t payments_per_year, std::uint32_t block_lot_size, std::uint32_t expiry_date)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), symbol_name_(symbol_name), long_name_(long_name), isin_(isin), exchange_(exchange), instrument_(instrument), cfi_code_(cfi_code), expiry_year_(expiry_year), expiry_month_(expiry_month), price_display_decimals_(price_display_decimals), price_fractional_denominator_(price_fractional_denominator), price_minimum_tick_(price_minimum_tick), last_trading_date_(last_trading_date), prior_day_settlement_(prior_day_settlement), currency_(currency), lot_size_or_face_value_(lot_size_or_face_value), maturity_value_(maturity_value), coupon_rate_(coupon_rate), payments_per_year_(payments_per_year), block_lot_size_(block_lot_size), expiry_date_(expiry_date) {}

std::chrono::nanoseconds FutureSymbolDirectoryMessage::nanoseconds() const { return nanoseconds_; }
void FutureSymbolDirectoryMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t FutureSymbolDirectoryMessage::trade_date() const { return trade_date_; }
void FutureSymbolDirectoryMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t FutureSymbolDirectoryMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void FutureSymbolDirectoryMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

const std::string& FutureSymbolDirectoryMessage::symbol_name() const { return symbol_name_; }
std::string& FutureSymbolDirectoryMessage::symbol_name() { return symbol_name_; }
void FutureSymbolDirectoryMessage::set_symbol_name(const std::string& value) { symbol_name_ = value; }

const std::string& FutureSymbolDirectoryMessage::long_name() const { return long_name_; }
std::string& FutureSymbolDirectoryMessage::long_name() { return long_name_; }
void FutureSymbolDirectoryMessage::set_long_name(const std::string& value) { long_name_ = value; }

const std::string& FutureSymbolDirectoryMessage::isin() const { return isin_; }
std::string& FutureSymbolDirectoryMessage::isin() { return isin_; }
void FutureSymbolDirectoryMessage::set_isin(const std::string& value) { isin_ = value; }

const std::string& FutureSymbolDirectoryMessage::exchange() const { return exchange_; }
std::string& FutureSymbolDirectoryMessage::exchange() { return exchange_; }
void FutureSymbolDirectoryMessage::set_exchange(const std::string& value) { exchange_ = value; }

const std::string& FutureSymbolDirectoryMessage::instrument() const { return instrument_; }
std::string& FutureSymbolDirectoryMessage::instrument() { return instrument_; }
void FutureSymbolDirectoryMessage::set_instrument(const std::string& value) { instrument_ = value; }

const std::string& FutureSymbolDirectoryMessage::cfi_code() const { return cfi_code_; }
std::string& FutureSymbolDirectoryMessage::cfi_code() { return cfi_code_; }
void FutureSymbolDirectoryMessage::set_cfi_code(const std::string& value) { cfi_code_ = value; }

std::uint16_t FutureSymbolDirectoryMessage::expiry_year() const { return expiry_year_; }
void FutureSymbolDirectoryMessage::set_expiry_year(std::uint16_t value) { expiry_year_ = value; }

ExpiryMonth FutureSymbolDirectoryMessage::expiry_month() const { return expiry_month_; }
void FutureSymbolDirectoryMessage::set_expiry_month(ExpiryMonth value) { expiry_month_ = value; }

std::uint8_t FutureSymbolDirectoryMessage::price_display_decimals() const { return price_display_decimals_; }
void FutureSymbolDirectoryMessage::set_price_display_decimals(std::uint8_t value) { price_display_decimals_ = value; }

std::uint32_t FutureSymbolDirectoryMessage::price_fractional_denominator() const { return price_fractional_denominator_; }
void FutureSymbolDirectoryMessage::set_price_fractional_denominator(std::uint32_t value) { price_fractional_denominator_ = value; }

std::uint32_t FutureSymbolDirectoryMessage::price_minimum_tick() const { return price_minimum_tick_; }
void FutureSymbolDirectoryMessage::set_price_minimum_tick(std::uint32_t value) { price_minimum_tick_ = value; }

std::uint32_t FutureSymbolDirectoryMessage::last_trading_date() const { return last_trading_date_; }
void FutureSymbolDirectoryMessage::set_last_trading_date(std::uint32_t value) { last_trading_date_ = value; }

Decimal FutureSymbolDirectoryMessage::prior_day_settlement() const { return prior_day_settlement_; }
void FutureSymbolDirectoryMessage::set_prior_day_settlement(Decimal value) { prior_day_settlement_ = value; }

const std::string& FutureSymbolDirectoryMessage::currency() const { return currency_; }
std::string& FutureSymbolDirectoryMessage::currency() { return currency_; }
void FutureSymbolDirectoryMessage::set_currency(const std::string& value) { currency_ = value; }

std::uint64_t FutureSymbolDirectoryMessage::lot_size_or_face_value() const { return lot_size_or_face_value_; }
void FutureSymbolDirectoryMessage::set_lot_size_or_face_value(std::uint64_t value) { lot_size_or_face_value_ = value; }

std::uint8_t FutureSymbolDirectoryMessage::maturity_value() const { return maturity_value_; }
void FutureSymbolDirectoryMessage::set_maturity_value(std::uint8_t value) { maturity_value_ = value; }

std::uint16_t FutureSymbolDirectoryMessage::coupon_rate() const { return coupon_rate_; }
void FutureSymbolDirectoryMessage::set_coupon_rate(std::uint16_t value) { coupon_rate_ = value; }

std::uint8_t FutureSymbolDirectoryMessage::payments_per_year() const { return payments_per_year_; }
void FutureSymbolDirectoryMessage::set_payments_per_year(std::uint8_t value) { payments_per_year_ = value; }

std::uint32_t FutureSymbolDirectoryMessage::block_lot_size() const { return block_lot_size_; }
void FutureSymbolDirectoryMessage::set_block_lot_size(std::uint32_t value) { block_lot_size_ = value; }

std::uint32_t FutureSymbolDirectoryMessage::expiry_date() const { return expiry_date_; }
void FutureSymbolDirectoryMessage::set_expiry_date(std::uint32_t value) { expiry_date_ = value; }

MessageCode FutureSymbolDirectoryMessage::type() const { return message_type; }

std::string_view FutureSymbolDirectoryMessage::name() const { return "Future Symbol Directory Message"; }

std::size_t FutureSymbolDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FutureSymbolDirectoryMessage", wire_size, length);

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

    price_display_decimals_ = wire::read_u8(data + offset);
    offset += 1;

    price_fractional_denominator_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_minimum_tick_ = wire::read_u32_be(data + offset);
    offset += 4;

    last_trading_date_ = wire::read_u32_be(data + offset);
    offset += 4;

    prior_day_settlement_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
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

    return offset;
}

std::size_t FutureSymbolDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FutureSymbolDirectoryMessage", wire_size, capacity);

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

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_display_decimals_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_fractional_denominator_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_minimum_tick_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(last_trading_date_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(prior_day_settlement_.mantissa()));
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

    return offset;
}

std::size_t FutureSymbolDirectoryMessage::encoded_size() const {
    return wire_size;
}

void FutureSymbolDirectoryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> FutureSymbolDirectoryMessage::clone() const {
    return std::make_unique<FutureSymbolDirectoryMessage>(*this);
}

void FutureSymbolDirectoryMessage::print(std::ostream& out) const {
    out << "FutureSymbolDirectoryMessage{";
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
    out << ", price_display_decimals=";
    out << static_cast<int>(price_display_decimals_);
    out << ", price_fractional_denominator=";
    out << price_fractional_denominator_;
    out << ", price_minimum_tick=";
    out << price_minimum_tick_;
    out << ", last_trading_date=";
    out << last_trading_date_;
    out << ", prior_day_settlement=";
    out << prior_day_settlement_;
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
    out << '}';
}

bool FutureSymbolDirectoryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const FutureSymbolDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FutureSymbolDirectoryMessage::operator==(const FutureSymbolDirectoryMessage& other) const {
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
        && price_display_decimals_ == other.price_display_decimals_
        && price_fractional_denominator_ == other.price_fractional_denominator_
        && price_minimum_tick_ == other.price_minimum_tick_
        && last_trading_date_ == other.last_trading_date_
        && prior_day_settlement_ == other.prior_day_settlement_
        && currency_ == other.currency_
        && lot_size_or_face_value_ == other.lot_size_or_face_value_
        && maturity_value_ == other.maturity_value_
        && coupon_rate_ == other.coupon_rate_
        && payments_per_year_ == other.payments_per_year_
        && block_lot_size_ == other.block_lot_size_
        && expiry_date_ == other.expiry_date_;
}

bool FutureSymbolDirectoryMessage::operator!=(const FutureSymbolDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
