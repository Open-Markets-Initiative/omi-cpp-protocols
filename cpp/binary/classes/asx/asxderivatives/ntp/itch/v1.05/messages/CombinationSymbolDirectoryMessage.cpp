#include "CombinationSymbolDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

CombinationSymbolDirectoryMessage::CombinationSymbolDirectoryMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, const std::string& symbol_name, const std::string& long_name, const std::string& cfi_code, PriceMethod price_method, std::uint8_t price_display_decimals, std::uint32_t price_fractional_denominator, std::uint32_t price_minimum_tick, std::uint8_t legs, const std::array<CombinationLeg, 6>& combination_leg)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), symbol_name_(symbol_name), long_name_(long_name), cfi_code_(cfi_code), price_method_(price_method), price_display_decimals_(price_display_decimals), price_fractional_denominator_(price_fractional_denominator), price_minimum_tick_(price_minimum_tick), legs_(legs), combination_leg_(combination_leg) {}

std::chrono::nanoseconds CombinationSymbolDirectoryMessage::nanoseconds() const { return nanoseconds_; }
void CombinationSymbolDirectoryMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t CombinationSymbolDirectoryMessage::trade_date() const { return trade_date_; }
void CombinationSymbolDirectoryMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t CombinationSymbolDirectoryMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void CombinationSymbolDirectoryMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

const std::string& CombinationSymbolDirectoryMessage::symbol_name() const { return symbol_name_; }
std::string& CombinationSymbolDirectoryMessage::symbol_name() { return symbol_name_; }
void CombinationSymbolDirectoryMessage::set_symbol_name(const std::string& value) { symbol_name_ = value; }

const std::string& CombinationSymbolDirectoryMessage::long_name() const { return long_name_; }
std::string& CombinationSymbolDirectoryMessage::long_name() { return long_name_; }
void CombinationSymbolDirectoryMessage::set_long_name(const std::string& value) { long_name_ = value; }

const std::string& CombinationSymbolDirectoryMessage::cfi_code() const { return cfi_code_; }
std::string& CombinationSymbolDirectoryMessage::cfi_code() { return cfi_code_; }
void CombinationSymbolDirectoryMessage::set_cfi_code(const std::string& value) { cfi_code_ = value; }

PriceMethod CombinationSymbolDirectoryMessage::price_method() const { return price_method_; }
void CombinationSymbolDirectoryMessage::set_price_method(PriceMethod value) { price_method_ = value; }

std::uint8_t CombinationSymbolDirectoryMessage::price_display_decimals() const { return price_display_decimals_; }
void CombinationSymbolDirectoryMessage::set_price_display_decimals(std::uint8_t value) { price_display_decimals_ = value; }

std::uint32_t CombinationSymbolDirectoryMessage::price_fractional_denominator() const { return price_fractional_denominator_; }
void CombinationSymbolDirectoryMessage::set_price_fractional_denominator(std::uint32_t value) { price_fractional_denominator_ = value; }

std::uint32_t CombinationSymbolDirectoryMessage::price_minimum_tick() const { return price_minimum_tick_; }
void CombinationSymbolDirectoryMessage::set_price_minimum_tick(std::uint32_t value) { price_minimum_tick_ = value; }

std::uint8_t CombinationSymbolDirectoryMessage::legs() const { return legs_; }
void CombinationSymbolDirectoryMessage::set_legs(std::uint8_t value) { legs_ = value; }

const std::array<CombinationLeg, 6>& CombinationSymbolDirectoryMessage::combination_leg() const { return combination_leg_; }
std::array<CombinationLeg, 6>& CombinationSymbolDirectoryMessage::combination_leg() { return combination_leg_; }
void CombinationSymbolDirectoryMessage::set_combination_leg(const std::array<CombinationLeg, 6>& value) { combination_leg_ = value; }

MessageCode CombinationSymbolDirectoryMessage::type() const { return message_type; }

std::string_view CombinationSymbolDirectoryMessage::name() const { return "Combination Symbol Directory Message"; }

std::size_t CombinationSymbolDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CombinationSymbolDirectoryMessage", wire_size, length);

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

    cfi_code_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    price_method_ = static_cast<PriceMethod>(wire::read_u8(data + offset));
    offset += 1;

    price_display_decimals_ = wire::read_u8(data + offset);
    offset += 1;

    price_fractional_denominator_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_minimum_tick_ = wire::read_u32_be(data + offset);
    offset += 4;

    legs_ = wire::read_u8(data + offset);
    offset += 1;

    for (std::size_t index = 0; index < combination_leg_.size(); ++index) {
        offset += combination_leg_[index].decode(data + offset, length - offset);
    }

    return offset;
}

std::size_t CombinationSymbolDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CombinationSymbolDirectoryMessage", wire_size, capacity);

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

    wire::write_text(data + offset, 6, ' ', cfi_code_);
    offset += 6;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_method_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_display_decimals_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_fractional_denominator_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_minimum_tick_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(legs_));
    offset += 1;

    for (const auto& entry : combination_leg_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t CombinationSymbolDirectoryMessage::encoded_size() const {
    return wire_size;
}

void CombinationSymbolDirectoryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> CombinationSymbolDirectoryMessage::clone() const {
    return std::make_unique<CombinationSymbolDirectoryMessage>(*this);
}

void CombinationSymbolDirectoryMessage::print(std::ostream& out) const {
    out << "CombinationSymbolDirectoryMessage{";
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
    out << ", cfi_code=";
    print::text(out, cfi_code_);
    out << ", price_method=";
    out << price_method_;
    out << ", price_display_decimals=";
    out << static_cast<int>(price_display_decimals_);
    out << ", price_fractional_denominator=";
    out << price_fractional_denominator_;
    out << ", price_minimum_tick=";
    out << price_minimum_tick_;
    out << ", legs=";
    out << static_cast<int>(legs_);
    out << ", combination_leg=";
    print::sequence(out, combination_leg_);
    out << '}';
}

bool CombinationSymbolDirectoryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const CombinationSymbolDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool CombinationSymbolDirectoryMessage::operator==(const CombinationSymbolDirectoryMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && symbol_name_ == other.symbol_name_
        && long_name_ == other.long_name_
        && cfi_code_ == other.cfi_code_
        && price_method_ == other.price_method_
        && price_display_decimals_ == other.price_display_decimals_
        && price_fractional_denominator_ == other.price_fractional_denominator_
        && price_minimum_tick_ == other.price_minimum_tick_
        && legs_ == other.legs_
        && combination_leg_ == other.combination_leg_;
}

bool CombinationSymbolDirectoryMessage::operator!=(const CombinationSymbolDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
