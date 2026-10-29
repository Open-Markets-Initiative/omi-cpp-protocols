#include "UnderlyingIndexMappingMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

UnderlyingIndexMappingMessage::UnderlyingIndexMappingMessage(std::uint32_t underlying_index, const std::string& underlying_symbol, std::uint8_t channel_id, MarketId market_id, std::uint8_t system_id, ExchangeCode exchange_code, std::uint8_t price_scale_code, SecurityType security_type, PriceResolution price_resolution, const std::array<std::byte, 1>& reserved_1)
  : underlying_index_(underlying_index), underlying_symbol_(underlying_symbol), channel_id_(channel_id), market_id_(market_id), system_id_(system_id), exchange_code_(exchange_code), price_scale_code_(price_scale_code), security_type_(security_type), price_resolution_(price_resolution), reserved_1_(reserved_1) {}

std::uint32_t UnderlyingIndexMappingMessage::underlying_index() const { return underlying_index_; }
void UnderlyingIndexMappingMessage::set_underlying_index(std::uint32_t value) { underlying_index_ = value; }

const std::string& UnderlyingIndexMappingMessage::underlying_symbol() const { return underlying_symbol_; }
std::string& UnderlyingIndexMappingMessage::underlying_symbol() { return underlying_symbol_; }
void UnderlyingIndexMappingMessage::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

std::uint8_t UnderlyingIndexMappingMessage::channel_id() const { return channel_id_; }
void UnderlyingIndexMappingMessage::set_channel_id(std::uint8_t value) { channel_id_ = value; }

MarketId UnderlyingIndexMappingMessage::market_id() const { return market_id_; }
void UnderlyingIndexMappingMessage::set_market_id(MarketId value) { market_id_ = value; }

std::uint8_t UnderlyingIndexMappingMessage::system_id() const { return system_id_; }
void UnderlyingIndexMappingMessage::set_system_id(std::uint8_t value) { system_id_ = value; }

ExchangeCode UnderlyingIndexMappingMessage::exchange_code() const { return exchange_code_; }
void UnderlyingIndexMappingMessage::set_exchange_code(ExchangeCode value) { exchange_code_ = value; }

std::uint8_t UnderlyingIndexMappingMessage::price_scale_code() const { return price_scale_code_; }
void UnderlyingIndexMappingMessage::set_price_scale_code(std::uint8_t value) { price_scale_code_ = value; }

SecurityType UnderlyingIndexMappingMessage::security_type() const { return security_type_; }
void UnderlyingIndexMappingMessage::set_security_type(SecurityType value) { security_type_ = value; }

PriceResolution UnderlyingIndexMappingMessage::price_resolution() const { return price_resolution_; }
void UnderlyingIndexMappingMessage::set_price_resolution(PriceResolution value) { price_resolution_ = value; }

const std::array<std::byte, 1>& UnderlyingIndexMappingMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& UnderlyingIndexMappingMessage::reserved_1() { return reserved_1_; }
void UnderlyingIndexMappingMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

MessageCode UnderlyingIndexMappingMessage::type() const { return message_type; }

std::string_view UnderlyingIndexMappingMessage::name() const { return "Underlying Index Mapping Message"; }

std::size_t UnderlyingIndexMappingMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UnderlyingIndexMappingMessage", wire_size, length);

    underlying_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    underlying_symbol_ = wire::read_text(data + offset, 11, '\0');
    offset += 11;

    channel_id_ = wire::read_u8(data + offset);
    offset += 1;

    market_id_ = static_cast<MarketId>(wire::read_u16_le(data + offset));
    offset += 2;

    system_id_ = wire::read_u8(data + offset);
    offset += 1;

    exchange_code_ = static_cast<ExchangeCode>(wire::read_char(data + offset));
    offset += 1;

    price_scale_code_ = wire::read_u8(data + offset);
    offset += 1;

    security_type_ = static_cast<SecurityType>(wire::read_char(data + offset));
    offset += 1;

    price_resolution_ = static_cast<PriceResolution>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t UnderlyingIndexMappingMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnderlyingIndexMappingMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(underlying_index_));
    offset += 4;

    wire::write_text(data + offset, 11, '\0', underlying_symbol_);
    offset += 11;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(channel_id_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(market_id_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(system_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(exchange_code_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_scale_code_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(security_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_resolution_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t UnderlyingIndexMappingMessage::encoded_size() const {
    return wire_size;
}

void UnderlyingIndexMappingMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> UnderlyingIndexMappingMessage::clone() const {
    return std::make_unique<UnderlyingIndexMappingMessage>(*this);
}

void UnderlyingIndexMappingMessage::print(std::ostream& out) const {
    out << "UnderlyingIndexMappingMessage{";
    out << "underlying_index=";
    out << underlying_index_;
    out << ", underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << ", channel_id=";
    out << static_cast<int>(channel_id_);
    out << ", market_id=";
    out << market_id_;
    out << ", system_id=";
    out << static_cast<int>(system_id_);
    out << ", exchange_code=";
    out << exchange_code_;
    out << ", price_scale_code=";
    out << static_cast<int>(price_scale_code_);
    out << ", security_type=";
    out << security_type_;
    out << ", price_resolution=";
    out << price_resolution_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << '}';
}

bool UnderlyingIndexMappingMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const UnderlyingIndexMappingMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnderlyingIndexMappingMessage::operator==(const UnderlyingIndexMappingMessage& other) const {
    return underlying_index_ == other.underlying_index_
        && underlying_symbol_ == other.underlying_symbol_
        && channel_id_ == other.channel_id_
        && market_id_ == other.market_id_
        && system_id_ == other.system_id_
        && exchange_code_ == other.exchange_code_
        && price_scale_code_ == other.price_scale_code_
        && security_type_ == other.security_type_
        && price_resolution_ == other.price_resolution_
        && reserved_1_ == other.reserved_1_;
}

bool UnderlyingIndexMappingMessage::operator!=(const UnderlyingIndexMappingMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
