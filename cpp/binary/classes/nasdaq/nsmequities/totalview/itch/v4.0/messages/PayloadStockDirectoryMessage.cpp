#include "PayloadStockDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

PayloadStockDirectoryMessage::PayloadStockDirectoryMessage(std::chrono::nanoseconds nanoseconds, const std::string& stock, MarketCategory market_category, FinancialStatusIndicator financial_status_indicator, std::uint32_t round_lot_size, RoundLotsOnly round_lots_only)
  : nanoseconds_(nanoseconds), stock_(stock), market_category_(market_category), financial_status_indicator_(financial_status_indicator), round_lot_size_(round_lot_size), round_lots_only_(round_lots_only) {}

std::chrono::nanoseconds PayloadStockDirectoryMessage::nanoseconds() const { return nanoseconds_; }
void PayloadStockDirectoryMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

const std::string& PayloadStockDirectoryMessage::stock() const { return stock_; }
std::string& PayloadStockDirectoryMessage::stock() { return stock_; }
void PayloadStockDirectoryMessage::set_stock(const std::string& value) { stock_ = value; }

MarketCategory PayloadStockDirectoryMessage::market_category() const { return market_category_; }
void PayloadStockDirectoryMessage::set_market_category(MarketCategory value) { market_category_ = value; }

FinancialStatusIndicator PayloadStockDirectoryMessage::financial_status_indicator() const { return financial_status_indicator_; }
void PayloadStockDirectoryMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

std::uint32_t PayloadStockDirectoryMessage::round_lot_size() const { return round_lot_size_; }
void PayloadStockDirectoryMessage::set_round_lot_size(std::uint32_t value) { round_lot_size_ = value; }

RoundLotsOnly PayloadStockDirectoryMessage::round_lots_only() const { return round_lots_only_; }
void PayloadStockDirectoryMessage::set_round_lots_only(RoundLotsOnly value) { round_lots_only_ = value; }

PacketMessageCode PayloadStockDirectoryMessage::type() const { return message_type; }

std::string_view PayloadStockDirectoryMessage::name() const { return "Stock Directory Message"; }

std::size_t PayloadStockDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadStockDirectoryMessage", wire_size, length);

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

std::size_t PayloadStockDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadStockDirectoryMessage", wire_size, capacity);

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

std::size_t PayloadStockDirectoryMessage::encoded_size() const {
    return wire_size;
}

void PayloadStockDirectoryMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadStockDirectoryMessage::clone() const {
    return std::make_unique<PayloadStockDirectoryMessage>(*this);
}

void PayloadStockDirectoryMessage::print(std::ostream& out) const {
    out << "PayloadStockDirectoryMessage{";
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

bool PayloadStockDirectoryMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadStockDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadStockDirectoryMessage::operator==(const PayloadStockDirectoryMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && stock_ == other.stock_
        && market_category_ == other.market_category_
        && financial_status_indicator_ == other.financial_status_indicator_
        && round_lot_size_ == other.round_lot_size_
        && round_lots_only_ == other.round_lots_only_;
}

bool PayloadStockDirectoryMessage::operator!=(const PayloadStockDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
