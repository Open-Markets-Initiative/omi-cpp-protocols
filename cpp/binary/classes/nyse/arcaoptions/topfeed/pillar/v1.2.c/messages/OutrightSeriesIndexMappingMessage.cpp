#include "OutrightSeriesIndexMappingMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

OutrightSeriesIndexMappingMessage::OutrightSeriesIndexMappingMessage(std::uint32_t series_index, SeriesType series_type, MarketId market_id, std::uint8_t system_id, const std::string& option_symbol_root, const std::string& underlying_symbol, std::uint32_t underlying_index, PriceScaleCode price_scale_code, std::uint16_t contract_multiplier, const std::string& maturity_date, PutOrCall put_or_call, const std::string& strike_price, ClosingOnlyIndicator closing_only_indicator, const std::array<std::byte, 1>& reserved_1)
  : series_index_(series_index), series_type_(series_type), market_id_(market_id), system_id_(system_id), option_symbol_root_(option_symbol_root), underlying_symbol_(underlying_symbol), underlying_index_(underlying_index), price_scale_code_(price_scale_code), contract_multiplier_(contract_multiplier), maturity_date_(maturity_date), put_or_call_(put_or_call), strike_price_(strike_price), closing_only_indicator_(closing_only_indicator), reserved_1_(reserved_1) {}

std::uint32_t OutrightSeriesIndexMappingMessage::series_index() const { return series_index_; }
void OutrightSeriesIndexMappingMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

SeriesType OutrightSeriesIndexMappingMessage::series_type() const { return series_type_; }
void OutrightSeriesIndexMappingMessage::set_series_type(SeriesType value) { series_type_ = value; }

MarketId OutrightSeriesIndexMappingMessage::market_id() const { return market_id_; }
void OutrightSeriesIndexMappingMessage::set_market_id(MarketId value) { market_id_ = value; }

std::uint8_t OutrightSeriesIndexMappingMessage::system_id() const { return system_id_; }
void OutrightSeriesIndexMappingMessage::set_system_id(std::uint8_t value) { system_id_ = value; }

const std::string& OutrightSeriesIndexMappingMessage::option_symbol_root() const { return option_symbol_root_; }
std::string& OutrightSeriesIndexMappingMessage::option_symbol_root() { return option_symbol_root_; }
void OutrightSeriesIndexMappingMessage::set_option_symbol_root(const std::string& value) { option_symbol_root_ = value; }

const std::string& OutrightSeriesIndexMappingMessage::underlying_symbol() const { return underlying_symbol_; }
std::string& OutrightSeriesIndexMappingMessage::underlying_symbol() { return underlying_symbol_; }
void OutrightSeriesIndexMappingMessage::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

std::uint32_t OutrightSeriesIndexMappingMessage::underlying_index() const { return underlying_index_; }
void OutrightSeriesIndexMappingMessage::set_underlying_index(std::uint32_t value) { underlying_index_ = value; }

PriceScaleCode OutrightSeriesIndexMappingMessage::price_scale_code() const { return price_scale_code_; }
void OutrightSeriesIndexMappingMessage::set_price_scale_code(PriceScaleCode value) { price_scale_code_ = value; }

std::uint16_t OutrightSeriesIndexMappingMessage::contract_multiplier() const { return contract_multiplier_; }
void OutrightSeriesIndexMappingMessage::set_contract_multiplier(std::uint16_t value) { contract_multiplier_ = value; }

const std::string& OutrightSeriesIndexMappingMessage::maturity_date() const { return maturity_date_; }
std::string& OutrightSeriesIndexMappingMessage::maturity_date() { return maturity_date_; }
void OutrightSeriesIndexMappingMessage::set_maturity_date(const std::string& value) { maturity_date_ = value; }

PutOrCall OutrightSeriesIndexMappingMessage::put_or_call() const { return put_or_call_; }
void OutrightSeriesIndexMappingMessage::set_put_or_call(PutOrCall value) { put_or_call_ = value; }

const std::string& OutrightSeriesIndexMappingMessage::strike_price() const { return strike_price_; }
std::string& OutrightSeriesIndexMappingMessage::strike_price() { return strike_price_; }
void OutrightSeriesIndexMappingMessage::set_strike_price(const std::string& value) { strike_price_ = value; }

ClosingOnlyIndicator OutrightSeriesIndexMappingMessage::closing_only_indicator() const { return closing_only_indicator_; }
void OutrightSeriesIndexMappingMessage::set_closing_only_indicator(ClosingOnlyIndicator value) { closing_only_indicator_ = value; }

