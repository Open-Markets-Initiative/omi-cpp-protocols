#include "SecurityDefinitionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

SecurityDefinitionMessage::SecurityDefinitionMessage(const SecurityType& security_type, SecurityExchange security_exchange, const Symbol& symbol, const TargetLocationId& target_location_id, std::uint32_t class_key, std::uint32_t security_id, std::uint64_t maturity_date, std::uint8_t price_type, const StrikePrice& strike_price, PutOrCall put_or_call, const MinimumStrikePriceFraction& minimum_strike_price_fraction, const MaxStrikePrice& max_strike_price, const PremiumBreakPoint& premium_break_point, const MinimumAbovePremiumFraction& minimum_above_premium_fraction, const MinimumBelowPremiumFraction& minimum_below_premium_fraction, ExerciseStyle exercise_style, const CurrencyCode& currency_code, const UnderlyingSymbol& underlying_symbol, const UnderlyingType& underlying_type, std::uint32_t contract_size, std::uint8_t no_legs, const std::vector<SecurityDefinitionLeg>& security_definition_leg)
  : security_type_(security_type), security_exchange_(security_exchange), symbol_(symbol), target_location_id_(target_location_id), class_key_(class_key), security_id_(security_id), maturity_date_(maturity_date), price_type_(price_type), strike_price_(strike_price), put_or_call_(put_or_call), minimum_strike_price_fraction_(minimum_strike_price_fraction), max_strike_price_(max_strike_price), premium_break_point_(premium_break_point), minimum_above_premium_fraction_(minimum_above_premium_fraction), minimum_below_premium_fraction_(minimum_below_premium_fraction), exercise_style_(exercise_style), currency_code_(currency_code), underlying_symbol_(underlying_symbol), underlying_type_(underlying_type), contract_size_(contract_size), no_legs_(no_legs), security_definition_leg_(security_definition_leg) {}

const SecurityType& SecurityDefinitionMessage::security_type() const { return security_type_; }
SecurityType& SecurityDefinitionMessage::security_type() { return security_type_; }
void SecurityDefinitionMessage::set_security_type(const SecurityType& value) { security_type_ = value; }

SecurityExchange SecurityDefinitionMessage::security_exchange() const { return security_exchange_; }
void SecurityDefinitionMessage::set_security_exchange(SecurityExchange value) { security_exchange_ = value; }

const Symbol& SecurityDefinitionMessage::symbol() const { return symbol_; }
Symbol& SecurityDefinitionMessage::symbol() { return symbol_; }
void SecurityDefinitionMessage::set_symbol(const Symbol& value) { symbol_ = value; }

const TargetLocationId& SecurityDefinitionMessage::target_location_id() const { return target_location_id_; }
TargetLocationId& SecurityDefinitionMessage::target_location_id() { return target_location_id_; }
void SecurityDefinitionMessage::set_target_location_id(const TargetLocationId& value) { target_location_id_ = value; }

std::uint32_t SecurityDefinitionMessage::class_key() const { return class_key_; }
void SecurityDefinitionMessage::set_class_key(std::uint32_t value) { class_key_ = value; }

std::uint32_t SecurityDefinitionMessage::security_id() const { return security_id_; }
void SecurityDefinitionMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

std::uint64_t SecurityDefinitionMessage::maturity_date() const { return maturity_date_; }
void SecurityDefinitionMessage::set_maturity_date(std::uint64_t value) { maturity_date_ = value; }

std::uint8_t SecurityDefinitionMessage::price_type() const { return price_type_; }
void SecurityDefinitionMessage::set_price_type(std::uint8_t value) { price_type_ = value; }

const StrikePrice& SecurityDefinitionMessage::strike_price() const { return strike_price_; }
StrikePrice& SecurityDefinitionMessage::strike_price() { return strike_price_; }
void SecurityDefinitionMessage::set_strike_price(const StrikePrice& value) { strike_price_ = value; }

PutOrCall SecurityDefinitionMessage::put_or_call() const { return put_or_call_; }
void SecurityDefinitionMessage::set_put_or_call(PutOrCall value) { put_or_call_ = value; }

const MinimumStrikePriceFraction& SecurityDefinitionMessage::minimum_strike_price_fraction() const { return minimum_strike_price_fraction_; }
MinimumStrikePriceFraction& SecurityDefinitionMessage::minimum_strike_price_fraction() { return minimum_strike_price_fraction_; }
void SecurityDefinitionMessage::set_minimum_strike_price_fraction(const MinimumStrikePriceFraction& value) { minimum_strike_price_fraction_ = value; }

const MaxStrikePrice& SecurityDefinitionMessage::max_strike_price() const { return max_strike_price_; }
MaxStrikePrice& SecurityDefinitionMessage::max_strike_price() { return max_strike_price_; }
void SecurityDefinitionMessage::set_max_strike_price(const MaxStrikePrice& value) { max_strike_price_ = value; }

