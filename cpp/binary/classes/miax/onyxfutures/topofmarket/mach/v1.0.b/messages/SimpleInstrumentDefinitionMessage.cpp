#include "SimpleInstrumentDefinitionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

SimpleInstrumentDefinitionMessage::SimpleInstrumentDefinitionMessage(std::chrono::nanoseconds timestamp, std::uint32_t instrument_id, UnderlyingAssetType underlying_asset_type, const std::string& underlying_asset, const std::string& product_group_code, const std::string& exchange, InstrumentIdSource instrument_id_source, InstrumentType instrument_type, std::uint32_t maturity_month_year, Currency currency, SettlementCurrency settlement_currency, MatchAlgorithm match_algorithm, std::uint32_t minimum_size, std::uint32_t maximum_size, Decimal tick, const std::string& unit_of_measure, std::uint32_t unit_of_measure_quantity, Decimal settlement_price, SettlementPriceTypeCalcMethod settlement_price_type_calc_method, std::uint32_t total_volume, std::uint32_t open_interest_quantity, Decimal high_limit_price, Decimal low_limit_price, TradingCollarVariationType trading_collar_variation_type, Decimal trading_collar_variation, const std::array<std::byte, 16>& reserved_16)
  : timestamp_(timestamp), instrument_id_(instrument_id), underlying_asset_type_(underlying_asset_type), underlying_asset_(underlying_asset), product_group_code_(product_group_code), exchange_(exchange), instrument_id_source_(instrument_id_source), instrument_type_(instrument_type), maturity_month_year_(maturity_month_year), currency_(currency), settlement_currency_(settlement_currency), match_algorithm_(match_algorithm), minimum_size_(minimum_size), maximum_size_(maximum_size), tick_(tick), unit_of_measure_(unit_of_measure), unit_of_measure_quantity_(unit_of_measure_quantity), settlement_price_(settlement_price), settlement_price_type_calc_method_(settlement_price_type_calc_method), total_volume_(total_volume), open_interest_quantity_(open_interest_quantity), high_limit_price_(high_limit_price), low_limit_price_(low_limit_price), trading_collar_variation_type_(trading_collar_variation_type), trading_collar_variation_(trading_collar_variation), reserved_16_(reserved_16) {}

std::chrono::nanoseconds SimpleInstrumentDefinitionMessage::timestamp() const { return timestamp_; }
void SimpleInstrumentDefinitionMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint32_t SimpleInstrumentDefinitionMessage::instrument_id() const { return instrument_id_; }
void SimpleInstrumentDefinitionMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

UnderlyingAssetType SimpleInstrumentDefinitionMessage::underlying_asset_type() const { return underlying_asset_type_; }
void SimpleInstrumentDefinitionMessage::set_underlying_asset_type(UnderlyingAssetType value) { underlying_asset_type_ = value; }

const std::string& SimpleInstrumentDefinitionMessage::underlying_asset() const { return underlying_asset_; }
std::string& SimpleInstrumentDefinitionMessage::underlying_asset() { return underlying_asset_; }
void SimpleInstrumentDefinitionMessage::set_underlying_asset(const std::string& value) { underlying_asset_ = value; }

const std::string& SimpleInstrumentDefinitionMessage::product_group_code() const { return product_group_code_; }
std::string& SimpleInstrumentDefinitionMessage::product_group_code() { return product_group_code_; }
void SimpleInstrumentDefinitionMessage::set_product_group_code(const std::string& value) { product_group_code_ = value; }

const std::string& SimpleInstrumentDefinitionMessage::exchange() const { return exchange_; }
std::string& SimpleInstrumentDefinitionMessage::exchange() { return exchange_; }
void SimpleInstrumentDefinitionMessage::set_exchange(const std::string& value) { exchange_ = value; }

