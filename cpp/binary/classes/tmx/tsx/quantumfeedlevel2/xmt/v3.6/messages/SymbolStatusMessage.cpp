// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/SymbolStatusMessage.cpp
#include "SymbolStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

SymbolStatusMessage::SymbolStatusMessage(const std::string& symbol, std::optional<std::uint8_t> stock_group, const std::string& cusip, std::optional<std::uint16_t> board_lot, Currency currency, std::optional<Decimal> face_value, std::optional<Decimal> last_sale, ListingMarket listing_market, ProductType product_type, std::optional<std::uint32_t> buy_maximum_quantity, std::optional<std::uint32_t> buy_minimum_quantity, std::optional<std::uint32_t> sell_maximum_quantity, std::optional<std::uint32_t> sell_minimum_quantity, const std::string& stock_state, TestSymbol test_symbol, MocEligible moc_eligible)
  : symbol_(symbol), stock_group_(stock_group), cusip_(cusip), board_lot_(board_lot), currency_(currency), face_value_(face_value), last_sale_(last_sale), listing_market_(listing_market), product_type_(product_type), buy_maximum_quantity_(buy_maximum_quantity), buy_minimum_quantity_(buy_minimum_quantity), sell_maximum_quantity_(sell_maximum_quantity), sell_minimum_quantity_(sell_minimum_quantity), stock_state_(stock_state), test_symbol_(test_symbol), moc_eligible_(moc_eligible) {}

const std::string& SymbolStatusMessage::symbol() const { return symbol_; }
std::string& SymbolStatusMessage::symbol() { return symbol_; }
void SymbolStatusMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::optional<std::uint8_t> SymbolStatusMessage::stock_group() const { return stock_group_; }
void SymbolStatusMessage::set_stock_group(std::optional<std::uint8_t> value) { stock_group_ = value; }

const std::string& SymbolStatusMessage::cusip() const { return cusip_; }
std::string& SymbolStatusMessage::cusip() { return cusip_; }
void SymbolStatusMessage::set_cusip(const std::string& value) { cusip_ = value; }

std::optional<std::uint16_t> SymbolStatusMessage::board_lot() const { return board_lot_; }
void SymbolStatusMessage::set_board_lot(std::optional<std::uint16_t> value) { board_lot_ = value; }

Currency SymbolStatusMessage::currency() const { return currency_; }
void SymbolStatusMessage::set_currency(Currency value) { currency_ = value; }

std::optional<Decimal> SymbolStatusMessage::face_value() const { return face_value_; }
void SymbolStatusMessage::set_face_value(std::optional<Decimal> value) { face_value_ = value; }

std::optional<Decimal> SymbolStatusMessage::last_sale() const { return last_sale_; }
void SymbolStatusMessage::set_last_sale(std::optional<Decimal> value) { last_sale_ = value; }

ListingMarket SymbolStatusMessage::listing_market() const { return listing_market_; }
void SymbolStatusMessage::set_listing_market(ListingMarket value) { listing_market_ = value; }

ProductType SymbolStatusMessage::product_type() const { return product_type_; }
void SymbolStatusMessage::set_product_type(ProductType value) { product_type_ = value; }

std::optional<std::uint32_t> SymbolStatusMessage::buy_maximum_quantity() const { return buy_maximum_quantity_; }
void SymbolStatusMessage::set_buy_maximum_quantity(std::optional<std::uint32_t> value) { buy_maximum_quantity_ = value; }

std::optional<std::uint32_t> SymbolStatusMessage::buy_minimum_quantity() const { return buy_minimum_quantity_; }
void SymbolStatusMessage::set_buy_minimum_quantity(std::optional<std::uint32_t> value) { buy_minimum_quantity_ = value; }

std::optional<std::uint32_t> SymbolStatusMessage::sell_maximum_quantity() const { return sell_maximum_quantity_; }
void SymbolStatusMessage::set_sell_maximum_quantity(std::optional<std::uint32_t> value) { sell_maximum_quantity_ = value; }

std::optional<std::uint32_t> SymbolStatusMessage::sell_minimum_quantity() const { return sell_minimum_quantity_; }
void SymbolStatusMessage::set_sell_minimum_quantity(std::optional<std::uint32_t> value) { sell_minimum_quantity_ = value; }

const std::string& SymbolStatusMessage::stock_state() const { return stock_state_; }
std::string& SymbolStatusMessage::stock_state() { return stock_state_; }
void SymbolStatusMessage::set_stock_state(const std::string& value) { stock_state_ = value; }

TestSymbol SymbolStatusMessage::test_symbol() const { return test_symbol_; }
void SymbolStatusMessage::set_test_symbol(TestSymbol value) { test_symbol_ = value; }