const PremiumBreakPoint& SecurityDefinitionMessage::premium_break_point() const { return premium_break_point_; }
PremiumBreakPoint& SecurityDefinitionMessage::premium_break_point() { return premium_break_point_; }
void SecurityDefinitionMessage::set_premium_break_point(const PremiumBreakPoint& value) { premium_break_point_ = value; }

const MinimumAbovePremiumFraction& SecurityDefinitionMessage::minimum_above_premium_fraction() const { return minimum_above_premium_fraction_; }
MinimumAbovePremiumFraction& SecurityDefinitionMessage::minimum_above_premium_fraction() { return minimum_above_premium_fraction_; }
void SecurityDefinitionMessage::set_minimum_above_premium_fraction(const MinimumAbovePremiumFraction& value) { minimum_above_premium_fraction_ = value; }

const MinimumBelowPremiumFraction& SecurityDefinitionMessage::minimum_below_premium_fraction() const { return minimum_below_premium_fraction_; }
MinimumBelowPremiumFraction& SecurityDefinitionMessage::minimum_below_premium_fraction() { return minimum_below_premium_fraction_; }
void SecurityDefinitionMessage::set_minimum_below_premium_fraction(const MinimumBelowPremiumFraction& value) { minimum_below_premium_fraction_ = value; }

ExerciseStyle SecurityDefinitionMessage::exercise_style() const { return exercise_style_; }
void SecurityDefinitionMessage::set_exercise_style(ExerciseStyle value) { exercise_style_ = value; }

const CurrencyCode& SecurityDefinitionMessage::currency_code() const { return currency_code_; }
CurrencyCode& SecurityDefinitionMessage::currency_code() { return currency_code_; }
void SecurityDefinitionMessage::set_currency_code(const CurrencyCode& value) { currency_code_ = value; }

const UnderlyingSymbol& SecurityDefinitionMessage::underlying_symbol() const { return underlying_symbol_; }
UnderlyingSymbol& SecurityDefinitionMessage::underlying_symbol() { return underlying_symbol_; }
void SecurityDefinitionMessage::set_underlying_symbol(const UnderlyingSymbol& value) { underlying_symbol_ = value; }

const UnderlyingType& SecurityDefinitionMessage::underlying_type() const { return underlying_type_; }
UnderlyingType& SecurityDefinitionMessage::underlying_type() { return underlying_type_; }
void SecurityDefinitionMessage::set_underlying_type(const UnderlyingType& value) { underlying_type_ = value; }

std::uint32_t SecurityDefinitionMessage::contract_size() const { return contract_size_; }
void SecurityDefinitionMessage::set_contract_size(std::uint32_t value) { contract_size_ = value; }

std::uint8_t SecurityDefinitionMessage::no_legs() const { return no_legs_; }
void SecurityDefinitionMessage::set_no_legs(std::uint8_t value) { no_legs_ = value; }

const std::vector<SecurityDefinitionLeg>& SecurityDefinitionMessage::security_definition_leg() const { return security_definition_leg_; }
std::vector<SecurityDefinitionLeg>& SecurityDefinitionMessage::security_definition_leg() { return security_definition_leg_; }
void SecurityDefinitionMessage::set_security_definition_leg(const std::vector<SecurityDefinitionLeg>& value) { security_definition_leg_ = value; }

MessageCode SecurityDefinitionMessage::type() const { return message_type; }

std::string_view SecurityDefinitionMessage::name() const { return "Security Definition Message"; }

