#include "SeriesIndexMappingMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

SeriesIndexMappingMessage::SeriesIndexMappingMessage(std::uint32_t series_index, std::uint8_t channel_id, const std::array<std::byte, 1>& reserved_a_1, MarketId market_id, std::uint8_t system_id, const std::array<std::byte, 1>& reserved_b_1, std::uint16_t stream_id, std::uint32_t underlying_index, std::uint16_t contract_multiplier, const std::string& maturity_date, PutOrCall put_or_call, const std::string& strike_price, std::uint8_t price_scale_code, const std::string& underlying_symbol, const std::string& option_symbol_root, std::uint32_t group_id)
  : series_index_(series_index), channel_id_(channel_id), reserved_a_1_(reserved_a_1), market_id_(market_id), system_id_(system_id), reserved_b_1_(reserved_b_1), stream_id_(stream_id), underlying_index_(underlying_index), contract_multiplier_(contract_multiplier), maturity_date_(maturity_date), put_or_call_(put_or_call), strike_price_(strike_price), price_scale_code_(price_scale_code), underlying_symbol_(underlying_symbol), option_symbol_root_(option_symbol_root), group_id_(group_id) {}

std::uint32_t SeriesIndexMappingMessage::series_index() const { return series_index_; }
void SeriesIndexMappingMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint8_t SeriesIndexMappingMessage::channel_id() const { return channel_id_; }
void SeriesIndexMappingMessage::set_channel_id(std::uint8_t value) { channel_id_ = value; }

const std::array<std::byte, 1>& SeriesIndexMappingMessage::reserved_a_1() const { return reserved_a_1_; }
std::array<std::byte, 1>& SeriesIndexMappingMessage::reserved_a_1() { return reserved_a_1_; }
void SeriesIndexMappingMessage::set_reserved_a_1(const std::array<std::byte, 1>& value) { reserved_a_1_ = value; }

MarketId SeriesIndexMappingMessage::market_id() const { return market_id_; }
void SeriesIndexMappingMessage::set_market_id(MarketId value) { market_id_ = value; }

std::uint8_t SeriesIndexMappingMessage::system_id() const { return system_id_; }
void SeriesIndexMappingMessage::set_system_id(std::uint8_t value) { system_id_ = value; }

const std::array<std::byte, 1>& SeriesIndexMappingMessage::reserved_b_1() const { return reserved_b_1_; }
std::array<std::byte, 1>& SeriesIndexMappingMessage::reserved_b_1() { return reserved_b_1_; }
void SeriesIndexMappingMessage::set_reserved_b_1(const std::array<std::byte, 1>& value) { reserved_b_1_ = value; }

std::uint16_t SeriesIndexMappingMessage::stream_id() const { return stream_id_; }
void SeriesIndexMappingMessage::set_stream_id(std::uint16_t value) { stream_id_ = value; }

std::uint32_t SeriesIndexMappingMessage::underlying_index() const { return underlying_index_; }
void SeriesIndexMappingMessage::set_underlying_index(std::uint32_t value) { underlying_index_ = value; }

std::uint16_t SeriesIndexMappingMessage::contract_multiplier() const { return contract_multiplier_; }
void SeriesIndexMappingMessage::set_contract_multiplier(std::uint16_t value) { contract_multiplier_ = value; }

const std::string& SeriesIndexMappingMessage::maturity_date() const { return maturity_date_; }
std::string& SeriesIndexMappingMessage::maturity_date() { return maturity_date_; }
void SeriesIndexMappingMessage::set_maturity_date(const std::string& value) { maturity_date_ = value; }

PutOrCall SeriesIndexMappingMessage::put_or_call() const { return put_or_call_; }
void SeriesIndexMappingMessage::set_put_or_call(PutOrCall value) { put_or_call_ = value; }

const std::string& SeriesIndexMappingMessage::strike_price() const { return strike_price_; }
std::string& SeriesIndexMappingMessage::strike_price() { return strike_price_; }
void SeriesIndexMappingMessage::set_strike_price(const std::string& value) { strike_price_ = value; }

std::uint8_t SeriesIndexMappingMessage::price_scale_code() const { return price_scale_code_; }
void SeriesIndexMappingMessage::set_price_scale_code(std::uint8_t value) { price_scale_code_ = value; }

const std::string& SeriesIndexMappingMessage::underlying_symbol() const { return underlying_symbol_; }
std::string& SeriesIndexMappingMessage::underlying_symbol() { return underlying_symbol_; }
void SeriesIndexMappingMessage::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

const std::string& SeriesIndexMappingMessage::option_symbol_root() const { return option_symbol_root_; }
std::string& SeriesIndexMappingMessage::option_symbol_root() { return option_symbol_root_; }
void SeriesIndexMappingMessage::set_option_symbol_root(const std::string& value) { option_symbol_root_ = value; }