MocEligible SymbolStatusMessage::moc_eligible() const { return moc_eligible_; }
void SymbolStatusMessage::set_moc_eligible(MocEligible value) { moc_eligible_ = value; }

MessageCode SymbolStatusMessage::type() const { return message_type; }

std::string_view SymbolStatusMessage::name() const { return "Symbol Status Message"; }

std::size_t SymbolStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolStatusMessage", wire_size, length);

    symbol_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    stock_group_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    cusip_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    board_lot_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    currency_ = static_cast<Currency>(wire::read_char(data + offset));
    offset += 1;

    face_value_ = wire::nullable_decimal(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL), -6);
    offset += 8;

    last_sale_ = wire::nullable_decimal(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL), -6);
    offset += 8;

    listing_market_ = static_cast<ListingMarket>(wire::read_char(data + offset));
    offset += 1;

    product_type_ = static_cast<ProductType>(wire::read_char(data + offset));
    offset += 1;

    buy_maximum_quantity_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    buy_minimum_quantity_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    sell_maximum_quantity_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    sell_minimum_quantity_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    stock_state_ = wire::read_text(data + offset, 2, ' ');
    offset += 2;

    test_symbol_ = static_cast<TestSymbol>(wire::read_char(data + offset));
    offset += 1;

    moc_eligible_ = static_cast<MocEligible>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SymbolStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolStatusMessage", wire_size, capacity);

    wire::write_text(data + offset, 12, ' ', symbol_);
    offset += 12;

    wire::write_u8(data + offset, stock_group_.value_or(static_cast<std::uint8_t>(0ULL)));
    offset += 1;

    wire::write_text(data + offset, 12, ' ', cusip_);
    offset += 12;

    wire::write_u16_le(data + offset, board_lot_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(currency_));
    offset += 1;

    wire::write_u64_le(data + offset, face_value_ ? static_cast<std::uint64_t>(face_value_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u64_le(data + offset, last_sale_ ? static_cast<std::uint64_t>(last_sale_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(listing_market_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(product_type_));
    offset += 1;

    wire::write_u32_le(data + offset, buy_maximum_quantity_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u32_le(data + offset, buy_minimum_quantity_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u32_le(data + offset, sell_maximum_quantity_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u32_le(data + offset, sell_minimum_quantity_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_text(data + offset, 2, ' ', stock_state_);
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(test_symbol_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(moc_eligible_));
    offset += 1;

    return offset;
}

std::size_t SymbolStatusMessage::encoded_size() const {
    return wire_size;
}

void SymbolStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SymbolStatusMessage::clone() const {
    return std::make_unique<SymbolStatusMessage>(*this);
}

void SymbolStatusMessage::print(std::ostream& out) const {
    out << "SymbolStatusMessage{";
    out << "symbol=";
    print::text(out, symbol_);
    out << ", stock_group=";
    print::optional(out, stock_group_);
    out << ", cusip=";
    print::text(out, cusip_);
    out << ", board_lot=";
    print::optional(out, board_lot_);
    out << ", currency=";
    out << currency_;
    out << ", face_value=";
    print::optional(out, face_value_);
    out << ", last_sale=";
    print::optional(out, last_sale_);
    out << ", listing_market=";
    out << listing_market_;
    out << ", product_type=";
    out << product_type_;
    out << ", buy_maximum_quantity=";
    print::optional(out, buy_maximum_quantity_);
    out << ", buy_minimum_quantity=";
    print::optional(out, buy_minimum_quantity_);
    out << ", sell_maximum_quantity=";
    print::optional(out, sell_maximum_quantity_);
    out << ", sell_minimum_quantity=";
    print::optional(out, sell_minimum_quantity_);
    out << ", stock_state=";
    print::text(out, stock_state_);
    out << ", test_symbol=";
    out << test_symbol_;
    out << ", moc_eligible=";
    out << moc_eligible_;
    out << '}';
}

bool SymbolStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SymbolStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SymbolStatusMessage::operator==(const SymbolStatusMessage& other) const {
    return symbol_ == other.symbol_
        && stock_group_ == other.stock_group_
        && cusip_ == other.cusip_
        && board_lot_ == other.board_lot_
        && currency_ == other.currency_
        && face_value_ == other.face_value_
        && last_sale_ == other.last_sale_
        && listing_market_ == other.listing_market_
        && product_type_ == other.product_type_
        && buy_maximum_quantity_ == other.buy_maximum_quantity_
        && buy_minimum_quantity_ == other.buy_minimum_quantity_
        && sell_maximum_quantity_ == other.sell_maximum_quantity_
        && sell_minimum_quantity_ == other.sell_minimum_quantity_
        && stock_state_ == other.stock_state_
        && test_symbol_ == other.test_symbol_
        && moc_eligible_ == other.moc_eligible_;
}

bool SymbolStatusMessage::operator!=(const SymbolStatusMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
