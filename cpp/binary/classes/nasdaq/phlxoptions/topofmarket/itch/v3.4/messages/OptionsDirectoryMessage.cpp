#include "OptionsDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

OptionsDirectoryMessage::OptionsDirectoryMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, const std::string& security_symbol, std::uint8_t expiration_year, std::uint8_t expiration_month, std::uint8_t expiration_day, Decimal strike_price, OptionType option_type, std::uint8_t source, const std::string& underlying_symbol, OptionClosingType option_closing_type, Tradable tradable, Mpv mpv)
  : nanoseconds_(nanoseconds), option_id_(option_id), security_symbol_(security_symbol), expiration_year_(expiration_year), expiration_month_(expiration_month), expiration_day_(expiration_day), strike_price_(strike_price), option_type_(option_type), source_(source), underlying_symbol_(underlying_symbol), option_closing_type_(option_closing_type), tradable_(tradable), mpv_(mpv) {}

std::chrono::nanoseconds OptionsDirectoryMessage::nanoseconds() const { return nanoseconds_; }
void OptionsDirectoryMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t OptionsDirectoryMessage::option_id() const { return option_id_; }
void OptionsDirectoryMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

const std::string& OptionsDirectoryMessage::security_symbol() const { return security_symbol_; }
std::string& OptionsDirectoryMessage::security_symbol() { return security_symbol_; }
void OptionsDirectoryMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

std::uint8_t OptionsDirectoryMessage::expiration_year() const { return expiration_year_; }
void OptionsDirectoryMessage::set_expiration_year(std::uint8_t value) { expiration_year_ = value; }

std::uint8_t OptionsDirectoryMessage::expiration_month() const { return expiration_month_; }
void OptionsDirectoryMessage::set_expiration_month(std::uint8_t value) { expiration_month_ = value; }

std::uint8_t OptionsDirectoryMessage::expiration_day() const { return expiration_day_; }
void OptionsDirectoryMessage::set_expiration_day(std::uint8_t value) { expiration_day_ = value; }

Decimal OptionsDirectoryMessage::strike_price() const { return strike_price_; }
void OptionsDirectoryMessage::set_strike_price(Decimal value) { strike_price_ = value; }

OptionType OptionsDirectoryMessage::option_type() const { return option_type_; }
void OptionsDirectoryMessage::set_option_type(OptionType value) { option_type_ = value; }

std::uint8_t OptionsDirectoryMessage::source() const { return source_; }
void OptionsDirectoryMessage::set_source(std::uint8_t value) { source_ = value; }

const std::string& OptionsDirectoryMessage::underlying_symbol() const { return underlying_symbol_; }
std::string& OptionsDirectoryMessage::underlying_symbol() { return underlying_symbol_; }
void OptionsDirectoryMessage::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

OptionClosingType OptionsDirectoryMessage::option_closing_type() const { return option_closing_type_; }
void OptionsDirectoryMessage::set_option_closing_type(OptionClosingType value) { option_closing_type_ = value; }

Tradable OptionsDirectoryMessage::tradable() const { return tradable_; }
void OptionsDirectoryMessage::set_tradable(Tradable value) { tradable_ = value; }

Mpv OptionsDirectoryMessage::mpv() const { return mpv_; }
void OptionsDirectoryMessage::set_mpv(Mpv value) { mpv_ = value; }

SequencedMessageCode OptionsDirectoryMessage::type() const { return message_type; }

std::string_view OptionsDirectoryMessage::name() const { return "Options Directory Message"; }

std::size_t OptionsDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsDirectoryMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    security_symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    expiration_year_ = wire::read_u8(data + offset);
    offset += 1;

    expiration_month_ = wire::read_u8(data + offset);
    offset += 1;

    expiration_day_ = wire::read_u8(data + offset);
    offset += 1;

    strike_price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), -4);
    offset += 4;

    option_type_ = static_cast<OptionType>(wire::read_char(data + offset));
    offset += 1;

    source_ = wire::read_u8(data + offset);
    offset += 1;

    underlying_symbol_ = wire::read_text(data + offset, 13, ' ');
    offset += 13;

    option_closing_type_ = static_cast<OptionClosingType>(wire::read_char(data + offset));
    offset += 1;

    tradable_ = static_cast<Tradable>(wire::read_char(data + offset));
    offset += 1;

    mpv_ = static_cast<Mpv>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OptionsDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsDirectoryMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', security_symbol_);
    offset += 6;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(expiration_year_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(expiration_month_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(expiration_day_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(strike_price_.mantissa()));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(option_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(source_));
    offset += 1;

    wire::write_text(data + offset, 13, ' ', underlying_symbol_);
    offset += 13;

    wire::write_char(data + offset, static_cast<char>(option_closing_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(tradable_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(mpv_));
    offset += 1;

    return offset;
}

std::size_t OptionsDirectoryMessage::encoded_size() const {
    return wire_size;
}

void OptionsDirectoryMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> OptionsDirectoryMessage::clone() const {
    return std::make_unique<OptionsDirectoryMessage>(*this);
}

void OptionsDirectoryMessage::print(std::ostream& out) const {
    out << "OptionsDirectoryMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", security_symbol=";
    print::text(out, security_symbol_);
    out << ", expiration_year=";
    out << static_cast<int>(expiration_year_);
    out << ", expiration_month=";
    out << static_cast<int>(expiration_month_);
    out << ", expiration_day=";
    out << static_cast<int>(expiration_day_);
    out << ", strike_price=";
    out << strike_price_;
    out << ", option_type=";
    out << option_type_;
    out << ", source=";
    out << static_cast<int>(source_);
    out << ", underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << ", option_closing_type=";
    out << option_closing_type_;
    out << ", tradable=";
    out << tradable_;
    out << ", mpv=";
    out << mpv_;
    out << '}';
}

bool OptionsDirectoryMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const OptionsDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsDirectoryMessage::operator==(const OptionsDirectoryMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && option_id_ == other.option_id_
        && security_symbol_ == other.security_symbol_
        && expiration_year_ == other.expiration_year_
        && expiration_month_ == other.expiration_month_
        && expiration_day_ == other.expiration_day_
        && strike_price_ == other.strike_price_
        && option_type_ == other.option_type_
        && source_ == other.source_
        && underlying_symbol_ == other.underlying_symbol_
        && option_closing_type_ == other.option_closing_type_
        && tradable_ == other.tradable_
        && mpv_ == other.mpv_;
}

bool OptionsDirectoryMessage::operator!=(const OptionsDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