InstrumentIdSource SimpleInstrumentDefinitionMessage::instrument_id_source() const { return instrument_id_source_; }
void SimpleInstrumentDefinitionMessage::set_instrument_id_source(InstrumentIdSource value) { instrument_id_source_ = value; }

InstrumentType SimpleInstrumentDefinitionMessage::instrument_type() const { return instrument_type_; }
void SimpleInstrumentDefinitionMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

std::uint32_t SimpleInstrumentDefinitionMessage::maturity_month_year() const { return maturity_month_year_; }
void SimpleInstrumentDefinitionMessage::set_maturity_month_year(std::uint32_t value) { maturity_month_year_ = value; }

Currency SimpleInstrumentDefinitionMessage::currency() const { return currency_; }
void SimpleInstrumentDefinitionMessage::set_currency(Currency value) { currency_ = value; }

SettlementCurrency SimpleInstrumentDefinitionMessage::settlement_currency() const { return settlement_currency_; }
void SimpleInstrumentDefinitionMessage::set_settlement_currency(SettlementCurrency value) { settlement_currency_ = value; }

MatchAlgorithm SimpleInstrumentDefinitionMessage::match_algorithm() const { return match_algorithm_; }
void SimpleInstrumentDefinitionMessage::set_match_algorithm(MatchAlgorithm value) { match_algorithm_ = value; }

std::uint32_t SimpleInstrumentDefinitionMessage::minimum_size() const { return minimum_size_; }
void SimpleInstrumentDefinitionMessage::set_minimum_size(std::uint32_t value) { minimum_size_ = value; }

std::uint32_t SimpleInstrumentDefinitionMessage::maximum_size() const { return maximum_size_; }
void SimpleInstrumentDefinitionMessage::set_maximum_size(std::uint32_t value) { maximum_size_ = value; }

Decimal SimpleInstrumentDefinitionMessage::tick() const { return tick_; }
void SimpleInstrumentDefinitionMessage::set_tick(Decimal value) { tick_ = value; }

const std::string& SimpleInstrumentDefinitionMessage::unit_of_measure() const { return unit_of_measure_; }
std::string& SimpleInstrumentDefinitionMessage::unit_of_measure() { return unit_of_measure_; }
void SimpleInstrumentDefinitionMessage::set_unit_of_measure(const std::string& value) { unit_of_measure_ = value; }

std::uint32_t SimpleInstrumentDefinitionMessage::unit_of_measure_quantity() const { return unit_of_measure_quantity_; }
void SimpleInstrumentDefinitionMessage::set_unit_of_measure_quantity(std::uint32_t value) { unit_of_measure_quantity_ = value; }

Decimal SimpleInstrumentDefinitionMessage::settlement_price() const { return settlement_price_; }
void SimpleInstrumentDefinitionMessage::set_settlement_price(Decimal value) { settlement_price_ = value; }

SettlementPriceTypeCalcMethod SimpleInstrumentDefinitionMessage::settlement_price_type_calc_method() const { return settlement_price_type_calc_method_; }
void SimpleInstrumentDefinitionMessage::set_settlement_price_type_calc_method(SettlementPriceTypeCalcMethod value) { settlement_price_type_calc_method_ = value; }

std::uint32_t SimpleInstrumentDefinitionMessage::total_volume() const { return total_volume_; }
void SimpleInstrumentDefinitionMessage::set_total_volume(std::uint32_t value) { total_volume_ = value; }

std::uint32_t SimpleInstrumentDefinitionMessage::open_interest_quantity() const { return open_interest_quantity_; }
void SimpleInstrumentDefinitionMessage::set_open_interest_quantity(std::uint32_t value) { open_interest_quantity_ = value; }

Decimal SimpleInstrumentDefinitionMessage::high_limit_price() const { return high_limit_price_; }
void SimpleInstrumentDefinitionMessage::set_high_limit_price(Decimal value) { high_limit_price_ = value; }

