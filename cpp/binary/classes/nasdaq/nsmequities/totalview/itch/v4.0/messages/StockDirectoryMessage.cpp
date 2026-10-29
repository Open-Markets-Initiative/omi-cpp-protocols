#include "StockDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

StockDirectoryMessage::StockDirectoryMessage(std::chrono::nanoseconds nanoseconds, const std::string& stock, MarketCategory market_category, FinancialStatusIndicator financial_status_indicator, std::uint32_t round_lot_size, RoundLotsOnly round_lots_only)
  : nanoseconds_(nanoseconds), stock_(stock), market_category_(market_category), financial_status_indicator_(financial_status_indicator), round_lot_size_(round_lot_size), round_lots_only_(round_lots_only) {}

std::chrono::nanoseconds StockDirectoryMessage::nanoseconds() const { return nanoseconds_; }
void StockDirectoryMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

const std::string& StockDirectoryMessage::stock() const { return stock_; }
std::string& StockDirectoryMessage::stock() { return stock_; }
void StockDirectoryMessage::set_stock(const std::string& value) { stock_ = value; }

MarketCategory StockDirectoryMessage::market_category() const { return market_category_; }
void StockDirectoryMessage::set_market_category(MarketCategory value) { market_category_ = value; }

FinancialStatusIndicator StockDirectoryMessage::financial_status_indicator() const { return financial_status_indicator_; }
void StockDirectoryMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

std::uint32_t StockDirectoryMessage::round_lot_size() const { return round_lot_size_; }
void StockDirectoryMessage::set_round_lot_size(std::uint32_t value) { round_lot_size_ = value; }

RoundLotsOnly StockDirectoryMessage::round_lots_only() const { return round_lots_only_; }
void StockDirectoryMessage::set_round_lots_only(RoundLotsOnly value) { round_lots_only_ = value; }

SequencedMessageCode StockDirectoryMessage::type() const { return message_type; }

std::string_view StockDirectoryMessage::name() const { return "Stock Directory Message"; }

std::size_t StockDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StockDirectoryMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    stock_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    market_category_ = static_cast<MarketCategory>(wire::read_char(data + offset));
    offset += 1;

    financial_status_indicator_ = static_cast<FinancialStatusIndicator>(wire::read_char(data + offset));
    offset += 1;

    round_lot_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    round_lots_only_ = static_cast<RoundLotsOnly>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t StockDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StockDirectoryMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', stock_);
    offset += 6;

    wire::write_char(data + offset, static_cast<char>(market_category_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(financial_status_indicator_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(round_lot_size_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(round_lots_only_));
    offset += 1;

    return offset;
}

std::size_t StockDirectoryMessage::encoded_size() const {
    return wire_size;
}

void StockDirectoryMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> StockDirectoryMessage::clone() const {
    return std::make_unique<StockDirectoryMessage>(*this);
}

void StockDirectoryMessage::print(std::ostream& out) const {
    out << "StockDirectoryMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", stock=";
    print::text(out, stock_);
    out << ", market_category=";
    out << market_category_;
    out << ", financial_status_indicator=";
    out << financial_status_indicator_;
    out << ", round_lot_size=";
    out << round_lot_size_;
    out << ", round_lots_only=";
    out << round_lots_only_;
    out << '}';
}

bool StockDirectoryMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const StockDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StockDirectoryMessage::operator==(const StockDirectoryMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && stock_ == other.stock_
        && market_category_ == other.market_category_
        && financial_status_indicator_ == other.financial_status_indicator_
        && round_lot_size_ == other.round_lot_size_
        && round_lots_only_ == other.round_lots_only_;
}

bool StockDirectoryMessage::operator!=(const StockDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
