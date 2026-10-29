#include "SymbolInformationMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

SymbolInformationMessage::SymbolInformationMessage(std::chrono::nanoseconds timestamp, std::uint16_t symbol_id, const std::string& symbol, ListingMarket listing_market, std::uint32_t board_lot_size)
  : timestamp_(timestamp), symbol_id_(symbol_id), symbol_(symbol), listing_market_(listing_market), board_lot_size_(board_lot_size) {}

std::chrono::nanoseconds SymbolInformationMessage::timestamp() const { return timestamp_; }
void SymbolInformationMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t SymbolInformationMessage::symbol_id() const { return symbol_id_; }
void SymbolInformationMessage::set_symbol_id(std::uint16_t value) { symbol_id_ = value; }

const std::string& SymbolInformationMessage::symbol() const { return symbol_; }
std::string& SymbolInformationMessage::symbol() { return symbol_; }
void SymbolInformationMessage::set_symbol(const std::string& value) { symbol_ = value; }

ListingMarket SymbolInformationMessage::listing_market() const { return listing_market_; }
void SymbolInformationMessage::set_listing_market(ListingMarket value) { listing_market_ = value; }

std::uint32_t SymbolInformationMessage::board_lot_size() const { return board_lot_size_; }
void SymbolInformationMessage::set_board_lot_size(std::uint32_t value) { board_lot_size_ = value; }

MessageCode SymbolInformationMessage::type() const { return message_type; }

std::string_view SymbolInformationMessage::name() const { return "Symbol Information Message"; }

std::size_t SymbolInformationMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolInformationMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    symbol_id_ = wire::read_u16_le(data + offset);
    offset += 2;

    symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    listing_market_ = static_cast<ListingMarket>(wire::read_char(data + offset));
    offset += 1;

    board_lot_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t SymbolInformationMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolInformationMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(symbol_id_));
    offset += 2;

    wire::write_text(data + offset, 11, ' ', symbol_);
    offset += 11;

    wire::write_char(data + offset, static_cast<char>(listing_market_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(board_lot_size_));
    offset += 4;

    return offset;
}

std::size_t SymbolInformationMessage::encoded_size() const {
    return wire_size;
}

void SymbolInformationMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SymbolInformationMessage::clone() const {
    return std::make_unique<SymbolInformationMessage>(*this);
}

void SymbolInformationMessage::print(std::ostream& out) const {
    out << "SymbolInformationMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", symbol_id=";
    out << symbol_id_;
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", listing_market=";
    out << listing_market_;
    out << ", board_lot_size=";
    out << board_lot_size_;
    out << '}';
}

bool SymbolInformationMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SymbolInformationMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SymbolInformationMessage::operator==(const SymbolInformationMessage& other) const {
    return timestamp_ == other.timestamp_
        && symbol_id_ == other.symbol_id_
        && symbol_ == other.symbol_
        && listing_market_ == other.listing_market_
        && board_lot_size_ == other.board_lot_size_;
}

bool SymbolInformationMessage::operator!=(const SymbolInformationMessage& other) const {
    return !(*this == other);
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