std::uint32_t SeriesIndexMappingMessage::group_id() const { return group_id_; }
void SeriesIndexMappingMessage::set_group_id(std::uint32_t value) { group_id_ = value; }

MessageCode SeriesIndexMappingMessage::type() const { return message_type; }

std::string_view SeriesIndexMappingMessage::name() const { return "Series Index Mapping Message"; }

std::size_t SeriesIndexMappingMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SeriesIndexMappingMessage", wire_size, length);

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    channel_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::read_bytes(data + offset, reserved_a_1_.data(), 1);
    offset += 1;

    market_id_ = static_cast<MarketId>(wire::read_u16_le(data + offset));
    offset += 2;

    system_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::read_bytes(data + offset, reserved_b_1_.data(), 1);
    offset += 1;

    stream_id_ = wire::read_u16_le(data + offset);
    offset += 2;

    underlying_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    contract_multiplier_ = wire::read_u16_le(data + offset);
    offset += 2;

    maturity_date_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    put_or_call_ = static_cast<PutOrCall>(wire::read_u8(data + offset));
    offset += 1;

    strike_price_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    price_scale_code_ = wire::read_u8(data + offset);
    offset += 1;

    underlying_symbol_ = wire::read_text(data + offset, 11, '\0');
    offset += 11;

    option_symbol_root_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    group_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t SeriesIndexMappingMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SeriesIndexMappingMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(channel_id_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_a_1_.data(), 1);
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(market_id_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(system_id_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_b_1_.data(), 1);
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(stream_id_));
    offset += 2;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(underlying_index_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(contract_multiplier_));
    offset += 2;

    wire::write_text(data + offset, 6, '\0', maturity_date_);
    offset += 6;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(put_or_call_));
    offset += 1;

    wire::write_text(data + offset, 10, '\0', strike_price_);
    offset += 10;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_scale_code_));
    offset += 1;

    wire::write_text(data + offset, 11, '\0', underlying_symbol_);
    offset += 11;

    wire::write_text(data + offset, 5, '\0', option_symbol_root_);
    offset += 5;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(group_id_));
    offset += 4;

    return offset;
}

std::size_t SeriesIndexMappingMessage::encoded_size() const {
    return wire_size;
}

void SeriesIndexMappingMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SeriesIndexMappingMessage::clone() const {
    return std::make_unique<SeriesIndexMappingMessage>(*this);
}

void SeriesIndexMappingMessage::print(std::ostream& out) const {
    out << "SeriesIndexMappingMessage{";
    out << "series_index=";
    out << series_index_;
    out << ", channel_id=";
    out << static_cast<int>(channel_id_);
    out << ", reserved_a_1=";
    print::hex(out, reserved_a_1_.data(), reserved_a_1_.size());
    out << ", market_id=";
    out << market_id_;
    out << ", system_id=";
    out << static_cast<int>(system_id_);
    out << ", reserved_b_1=";
    print::hex(out, reserved_b_1_.data(), reserved_b_1_.size());
    out << ", stream_id=";
    out << stream_id_;
    out << ", underlying_index=";
    out << underlying_index_;
    out << ", contract_multiplier=";
    out << contract_multiplier_;
    out << ", maturity_date=";
    print::text(out, maturity_date_);
    out << ", put_or_call=";
    out << put_or_call_;
    out << ", strike_price=";
    print::text(out, strike_price_);
    out << ", price_scale_code=";
    out << static_cast<int>(price_scale_code_);
    out << ", underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << ", option_symbol_root=";
    print::text(out, option_symbol_root_);
    out << ", group_id=";
    out << group_id_;
    out << '}';
}

bool SeriesIndexMappingMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SeriesIndexMappingMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SeriesIndexMappingMessage::operator==(const SeriesIndexMappingMessage& other) const {
    return series_index_ == other.series_index_
        && channel_id_ == other.channel_id_
        && reserved_a_1_ == other.reserved_a_1_
        && market_id_ == other.market_id_
        && system_id_ == other.system_id_
        && reserved_b_1_ == other.reserved_b_1_
        && stream_id_ == other.stream_id_
        && underlying_index_ == other.underlying_index_
        && contract_multiplier_ == other.contract_multiplier_
        && maturity_date_ == other.maturity_date_
        && put_or_call_ == other.put_or_call_
        && strike_price_ == other.strike_price_
        && price_scale_code_ == other.price_scale_code_
        && underlying_symbol_ == other.underlying_symbol_
        && option_symbol_root_ == other.option_symbol_root_
        && group_id_ == other.group_id_;
}

bool SeriesIndexMappingMessage::operator!=(const SeriesIndexMappingMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
