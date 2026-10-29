#include "EndOfDayTradeSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

EndOfDayTradeSummaryMessage::EndOfDayTradeSummaryMessage(const std::string& issue_symbol, MarketCategory market_category, Decimal consolidated_high_price, Decimal consolidated_low_price, Decimal consolidated_closing_price, std::uint64_t consolidated_volume, Decimal consolidated_open_price)
  : issue_symbol_(issue_symbol), market_category_(market_category), consolidated_high_price_(consolidated_high_price), consolidated_low_price_(consolidated_low_price), consolidated_closing_price_(consolidated_closing_price), consolidated_volume_(consolidated_volume), consolidated_open_price_(consolidated_open_price) {}

const std::string& EndOfDayTradeSummaryMessage::issue_symbol() const { return issue_symbol_; }
std::string& EndOfDayTradeSummaryMessage::issue_symbol() { return issue_symbol_; }
void EndOfDayTradeSummaryMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

MarketCategory EndOfDayTradeSummaryMessage::market_category() const { return market_category_; }
void EndOfDayTradeSummaryMessage::set_market_category(MarketCategory value) { market_category_ = value; }

Decimal EndOfDayTradeSummaryMessage::consolidated_high_price() const { return consolidated_high_price_; }
void EndOfDayTradeSummaryMessage::set_consolidated_high_price(Decimal value) { consolidated_high_price_ = value; }

Decimal EndOfDayTradeSummaryMessage::consolidated_low_price() const { return consolidated_low_price_; }
void EndOfDayTradeSummaryMessage::set_consolidated_low_price(Decimal value) { consolidated_low_price_ = value; }

Decimal EndOfDayTradeSummaryMessage::consolidated_closing_price() const { return consolidated_closing_price_; }
void EndOfDayTradeSummaryMessage::set_consolidated_closing_price(Decimal value) { consolidated_closing_price_ = value; }

std::uint64_t EndOfDayTradeSummaryMessage::consolidated_volume() const { return consolidated_volume_; }
void EndOfDayTradeSummaryMessage::set_consolidated_volume(std::uint64_t value) { consolidated_volume_ = value; }

Decimal EndOfDayTradeSummaryMessage::consolidated_open_price() const { return consolidated_open_price_; }
void EndOfDayTradeSummaryMessage::set_consolidated_open_price(Decimal value) { consolidated_open_price_ = value; }

MessageCode EndOfDayTradeSummaryMessage::type() const { return message_type; }

std::string_view EndOfDayTradeSummaryMessage::name() const { return "End Of Day Trade Summary Message"; }

std::size_t EndOfDayTradeSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EndOfDayTradeSummaryMessage", wire_size, length);

    issue_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    market_category_ = static_cast<MarketCategory>(wire::read_char(data + offset));
    offset += 1;

    consolidated_high_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    consolidated_low_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    consolidated_closing_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    consolidated_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    consolidated_open_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    return offset;
}

std::size_t EndOfDayTradeSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EndOfDayTradeSummaryMessage", wire_size, capacity);

    wire::write_text(data + offset, 8, ' ', issue_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(market_category_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(consolidated_high_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(consolidated_low_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(consolidated_closing_price_.mantissa()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_volume_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(consolidated_open_price_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t EndOfDayTradeSummaryMessage::encoded_size() const {
    return wire_size;
}

void EndOfDayTradeSummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EndOfDayTradeSummaryMessage::clone() const {
    return std::make_unique<EndOfDayTradeSummaryMessage>(*this);
}

void EndOfDayTradeSummaryMessage::print(std::ostream& out) const {
    out << "EndOfDayTradeSummaryMessage{";
    out << "issue_symbol=";
    print::text(out, issue_symbol_);
    out << ", market_category=";
    out << market_category_;
    out << ", consolidated_high_price=";
    out << consolidated_high_price_;
    out << ", consolidated_low_price=";
    out << consolidated_low_price_;
    out << ", consolidated_closing_price=";
    out << consolidated_closing_price_;
    out << ", consolidated_volume=";
    out << consolidated_volume_;
    out << ", consolidated_open_price=";
    out << consolidated_open_price_;
    out << '}';
}

bool EndOfDayTradeSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EndOfDayTradeSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EndOfDayTradeSummaryMessage::operator==(const EndOfDayTradeSummaryMessage& other) const {
    return issue_symbol_ == other.issue_symbol_
        && market_category_ == other.market_category_
        && consolidated_high_price_ == other.consolidated_high_price_
        && consolidated_low_price_ == other.consolidated_low_price_
        && consolidated_closing_price_ == other.consolidated_closing_price_
        && consolidated_volume_ == other.consolidated_volume_
        && consolidated_open_price_ == other.consolidated_open_price_;
}

bool EndOfDayTradeSummaryMessage::operator!=(const EndOfDayTradeSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