const std::array<std::byte, 1>& OutrightSeriesIndexMappingMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& OutrightSeriesIndexMappingMessage::reserved_1() { return reserved_1_; }
void OutrightSeriesIndexMappingMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

MessageCode OutrightSeriesIndexMappingMessage::type() const { return message_type; }

std::string_view OutrightSeriesIndexMappingMessage::name() const { return "Outright Series Index Mapping Message"; }

std::size_t OutrightSeriesIndexMappingMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OutrightSeriesIndexMappingMessage", wire_size, length);

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_type_ = static_cast<SeriesType>(wire::read_u8(data + offset));
    offset += 1;

    market_id_ = static_cast<MarketId>(wire::read_u16_le(data + offset));
    offset += 2;

    system_id_ = wire::read_u8(data + offset);
    offset += 1;

    option_symbol_root_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    underlying_symbol_ = wire::read_text(data + offset, 11, '\0');
    offset += 11;

    underlying_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_scale_code_ = static_cast<PriceScaleCode>(wire::read_u8(data + offset));
    offset += 1;

    contract_multiplier_ = wire::read_u16_le(data + offset);
    offset += 2;

    maturity_date_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    put_or_call_ = static_cast<PutOrCall>(wire::read_u8(data + offset));
    offset += 1;

    strike_price_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    closing_only_indicator_ = static_cast<ClosingOnlyIndicator>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t OutrightSeriesIndexMappingMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OutrightSeriesIndexMappingMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(series_type_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(market_id_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(system_id_));
    offset += 1;

    wire::write_text(data + offset, 6, '\0', option_symbol_root_);
    offset += 6;

    wire::write_text(data + offset, 11, '\0', underlying_symbol_);
    offset += 11;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(underlying_index_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_scale_code_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(contract_multiplier_));
    offset += 2;

    wire::write_text(data + offset, 6, '\0', maturity_date_);
    offset += 6;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(put_or_call_));
    offset += 1;

    wire::write_text(data + offset, 10, '\0', strike_price_);
    offset += 10;

    wire::write_char(data + offset, static_cast<char>(closing_only_indicator_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t OutrightSeriesIndexMappingMessage::encoded_size() const {
    return wire_size;
}

void OutrightSeriesIndexMappingMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OutrightSeriesIndexMappingMessage::clone() const {
    return std::make_unique<OutrightSeriesIndexMappingMessage>(*this);
}

void OutrightSeriesIndexMappingMessage::print(std::ostream& out) const {
    out << "OutrightSeriesIndexMappingMessage{";
    out << "series_index=";
    out << series_index_;
    out << ", series_type=";
    out << series_type_;
    out << ", market_id=";
    out << market_id_;
    out << ", system_id=";
    out << static_cast<int>(system_id_);
    out << ", option_symbol_root=";
    print::text(out, option_symbol_root_);
    out << ", underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << ", underlying_index=";
    out << underlying_index_;
    out << ", price_scale_code=";
    out << price_scale_code_;
    out << ", contract_multiplier=";
    out << contract_multiplier_;
    out << ", maturity_date=";
    print::text(out, maturity_date_);
    out << ", put_or_call=";
    out << put_or_call_;
    out << ", strike_price=";
    print::text(out, strike_price_);
    out << ", closing_only_indicator=";
    out << closing_only_indicator_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << '}';
}

bool OutrightSeriesIndexMappingMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OutrightSeriesIndexMappingMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OutrightSeriesIndexMappingMessage::operator==(const OutrightSeriesIndexMappingMessage& other) const {
    return series_index_ == other.series_index_
        && series_type_ == other.series_type_
        && market_id_ == other.market_id_
        && system_id_ == other.system_id_
        && option_symbol_root_ == other.option_symbol_root_
        && underlying_symbol_ == other.underlying_symbol_
        && underlying_index_ == other.underlying_index_
        && price_scale_code_ == other.price_scale_code_
        && contract_multiplier_ == other.contract_multiplier_
        && maturity_date_ == other.maturity_date_
        && put_or_call_ == other.put_or_call_
        && strike_price_ == other.strike_price_
        && closing_only_indicator_ == other.closing_only_indicator_
        && reserved_1_ == other.reserved_1_;
}

bool OutrightSeriesIndexMappingMessage::operator!=(const OutrightSeriesIndexMappingMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