Decimal SimpleInstrumentDefinitionMessage::low_limit_price() const { return low_limit_price_; }
void SimpleInstrumentDefinitionMessage::set_low_limit_price(Decimal value) { low_limit_price_ = value; }

TradingCollarVariationType SimpleInstrumentDefinitionMessage::trading_collar_variation_type() const { return trading_collar_variation_type_; }
void SimpleInstrumentDefinitionMessage::set_trading_collar_variation_type(TradingCollarVariationType value) { trading_collar_variation_type_ = value; }

Decimal SimpleInstrumentDefinitionMessage::trading_collar_variation() const { return trading_collar_variation_; }
void SimpleInstrumentDefinitionMessage::set_trading_collar_variation(Decimal value) { trading_collar_variation_ = value; }

const std::array<std::byte, 16>& SimpleInstrumentDefinitionMessage::reserved_16() const { return reserved_16_; }
std::array<std::byte, 16>& SimpleInstrumentDefinitionMessage::reserved_16() { return reserved_16_; }
void SimpleInstrumentDefinitionMessage::set_reserved_16(const std::array<std::byte, 16>& value) { reserved_16_ = value; }

DataCode SimpleInstrumentDefinitionMessage::type() const { return message_type; }

std::string_view SimpleInstrumentDefinitionMessage::name() const { return "Simple Instrument Definition Message"; }

std::size_t SimpleInstrumentDefinitionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SimpleInstrumentDefinitionMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    underlying_asset_type_ = static_cast<UnderlyingAssetType>(wire::read_char(data + offset));
    offset += 1;

    underlying_asset_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    product_group_code_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    exchange_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    instrument_id_source_ = static_cast<InstrumentIdSource>(wire::read_char(data + offset));
    offset += 1;

    instrument_type_ = static_cast<InstrumentType>(wire::read_char(data + offset));
    offset += 1;

    maturity_month_year_ = wire::read_u32_le(data + offset);
    offset += 4;

    currency_ = static_cast<Currency>(wire::read_char(data + offset));
    offset += 1;

    settlement_currency_ = static_cast<SettlementCurrency>(wire::read_char(data + offset));
    offset += 1;

    match_algorithm_ = static_cast<MatchAlgorithm>(wire::read_char(data + offset));
    offset += 1;

    minimum_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    maximum_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    tick_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    unit_of_measure_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    unit_of_measure_quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    settlement_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    settlement_price_type_calc_method_ = static_cast<SettlementPriceTypeCalcMethod>(wire::read_char(data + offset));
    offset += 1;

    total_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    open_interest_quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    high_limit_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    low_limit_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    trading_collar_variation_type_ = static_cast<TradingCollarVariationType>(wire::read_char(data + offset));
    offset += 1;

    trading_collar_variation_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    wire::read_bytes(data + offset, reserved_16_.data(), 16);
    offset += 16;

    return offset;
}

std::size_t SimpleInstrumentDefinitionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SimpleInstrumentDefinitionMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(underlying_asset_type_));
    offset += 1;

    wire::write_text(data + offset, 4, ' ', underlying_asset_);
    offset += 4;

    wire::write_text(data + offset, 6, ' ', product_group_code_);
    offset += 6;

    wire::write_text(data + offset, 4, ' ', exchange_);
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(instrument_id_source_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(instrument_type_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(maturity_month_year_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(currency_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(settlement_currency_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(match_algorithm_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(minimum_size_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(maximum_size_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(tick_.mantissa()));
    offset += 8;

    wire::write_text(data + offset, 5, ' ', unit_of_measure_);
    offset += 5;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(unit_of_measure_quantity_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(settlement_price_.mantissa()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(settlement_price_type_calc_method_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(total_volume_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(open_interest_quantity_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(high_limit_price_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(low_limit_price_.mantissa()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(trading_collar_variation_type_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(trading_collar_variation_.mantissa()));
    offset += 8;

    wire::write_bytes(data + offset, reserved_16_.data(), 16);
    offset += 16;

    return offset;
}

std::size_t SimpleInstrumentDefinitionMessage::encoded_size() const {
    return wire_size;
}

void SimpleInstrumentDefinitionMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> SimpleInstrumentDefinitionMessage::clone() const {
    return std::make_unique<SimpleInstrumentDefinitionMessage>(*this);
}

void SimpleInstrumentDefinitionMessage::print(std::ostream& out) const {
    out << "SimpleInstrumentDefinitionMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", underlying_asset_type=";
    out << underlying_asset_type_;
    out << ", underlying_asset=";
    print::text(out, underlying_asset_);
    out << ", product_group_code=";
    print::text(out, product_group_code_);
    out << ", exchange=";
    print::text(out, exchange_);
    out << ", instrument_id_source=";
    out << instrument_id_source_;
    out << ", instrument_type=";
    out << instrument_type_;
    out << ", maturity_month_year=";
    out << maturity_month_year_;
    out << ", currency=";
    out << currency_;
    out << ", settlement_currency=";
    out << settlement_currency_;
    out << ", match_algorithm=";
    out << match_algorithm_;
    out << ", minimum_size=";
    out << minimum_size_;
    out << ", maximum_size=";
    out << maximum_size_;
    out << ", tick=";
    out << tick_;
    out << ", unit_of_measure=";
    print::text(out, unit_of_measure_);
    out << ", unit_of_measure_quantity=";
    out << unit_of_measure_quantity_;
    out << ", settlement_price=";
    out << settlement_price_;
    out << ", settlement_price_type_calc_method=";
    out << settlement_price_type_calc_method_;
    out << ", total_volume=";
    out << total_volume_;
    out << ", open_interest_quantity=";
    out << open_interest_quantity_;
    out << ", high_limit_price=";
    out << high_limit_price_;
    out << ", low_limit_price=";
    out << low_limit_price_;
    out << ", trading_collar_variation_type=";
    out << trading_collar_variation_type_;
    out << ", trading_collar_variation=";
    out << trading_collar_variation_;
    out << ", reserved_16=";
    print::hex(out, reserved_16_.data(), reserved_16_.size());
    out << '}';
}

bool SimpleInstrumentDefinitionMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const SimpleInstrumentDefinitionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SimpleInstrumentDefinitionMessage::operator==(const SimpleInstrumentDefinitionMessage& other) const {
    return timestamp_ == other.timestamp_
        && instrument_id_ == other.instrument_id_
        && underlying_asset_type_ == other.underlying_asset_type_
        && underlying_asset_ == other.underlying_asset_
        && product_group_code_ == other.product_group_code_
        && exchange_ == other.exchange_
        && instrument_id_source_ == other.instrument_id_source_
        && instrument_type_ == other.instrument_type_
        && maturity_month_year_ == other.maturity_month_year_
        && currency_ == other.currency_
        && settlement_currency_ == other.settlement_currency_
        && match_algorithm_ == other.match_algorithm_
        && minimum_size_ == other.minimum_size_
        && maximum_size_ == other.maximum_size_
        && tick_ == other.tick_
        && unit_of_measure_ == other.unit_of_measure_
        && unit_of_measure_quantity_ == other.unit_of_measure_quantity_
        && settlement_price_ == other.settlement_price_
        && settlement_price_type_calc_method_ == other.settlement_price_type_calc_method_
        && total_volume_ == other.total_volume_
        && open_interest_quantity_ == other.open_interest_quantity_
        && high_limit_price_ == other.high_limit_price_
        && low_limit_price_ == other.low_limit_price_
        && trading_collar_variation_type_ == other.trading_collar_variation_type_
        && trading_collar_variation_ == other.trading_collar_variation_
        && reserved_16_ == other.reserved_16_;
}

bool SimpleInstrumentDefinitionMessage::operator!=(const SimpleInstrumentDefinitionMessage& other) const {
    return !(*this == other);
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
