#include "SymbolIndexMappingMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

SymbolIndexMappingMessage::SymbolIndexMappingMessage(std::uint32_t symbol_index, const std::string& symbol, const std::array<std::byte, 1>& reserved_1, MarketId market_id, std::uint8_t system_id, ExchangeCode exchange_code, std::uint8_t price_scale_code, SecurityType security_type, std::uint16_t lot_size, std::uint32_t prev_close_price, std::uint32_t prev_close_volume, PriceResolution price_resolution, RoundLot round_lot, std::uint16_t mpv, std::uint16_t unit_of_trade, const std::array<std::byte, 2>& reserved_2)
  : symbol_index_(symbol_index), symbol_(symbol), reserved_1_(reserved_1), market_id_(market_id), system_id_(system_id), exchange_code_(exchange_code), price_scale_code_(price_scale_code), security_type_(security_type), lot_size_(lot_size), prev_close_price_(prev_close_price), prev_close_volume_(prev_close_volume), price_resolution_(price_resolution), round_lot_(round_lot), mpv_(mpv), unit_of_trade_(unit_of_trade), reserved_2_(reserved_2) {}

std::uint32_t SymbolIndexMappingMessage::symbol_index() const { return symbol_index_; }
void SymbolIndexMappingMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

const std::string& SymbolIndexMappingMessage::symbol() const { return symbol_; }
std::string& SymbolIndexMappingMessage::symbol() { return symbol_; }
void SymbolIndexMappingMessage::set_symbol(const std::string& value) { symbol_ = value; }

const std::array<std::byte, 1>& SymbolIndexMappingMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& SymbolIndexMappingMessage::reserved_1() { return reserved_1_; }
void SymbolIndexMappingMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

MarketId SymbolIndexMappingMessage::market_id() const { return market_id_; }
void SymbolIndexMappingMessage::set_market_id(MarketId value) { market_id_ = value; }

std::uint8_t SymbolIndexMappingMessage::system_id() const { return system_id_; }
void SymbolIndexMappingMessage::set_system_id(std::uint8_t value) { system_id_ = value; }

ExchangeCode SymbolIndexMappingMessage::exchange_code() const { return exchange_code_; }
void SymbolIndexMappingMessage::set_exchange_code(ExchangeCode value) { exchange_code_ = value; }

std::uint8_t SymbolIndexMappingMessage::price_scale_code() const { return price_scale_code_; }
void SymbolIndexMappingMessage::set_price_scale_code(std::uint8_t value) { price_scale_code_ = value; }

SecurityType SymbolIndexMappingMessage::security_type() const { return security_type_; }
void SymbolIndexMappingMessage::set_security_type(SecurityType value) { security_type_ = value; }

std::uint16_t SymbolIndexMappingMessage::lot_size() const { return lot_size_; }
void SymbolIndexMappingMessage::set_lot_size(std::uint16_t value) { lot_size_ = value; }

std::uint32_t SymbolIndexMappingMessage::prev_close_price() const { return prev_close_price_; }
void SymbolIndexMappingMessage::set_prev_close_price(std::uint32_t value) { prev_close_price_ = value; }

std::uint32_t SymbolIndexMappingMessage::prev_close_volume() const { return prev_close_volume_; }
void SymbolIndexMappingMessage::set_prev_close_volume(std::uint32_t value) { prev_close_volume_ = value; }

PriceResolution SymbolIndexMappingMessage::price_resolution() const { return price_resolution_; }
void SymbolIndexMappingMessage::set_price_resolution(PriceResolution value) { price_resolution_ = value; }

RoundLot SymbolIndexMappingMessage::round_lot() const { return round_lot_; }
void SymbolIndexMappingMessage::set_round_lot(RoundLot value) { round_lot_ = value; }

std::uint16_t SymbolIndexMappingMessage::mpv() const { return mpv_; }
void SymbolIndexMappingMessage::set_mpv(std::uint16_t value) { mpv_ = value; }

std::uint16_t SymbolIndexMappingMessage::unit_of_trade() const { return unit_of_trade_; }
void SymbolIndexMappingMessage::set_unit_of_trade(std::uint16_t value) { unit_of_trade_ = value; }

const std::array<std::byte, 2>& SymbolIndexMappingMessage::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& SymbolIndexMappingMessage::reserved_2() { return reserved_2_; }
void SymbolIndexMappingMessage::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

MessageCode SymbolIndexMappingMessage::type() const { return message_type; }

std::string_view SymbolIndexMappingMessage::name() const { return "Symbol Index Mapping Message"; }

std::size_t SymbolIndexMappingMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolIndexMappingMessage", wire_size, length);

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_ = wire::read_text(data + offset, 11, '\0');
    offset += 11;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
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

    lot_size_ = wire::read_u16_le(data + offset);
    offset += 2;

    prev_close_price_ = wire::read_u32_le(data + offset);
    offset += 4;

    prev_close_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_resolution_ = static_cast<PriceResolution>(wire::read_u8(data + offset));
    offset += 1;

    round_lot_ = static_cast<RoundLot>(wire::read_char(data + offset));
    offset += 1;

    mpv_ = wire::read_u16_le(data + offset);
    offset += 2;

    unit_of_trade_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::read_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t SymbolIndexMappingMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolIndexMappingMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_text(data + offset, 11, '\0', symbol_);
    offset += 11;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
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

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(lot_size_));
    offset += 2;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(prev_close_price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(prev_close_volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_resolution_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(round_lot_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(mpv_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(unit_of_trade_));
    offset += 2;

    wire::write_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t SymbolIndexMappingMessage::encoded_size() const {
    return wire_size;
}

void SymbolIndexMappingMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SymbolIndexMappingMessage::clone() const {
    return std::make_unique<SymbolIndexMappingMessage>(*this);
}

void SymbolIndexMappingMessage::print(std::ostream& out) const {
    out << "SymbolIndexMappingMessage{";
    out << "symbol_index=";
    out << symbol_index_;
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
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
    out << ", lot_size=";
    out << lot_size_;
    out << ", prev_close_price=";
    out << prev_close_price_;
    out << ", prev_close_volume=";
    out << prev_close_volume_;
    out << ", price_resolution=";
    out << price_resolution_;
    out << ", round_lot=";
    out << round_lot_;
    out << ", mpv=";
    out << mpv_;
    out << ", unit_of_trade=";
    out << unit_of_trade_;
    out << ", reserved_2=";
    print::hex(out, reserved_2_.data(), reserved_2_.size());
    out << '}';
}

bool SymbolIndexMappingMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SymbolIndexMappingMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SymbolIndexMappingMessage::operator==(const SymbolIndexMappingMessage& other) const {
    return symbol_index_ == other.symbol_index_
        && symbol_ == other.symbol_
        && reserved_1_ == other.reserved_1_
        && market_id_ == other.market_id_
        && system_id_ == other.system_id_
        && exchange_code_ == other.exchange_code_
        && price_scale_code_ == other.price_scale_code_
        && security_type_ == other.security_type_
        && lot_size_ == other.lot_size_
        && prev_close_price_ == other.prev_close_price_
        && prev_close_volume_ == other.prev_close_volume_
        && price_resolution_ == other.price_resolution_
        && round_lot_ == other.round_lot_
        && mpv_ == other.mpv_
        && unit_of_trade_ == other.unit_of_trade_
        && reserved_2_ == other.reserved_2_;
}

bool SymbolIndexMappingMessage::operator!=(const SymbolIndexMappingMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g
