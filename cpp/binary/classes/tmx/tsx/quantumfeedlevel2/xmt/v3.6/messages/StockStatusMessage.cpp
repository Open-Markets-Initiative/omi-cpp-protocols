// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/StockStatusMessage.cpp
#include "StockStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

StockStatusMessage::StockStatusMessage(const std::string& symbol, const std::string& comment, const std::string& stock_state, std::optional<std::chrono::nanoseconds> trading_system_time_stamp, ListingMarket listing_market, ProductType product_type)
  : symbol_(symbol), comment_(comment), stock_state_(stock_state), trading_system_time_stamp_(trading_system_time_stamp), listing_market_(listing_market), product_type_(product_type) {}

const std::string& StockStatusMessage::symbol() const { return symbol_; }
std::string& StockStatusMessage::symbol() { return symbol_; }
void StockStatusMessage::set_symbol(const std::string& value) { symbol_ = value; }

const std::string& StockStatusMessage::comment() const { return comment_; }
std::string& StockStatusMessage::comment() { return comment_; }
void StockStatusMessage::set_comment(const std::string& value) { comment_ = value; }

const std::string& StockStatusMessage::stock_state() const { return stock_state_; }
std::string& StockStatusMessage::stock_state() { return stock_state_; }
void StockStatusMessage::set_stock_state(const std::string& value) { stock_state_ = value; }

std::optional<std::chrono::nanoseconds> StockStatusMessage::trading_system_time_stamp() const { return trading_system_time_stamp_; }
void StockStatusMessage::set_trading_system_time_stamp(std::optional<std::chrono::nanoseconds> value) { trading_system_time_stamp_ = value; }

ListingMarket StockStatusMessage::listing_market() const { return listing_market_; }
void StockStatusMessage::set_listing_market(ListingMarket value) { listing_market_ = value; }

ProductType StockStatusMessage::product_type() const { return product_type_; }
void StockStatusMessage::set_product_type(ProductType value) { product_type_ = value; }

MessageCode StockStatusMessage::type() const { return message_type; }

std::string_view StockStatusMessage::name() const { return "Stock Status Message"; }

std::size_t StockStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StockStatusMessage", wire_size, length);

    symbol_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    comment_ = wire::read_text(data + offset, 40, ' ');
    offset += 40;

    stock_state_ = wire::read_text(data + offset, 2, ' ');
    offset += 2;

    trading_system_time_stamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    listing_market_ = static_cast<ListingMarket>(wire::read_char(data + offset));
    offset += 1;

    product_type_ = static_cast<ProductType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t StockStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StockStatusMessage", wire_size, capacity);

    wire::write_text(data + offset, 12, ' ', symbol_);
    offset += 12;

    wire::write_text(data + offset, 40, ' ', comment_);
    offset += 40;

    wire::write_text(data + offset, 2, ' ', stock_state_);
    offset += 2;

    wire::write_u64_le(data + offset, trading_system_time_stamp_ ? static_cast<std::uint64_t>(trading_system_time_stamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(listing_market_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(product_type_));
    offset += 1;

    return offset;
}

std::size_t StockStatusMessage::encoded_size() const {
    return wire_size;
}

void StockStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StockStatusMessage::clone() const {
    return std::make_unique<StockStatusMessage>(*this);
}

void StockStatusMessage::print(std::ostream& out) const {
    out << "StockStatusMessage{";
    out << "symbol=";
    print::text(out, symbol_);
    out << ", comment=";
    print::text(out, comment_);
    out << ", stock_state=";
    print::text(out, stock_state_);
    out << ", trading_system_time_stamp=";
    print::optional_duration(out, trading_system_time_stamp_);
    out << ", listing_market=";
    out << listing_market_;
    out << ", product_type=";
    out << product_type_;
    out << '}';
}

bool StockStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StockStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StockStatusMessage::operator==(const StockStatusMessage& other) const {
    return symbol_ == other.symbol_
        && comment_ == other.comment_
        && stock_state_ == other.stock_state_
        && trading_system_time_stamp_ == other.trading_system_time_stamp_
        && listing_market_ == other.listing_market_
        && product_type_ == other.product_type_;
}

bool StockStatusMessage::operator!=(const StockStatusMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
