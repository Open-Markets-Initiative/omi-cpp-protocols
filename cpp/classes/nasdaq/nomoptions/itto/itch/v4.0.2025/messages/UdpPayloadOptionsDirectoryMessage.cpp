#include "UdpPayloadOptionsDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadOptionsDirectoryMessage::UdpPayloadOptionsDirectoryMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint32_t option_id, const std::string& security_symbol, std::uint8_t expiration_year, std::uint8_t expiration_month, std::uint8_t expiration_date, Decimal explicit_strike_price, OptionType option_type, std::uint8_t source, const std::string& underlying_symbol, OptionsClosingType options_closing_type, Tradable tradable, Mpv mpv)
  : tracking_number_(tracking_number), timestamp_(timestamp), option_id_(option_id), security_symbol_(security_symbol), expiration_year_(expiration_year), expiration_month_(expiration_month), expiration_date_(expiration_date), explicit_strike_price_(explicit_strike_price), option_type_(option_type), source_(source), underlying_symbol_(underlying_symbol), options_closing_type_(options_closing_type), tradable_(tradable), mpv_(mpv) {}

std::uint16_t UdpPayloadOptionsDirectoryMessage::tracking_number() const { return tracking_number_; }
void UdpPayloadOptionsDirectoryMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadOptionsDirectoryMessage::timestamp() const { return timestamp_; }
void UdpPayloadOptionsDirectoryMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint32_t UdpPayloadOptionsDirectoryMessage::option_id() const { return option_id_; }
void UdpPayloadOptionsDirectoryMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

const std::string& UdpPayloadOptionsDirectoryMessage::security_symbol() const { return security_symbol_; }
std::string& UdpPayloadOptionsDirectoryMessage::security_symbol() { return security_symbol_; }
void UdpPayloadOptionsDirectoryMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

std::uint8_t UdpPayloadOptionsDirectoryMessage::expiration_year() const { return expiration_year_; }
void UdpPayloadOptionsDirectoryMessage::set_expiration_year(std::uint8_t value) { expiration_year_ = value; }

std::uint8_t UdpPayloadOptionsDirectoryMessage::expiration_month() const { return expiration_month_; }
void UdpPayloadOptionsDirectoryMessage::set_expiration_month(std::uint8_t value) { expiration_month_ = value; }

std::uint8_t UdpPayloadOptionsDirectoryMessage::expiration_date() const { return expiration_date_; }
void UdpPayloadOptionsDirectoryMessage::set_expiration_date(std::uint8_t value) { expiration_date_ = value; }

Decimal UdpPayloadOptionsDirectoryMessage::explicit_strike_price() const { return explicit_strike_price_; }
void UdpPayloadOptionsDirectoryMessage::set_explicit_strike_price(Decimal value) { explicit_strike_price_ = value; }

OptionType UdpPayloadOptionsDirectoryMessage::option_type() const { return option_type_; }
void UdpPayloadOptionsDirectoryMessage::set_option_type(OptionType value) { option_type_ = value; }

std::uint8_t UdpPayloadOptionsDirectoryMessage::source() const { return source_; }
void UdpPayloadOptionsDirectoryMessage::set_source(std::uint8_t value) { source_ = value; }

const std::string& UdpPayloadOptionsDirectoryMessage::underlying_symbol() const { return underlying_symbol_; }
std::string& UdpPayloadOptionsDirectoryMessage::underlying_symbol() { return underlying_symbol_; }
void UdpPayloadOptionsDirectoryMessage::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

OptionsClosingType UdpPayloadOptionsDirectoryMessage::options_closing_type() const { return options_closing_type_; }
void UdpPayloadOptionsDirectoryMessage::set_options_closing_type(OptionsClosingType value) { options_closing_type_ = value; }

Tradable UdpPayloadOptionsDirectoryMessage::tradable() const { return tradable_; }
void UdpPayloadOptionsDirectoryMessage::set_tradable(Tradable value) { tradable_ = value; }

Mpv UdpPayloadOptionsDirectoryMessage::mpv() const { return mpv_; }
void UdpPayloadOptionsDirectoryMessage::set_mpv(Mpv value) { mpv_ = value; }

PacketMessageCode UdpPayloadOptionsDirectoryMessage::type() const { return message_type; }

std::string_view UdpPayloadOptionsDirectoryMessage::name() const { return "Options Directory Message"; }

std::size_t UdpPayloadOptionsDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadOptionsDirectoryMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    security_symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    expiration_year_ = wire::read_u8(data + offset);
    offset += 1;

    expiration_month_ = wire::read_u8(data + offset);
    offset += 1;

    expiration_date_ = wire::read_u8(data + offset);
    offset += 1;

    explicit_strike_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    option_type_ = static_cast<OptionType>(wire::read_char(data + offset));
    offset += 1;

    source_ = wire::read_u8(data + offset);
    offset += 1;

    underlying_symbol_ = wire::read_text(data + offset, 13, ' ');
    offset += 13;

    options_closing_type_ = static_cast<OptionsClosingType>(wire::read_char(data + offset));
    offset += 1;

    tradable_ = static_cast<Tradable>(wire::read_char(data + offset));
    offset += 1;

    mpv_ = static_cast<Mpv>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t UdpPayloadOptionsDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadOptionsDirectoryMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', security_symbol_);
    offset += 6;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(expiration_year_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(expiration_month_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(expiration_date_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(explicit_strike_price_.mantissa()));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(option_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(source_));
    offset += 1;

    wire::write_text(data + offset, 13, ' ', underlying_symbol_);
    offset += 13;

    wire::write_char(data + offset, static_cast<char>(options_closing_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(tradable_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(mpv_));
    offset += 1;

    return offset;
}

std::size_t UdpPayloadOptionsDirectoryMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadOptionsDirectoryMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadOptionsDirectoryMessage::clone() const {
    return std::make_unique<UdpPayloadOptionsDirectoryMessage>(*this);
}

void UdpPayloadOptionsDirectoryMessage::print(std::ostream& out) const {
    out << "UdpPayloadOptionsDirectoryMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", security_symbol=";
    print::text(out, security_symbol_);
    out << ", expiration_year=";
    out << static_cast<int>(expiration_year_);
    out << ", expiration_month=";
    out << static_cast<int>(expiration_month_);
    out << ", expiration_date=";
    out << static_cast<int>(expiration_date_);
    out << ", explicit_strike_price=";
    out << explicit_strike_price_;
    out << ", option_type=";
    out << option_type_;
    out << ", source=";
    out << static_cast<int>(source_);
    out << ", underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << ", options_closing_type=";
    out << options_closing_type_;
    out << ", tradable=";
    out << tradable_;
    out << ", mpv=";
    out << mpv_;
    out << '}';
}

bool UdpPayloadOptionsDirectoryMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadOptionsDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadOptionsDirectoryMessage::operator==(const UdpPayloadOptionsDirectoryMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && option_id_ == other.option_id_
        && security_symbol_ == other.security_symbol_
        && expiration_year_ == other.expiration_year_
        && expiration_month_ == other.expiration_month_
        && expiration_date_ == other.expiration_date_
        && explicit_strike_price_ == other.explicit_strike_price_
        && option_type_ == other.option_type_
        && source_ == other.source_
        && underlying_symbol_ == other.underlying_symbol_
        && options_closing_type_ == other.options_closing_type_
        && tradable_ == other.tradable_
        && mpv_ == other.mpv_;
}

bool UdpPayloadOptionsDirectoryMessage::operator!=(const UdpPayloadOptionsDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
