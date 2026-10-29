#include "ComplexInstrumentDefinitionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

ComplexInstrumentDefinitionMessage::ComplexInstrumentDefinitionMessage(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, UnderlyingAssetType underlying_asset_type, const std::string& underlying_asset, const std::string& product_group_code, char spread_type, const std::string& exchange, InstrumentIdSource instrument_id_source, InstrumentType instrument_type, Currency currency, SettlementCurrency settlement_currency, MatchAlgorithm match_algorithm, std::uint32_t minimum_size, std::uint32_t maximum_size, Decimal tick, const std::string& unit_of_measure, std::uint32_t unit_of_measure_quantity, TradingCollarVariationType trading_collar_variation_type, Decimal trading_collar_variation, const std::array<std::byte, 16>& reserved_16, std::uint8_t number_of_legs, const std::vector<InstrumentLeg>& instrument_leg)
  : timestamp_(timestamp), strategy_id_(strategy_id), underlying_asset_type_(underlying_asset_type), underlying_asset_(underlying_asset), product_group_code_(product_group_code), spread_type_(spread_type), exchange_(exchange), instrument_id_source_(instrument_id_source), instrument_type_(instrument_type), currency_(currency), settlement_currency_(settlement_currency), match_algorithm_(match_algorithm), minimum_size_(minimum_size), maximum_size_(maximum_size), tick_(tick), unit_of_measure_(unit_of_measure), unit_of_measure_quantity_(unit_of_measure_quantity), trading_collar_variation_type_(trading_collar_variation_type), trading_collar_variation_(trading_collar_variation), reserved_16_(reserved_16), number_of_legs_(number_of_legs), instrument_leg_(instrument_leg) {}

std::chrono::nanoseconds ComplexInstrumentDefinitionMessage::timestamp() const { return timestamp_; }
void ComplexInstrumentDefinitionMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint32_t ComplexInstrumentDefinitionMessage::strategy_id() const { return strategy_id_; }
void ComplexInstrumentDefinitionMessage::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

UnderlyingAssetType ComplexInstrumentDefinitionMessage::underlying_asset_type() const { return underlying_asset_type_; }
void ComplexInstrumentDefinitionMessage::set_underlying_asset_type(UnderlyingAssetType value) { underlying_asset_type_ = value; }

const std::string& ComplexInstrumentDefinitionMessage::underlying_asset() const { return underlying_asset_; }
std::string& ComplexInstrumentDefinitionMessage::underlying_asset() { return underlying_asset_; }
void ComplexInstrumentDefinitionMessage::set_underlying_asset(const std::string& value) { underlying_asset_ = value; }

const std::string& ComplexInstrumentDefinitionMessage::product_group_code() const { return product_group_code_; }
std::string& ComplexInstrumentDefinitionMessage::product_group_code() { return product_group_code_; }
void ComplexInstrumentDefinitionMessage::set_product_group_code(const std::string& value) { product_group_code_ = value; }

char ComplexInstrumentDefinitionMessage::spread_type() const { return spread_type_; }
void ComplexInstrumentDefinitionMessage::set_spread_type(char value) { spread_type_ = value; }

const std::string& ComplexInstrumentDefinitionMessage::exchange() const { return exchange_; }
std::string& ComplexInstrumentDefinitionMessage::exchange() { return exchange_; }
void ComplexInstrumentDefinitionMessage::set_exchange(const std::string& value) { exchange_ = value; }

InstrumentIdSource ComplexInstrumentDefinitionMessage::instrument_id_source() const { return instrument_id_source_; }
void ComplexInstrumentDefinitionMessage::set_instrument_id_source(InstrumentIdSource value) { instrument_id_source_ = value; }

InstrumentType ComplexInstrumentDefinitionMessage::instrument_type() const { return instrument_type_; }
void ComplexInstrumentDefinitionMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

Currency ComplexInstrumentDefinitionMessage::currency() const { return currency_; }
void ComplexInstrumentDefinitionMessage::set_currency(Currency value) { currency_ = value; }

SettlementCurrency ComplexInstrumentDefinitionMessage::settlement_currency() const { return settlement_currency_; }
void ComplexInstrumentDefinitionMessage::set_settlement_currency(SettlementCurrency value) { settlement_currency_ = value; }