std::size_t SecurityDefinitionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += security_type_.decode(data + offset, length - offset);

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    security_exchange_ = static_cast<SecurityExchange>(wire::read_char(data + offset));
    offset += 1;

    offset += symbol_.decode(data + offset, length - offset);

    offset += target_location_id_.decode(data + offset, length - offset);

    wire::require("SecurityDefinitionMessage", offset + 4, length);
    class_key_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("SecurityDefinitionMessage", offset + 4, length);
    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    maturity_date_ = wire::read_u64_be(data + offset);
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    price_type_ = wire::read_u8(data + offset);
    offset += 1;

    offset += strike_price_.decode(data + offset, length - offset);

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    put_or_call_ = static_cast<PutOrCall>(wire::read_u8(data + offset));
    offset += 1;

    offset += minimum_strike_price_fraction_.decode(data + offset, length - offset);

    offset += max_strike_price_.decode(data + offset, length - offset);

    offset += premium_break_point_.decode(data + offset, length - offset);

    offset += minimum_above_premium_fraction_.decode(data + offset, length - offset);

    offset += minimum_below_premium_fraction_.decode(data + offset, length - offset);

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    exercise_style_ = static_cast<ExerciseStyle>(wire::read_u8(data + offset));
    offset += 1;

    offset += currency_code_.decode(data + offset, length - offset);

    offset += underlying_symbol_.decode(data + offset, length - offset);

    offset += underlying_type_.decode(data + offset, length - offset);

    wire::require("SecurityDefinitionMessage", offset + 4, length);
    contract_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    no_legs_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(no_legs_);
        security_definition_leg_.clear();
        security_definition_leg_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SecurityDefinitionLeg entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            security_definition_leg_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SecurityDefinitionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityDefinitionMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto no_legs = no_legs_;
    no_legs = static_cast<std::uint8_t>(security_definition_leg_.size());

    offset += security_type_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(security_exchange_));
    offset += 1;

    offset += symbol_.encode(data + offset, capacity - offset);

    offset += target_location_id_.encode(data + offset, capacity - offset);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(class_key_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(security_id_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(maturity_date_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_type_));
    offset += 1;

    offset += strike_price_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(put_or_call_));
    offset += 1;

    offset += minimum_strike_price_fraction_.encode(data + offset, capacity - offset);

    offset += max_strike_price_.encode(data + offset, capacity - offset);

    offset += premium_break_point_.encode(data + offset, capacity - offset);

    offset += minimum_above_premium_fraction_.encode(data + offset, capacity - offset);

    offset += minimum_below_premium_fraction_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(exercise_style_));
    offset += 1;

    offset += currency_code_.encode(data + offset, capacity - offset);

    offset += underlying_symbol_.encode(data + offset, capacity - offset);

    offset += underlying_type_.encode(data + offset, capacity - offset);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(contract_size_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(no_legs));
    offset += 1;

    for (const auto& entry : security_definition_leg_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SecurityDefinitionMessage::encoded_size() const {
    return security_type_.encoded_size() + 1 + symbol_.encoded_size() + target_location_id_.encoded_size() + 4 + 4 + 8 + 1 + strike_price_.encoded_size() + 1 + minimum_strike_price_fraction_.encoded_size() + max_strike_price_.encoded_size() + premium_break_point_.encoded_size() + minimum_above_premium_fraction_.encoded_size() + minimum_below_premium_fraction_.encoded_size() + 1 + currency_code_.encoded_size() + underlying_symbol_.encoded_size() + underlying_type_.encoded_size() + 4 + 1 + wire::encoded_size_of(security_definition_leg_);
}

void SecurityDefinitionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SecurityDefinitionMessage::clone() const {
    return std::make_unique<SecurityDefinitionMessage>(*this);
}

void SecurityDefinitionMessage::print(std::ostream& out) const {
    out << "SecurityDefinitionMessage{";
    out << "security_type=";
    security_type_.print(out);
    out << ", security_exchange=";
    out << security_exchange_;
    out << ", symbol=";
    symbol_.print(out);
    out << ", target_location_id=";
    target_location_id_.print(out);
    out << ", class_key=";
    out << class_key_;
    out << ", security_id=";
    out << security_id_;
    out << ", maturity_date=";
    out << maturity_date_;
    out << ", price_type=";
    out << static_cast<int>(price_type_);
    out << ", strike_price=";
    strike_price_.print(out);
    out << ", put_or_call=";
    out << put_or_call_;
    out << ", minimum_strike_price_fraction=";
    minimum_strike_price_fraction_.print(out);
    out << ", max_strike_price=";
    max_strike_price_.print(out);
    out << ", premium_break_point=";
    premium_break_point_.print(out);
    out << ", minimum_above_premium_fraction=";
    minimum_above_premium_fraction_.print(out);
    out << ", minimum_below_premium_fraction=";
    minimum_below_premium_fraction_.print(out);
    out << ", exercise_style=";
    out << exercise_style_;
    out << ", currency_code=";
    currency_code_.print(out);
    out << ", underlying_symbol=";
    underlying_symbol_.print(out);
    out << ", underlying_type=";
    underlying_type_.print(out);
    out << ", contract_size=";
    out << contract_size_;
    out << ", no_legs=";
    out << static_cast<int>(no_legs_);
    out << ", security_definition_leg=";
    print::sequence(out, security_definition_leg_);
    out << '}';
}

bool SecurityDefinitionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SecurityDefinitionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityDefinitionMessage::operator==(const SecurityDefinitionMessage& other) const {
    return security_type_ == other.security_type_
        && security_exchange_ == other.security_exchange_
        && symbol_ == other.symbol_
        && target_location_id_ == other.target_location_id_
        && class_key_ == other.class_key_
        && security_id_ == other.security_id_
        && maturity_date_ == other.maturity_date_
        && price_type_ == other.price_type_
        && strike_price_ == other.strike_price_
        && put_or_call_ == other.put_or_call_
        && minimum_strike_price_fraction_ == other.minimum_strike_price_fraction_
        && max_strike_price_ == other.max_strike_price_
        && premium_break_point_ == other.premium_break_point_
        && minimum_above_premium_fraction_ == other.minimum_above_premium_fraction_
        && minimum_below_premium_fraction_ == other.minimum_below_premium_fraction_
        && exercise_style_ == other.exercise_style_
        && currency_code_ == other.currency_code_
        && underlying_symbol_ == other.underlying_symbol_
        && underlying_type_ == other.underlying_type_
        && contract_size_ == other.contract_size_
        && no_legs_ == other.no_legs_
        && security_definition_leg_ == other.security_definition_leg_;
}

bool SecurityDefinitionMessage::operator!=(const SecurityDefinitionMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