MatchAlgorithm ComplexInstrumentDefinitionMessage::match_algorithm() const { return match_algorithm_; }
void ComplexInstrumentDefinitionMessage::set_match_algorithm(MatchAlgorithm value) { match_algorithm_ = value; }

std::uint32_t ComplexInstrumentDefinitionMessage::minimum_size() const { return minimum_size_; }
void ComplexInstrumentDefinitionMessage::set_minimum_size(std::uint32_t value) { minimum_size_ = value; }

std::uint32_t ComplexInstrumentDefinitionMessage::maximum_size() const { return maximum_size_; }
void ComplexInstrumentDefinitionMessage::set_maximum_size(std::uint32_t value) { maximum_size_ = value; }

Decimal ComplexInstrumentDefinitionMessage::tick() const { return tick_; }
void ComplexInstrumentDefinitionMessage::set_tick(Decimal value) { tick_ = value; }

const std::string& ComplexInstrumentDefinitionMessage::unit_of_measure() const { return unit_of_measure_; }
std::string& ComplexInstrumentDefinitionMessage::unit_of_measure() { return unit_of_measure_; }
void ComplexInstrumentDefinitionMessage::set_unit_of_measure(const std::string& value) { unit_of_measure_ = value; }

std::uint32_t ComplexInstrumentDefinitionMessage::unit_of_measure_quantity() const { return unit_of_measure_quantity_; }
void ComplexInstrumentDefinitionMessage::set_unit_of_measure_quantity(std::uint32_t value) { unit_of_measure_quantity_ = value; }

TradingCollarVariationType ComplexInstrumentDefinitionMessage::trading_collar_variation_type() const { return trading_collar_variation_type_; }
void ComplexInstrumentDefinitionMessage::set_trading_collar_variation_type(TradingCollarVariationType value) { trading_collar_variation_type_ = value; }

Decimal ComplexInstrumentDefinitionMessage::trading_collar_variation() const { return trading_collar_variation_; }
void ComplexInstrumentDefinitionMessage::set_trading_collar_variation(Decimal value) { trading_collar_variation_ = value; }

const std::array<std::byte, 16>& ComplexInstrumentDefinitionMessage::reserved_16() const { return reserved_16_; }
std::array<std::byte, 16>& ComplexInstrumentDefinitionMessage::reserved_16() { return reserved_16_; }
void ComplexInstrumentDefinitionMessage::set_reserved_16(const std::array<std::byte, 16>& value) { reserved_16_ = value; }

std::uint8_t ComplexInstrumentDefinitionMessage::number_of_legs() const { return number_of_legs_; }
void ComplexInstrumentDefinitionMessage::set_number_of_legs(std::uint8_t value) { number_of_legs_ = value; }

const std::vector<InstrumentLeg>& ComplexInstrumentDefinitionMessage::instrument_leg() const { return instrument_leg_; }
std::vector<InstrumentLeg>& ComplexInstrumentDefinitionMessage::instrument_leg() { return instrument_leg_; }
void ComplexInstrumentDefinitionMessage::set_instrument_leg(const std::vector<InstrumentLeg>& value) { instrument_leg_ = value; }

DataCode ComplexInstrumentDefinitionMessage::type() const { return message_type; }

std::string_view ComplexInstrumentDefinitionMessage::name() const { return "Complex Instrument Definition Message"; }

std::size_t ComplexInstrumentDefinitionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 8, length);
    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 4, length);
    strategy_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 1, length);
    underlying_asset_type_ = static_cast<UnderlyingAssetType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 4, length);
    underlying_asset_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 6, length);
    product_group_code_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 1, length);
    spread_type_ = wire::read_char(data + offset);
    offset += 1;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 4, length);
    exchange_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 1, length);
    instrument_id_source_ = static_cast<InstrumentIdSource>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 1, length);
    instrument_type_ = static_cast<InstrumentType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 1, length);
    currency_ = static_cast<Currency>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 1, length);
    settlement_currency_ = static_cast<SettlementCurrency>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 1, length);
    match_algorithm_ = static_cast<MatchAlgorithm>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 4, length);
    minimum_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 4, length);
    maximum_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 8, length);
    tick_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 5, length);
    unit_of_measure_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 4, length);
    unit_of_measure_quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 1, length);
    trading_collar_variation_type_ = static_cast<TradingCollarVariationType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 8, length);
    trading_collar_variation_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 16, length);
    wire::read_bytes(data + offset, reserved_16_.data(), 16);
    offset += 16;

    wire::require("ComplexInstrumentDefinitionMessage", offset + 1, length);
    number_of_legs_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(number_of_legs_);
        instrument_leg_.clear();
        instrument_leg_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            InstrumentLeg entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            instrument_leg_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t ComplexInstrumentDefinitionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexInstrumentDefinitionMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto number_of_legs = number_of_legs_;
    number_of_legs = static_cast<std::uint8_t>(instrument_leg_.size());

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(underlying_asset_type_));
    offset += 1;

    wire::write_text(data + offset, 4, ' ', underlying_asset_);
    offset += 4;

    wire::write_text(data + offset, 6, ' ', product_group_code_);
    offset += 6;

    wire::write_char(data + offset, spread_type_);
    offset += 1;

    wire::write_text(data + offset, 4, ' ', exchange_);
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(instrument_id_source_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(instrument_type_));
    offset += 1;

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

    wire::write_char(data + offset, static_cast<char>(trading_collar_variation_type_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(trading_collar_variation_.mantissa()));
    offset += 8;

    wire::write_bytes(data + offset, reserved_16_.data(), 16);
    offset += 16;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_legs));
    offset += 1;

    for (const auto& entry : instrument_leg_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t ComplexInstrumentDefinitionMessage::encoded_size() const {
    return 8 + 4 + 1 + 4 + 6 + 1 + 4 + 1 + 1 + 1 + 1 + 1 + 4 + 4 + 8 + 5 + 4 + 1 + 8 + 16 + 1 + wire::encoded_size_of(instrument_leg_);
}

void ComplexInstrumentDefinitionMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> ComplexInstrumentDefinitionMessage::clone() const {
    return std::make_unique<ComplexInstrumentDefinitionMessage>(*this);
}

void ComplexInstrumentDefinitionMessage::print(std::ostream& out) const {
    out << "ComplexInstrumentDefinitionMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", underlying_asset_type=";
    out << underlying_asset_type_;
    out << ", underlying_asset=";
    print::text(out, underlying_asset_);
    out << ", product_group_code=";
    print::text(out, product_group_code_);
    out << ", spread_type=";
    print::character(out, spread_type_);
    out << ", exchange=";
    print::text(out, exchange_);
    out << ", instrument_id_source=";
    out << instrument_id_source_;
    out << ", instrument_type=";
    out << instrument_type_;
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
    out << ", trading_collar_variation_type=";
    out << trading_collar_variation_type_;
    out << ", trading_collar_variation=";
    out << trading_collar_variation_;
    out << ", reserved_16=";
    print::hex(out, reserved_16_.data(), reserved_16_.size());
    out << ", number_of_legs=";
    out << static_cast<int>(number_of_legs_);
    out << ", instrument_leg=";
    print::sequence(out, instrument_leg_);
    out << '}';
}

bool ComplexInstrumentDefinitionMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const ComplexInstrumentDefinitionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ComplexInstrumentDefinitionMessage::operator==(const ComplexInstrumentDefinitionMessage& other) const {
    return timestamp_ == other.timestamp_
        && strategy_id_ == other.strategy_id_
        && underlying_asset_type_ == other.underlying_asset_type_
        && underlying_asset_ == other.underlying_asset_
        && product_group_code_ == other.product_group_code_
        && spread_type_ == other.spread_type_
        && exchange_ == other.exchange_
        && instrument_id_source_ == other.instrument_id_source_
        && instrument_type_ == other.instrument_type_
        && currency_ == other.currency_
        && settlement_currency_ == other.settlement_currency_
        && match_algorithm_ == other.match_algorithm_
        && minimum_size_ == other.minimum_size_
        && maximum_size_ == other.maximum_size_
        && tick_ == other.tick_
        && unit_of_measure_ == other.unit_of_measure_
        && unit_of_measure_quantity_ == other.unit_of_measure_quantity_
        && trading_collar_variation_type_ == other.trading_collar_variation_type_
        && trading_collar_variation_ == other.trading_collar_variation_
        && reserved_16_ == other.reserved_16_
        && number_of_legs_ == other.number_of_legs_
        && instrument_leg_ == other.instrument_leg_;
}

bool ComplexInstrumentDefinitionMessage::operator!=(const ComplexInstrumentDefinitionMessage& other) const {
    return !(*this == other);
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
