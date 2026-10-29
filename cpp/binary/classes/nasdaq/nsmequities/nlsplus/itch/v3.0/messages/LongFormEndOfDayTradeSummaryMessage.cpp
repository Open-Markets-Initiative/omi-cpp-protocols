#include "LongFormEndOfDayTradeSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

LongFormEndOfDayTradeSummaryMessage::LongFormEndOfDayTradeSummaryMessage(const std::string& issue_symbol, MarketCategory market_category, Decimal consolidated_high_price_long, Decimal consolidated_low_price_long, Decimal consolidated_closing_price_long, std::uint64_t consolidated_volume, Decimal consolidated_open_price_long)
  : issue_symbol_(issue_symbol), market_category_(market_category), consolidated_high_price_long_(consolidated_high_price_long), consolidated_low_price_long_(consolidated_low_price_long), consolidated_closing_price_long_(consolidated_closing_price_long), consolidated_volume_(consolidated_volume), consolidated_open_price_long_(consolidated_open_price_long) {}

const std::string& LongFormEndOfDayTradeSummaryMessage::issue_symbol() const { return issue_symbol_; }
std::string& LongFormEndOfDayTradeSummaryMessage::issue_symbol() { return issue_symbol_; }
void LongFormEndOfDayTradeSummaryMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

MarketCategory LongFormEndOfDayTradeSummaryMessage::market_category() const { return market_category_; }
void LongFormEndOfDayTradeSummaryMessage::set_market_category(MarketCategory value) { market_category_ = value; }

Decimal LongFormEndOfDayTradeSummaryMessage::consolidated_high_price_long() const { return consolidated_high_price_long_; }
void LongFormEndOfDayTradeSummaryMessage::set_consolidated_high_price_long(Decimal value) { consolidated_high_price_long_ = value; }

Decimal LongFormEndOfDayTradeSummaryMessage::consolidated_low_price_long() const { return consolidated_low_price_long_; }
void LongFormEndOfDayTradeSummaryMessage::set_consolidated_low_price_long(Decimal value) { consolidated_low_price_long_ = value; }

Decimal LongFormEndOfDayTradeSummaryMessage::consolidated_closing_price_long() const { return consolidated_closing_price_long_; }
void LongFormEndOfDayTradeSummaryMessage::set_consolidated_closing_price_long(Decimal value) { consolidated_closing_price_long_ = value; }

std::uint64_t LongFormEndOfDayTradeSummaryMessage::consolidated_volume() const { return consolidated_volume_; }
void LongFormEndOfDayTradeSummaryMessage::set_consolidated_volume(std::uint64_t value) { consolidated_volume_ = value; }

Decimal LongFormEndOfDayTradeSummaryMessage::consolidated_open_price_long() const { return consolidated_open_price_long_; }
void LongFormEndOfDayTradeSummaryMessage::set_consolidated_open_price_long(Decimal value) { consolidated_open_price_long_ = value; }

MessageCode LongFormEndOfDayTradeSummaryMessage::type() const { return message_type; }

std::string_view LongFormEndOfDayTradeSummaryMessage::name() const { return "Long Form End Of Day Trade Summary Message"; }

std::size_t LongFormEndOfDayTradeSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LongFormEndOfDayTradeSummaryMessage", wire_size, length);

    issue_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    market_category_ = static_cast<MarketCategory>(wire::read_char(data + offset));
    offset += 1;

    consolidated_high_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -4);
    offset += 8;

    consolidated_low_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -4);
    offset += 8;

    consolidated_closing_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -4);
    offset += 8;

    consolidated_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    consolidated_open_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t LongFormEndOfDayTradeSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LongFormEndOfDayTradeSummaryMessage", wire_size, capacity);

    wire::write_text(data + offset, 8, ' ', issue_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(market_category_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_high_price_long_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_low_price_long_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_closing_price_long_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_volume_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_open_price_long_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t LongFormEndOfDayTradeSummaryMessage::encoded_size() const {
    return wire_size;
}

void LongFormEndOfDayTradeSummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> LongFormEndOfDayTradeSummaryMessage::clone() const {
    return std::make_unique<LongFormEndOfDayTradeSummaryMessage>(*this);
}

void LongFormEndOfDayTradeSummaryMessage::print(std::ostream& out) const {
    out << "LongFormEndOfDayTradeSummaryMessage{";
    out << "issue_symbol=";
    print::text(out, issue_symbol_);
    out << ", market_category=";
    out << market_category_;
    out << ", consolidated_high_price_long=";
    out << consolidated_high_price_long_;
    out << ", consolidated_low_price_long=";
    out << consolidated_low_price_long_;
    out << ", consolidated_closing_price_long=";
    out << consolidated_closing_price_long_;
    out << ", consolidated_volume=";
    out << consolidated_volume_;
    out << ", consolidated_open_price_long=";
    out << consolidated_open_price_long_;
    out << '}';
}

bool LongFormEndOfDayTradeSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const LongFormEndOfDayTradeSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LongFormEndOfDayTradeSummaryMessage::operator==(const LongFormEndOfDayTradeSummaryMessage& other) const {
    return issue_symbol_ == other.issue_symbol_
        && market_category_ == other.market_category_
        && consolidated_high_price_long_ == other.consolidated_high_price_long_
        && consolidated_low_price_long_ == other.consolidated_low_price_long_
        && consolidated_closing_price_long_ == other.consolidated_closing_price_long_
        && consolidated_volume_ == other.consolidated_volume_
        && consolidated_open_price_long_ == other.consolidated_open_price_long_;
}

bool LongFormEndOfDayTradeSummaryMessage::operator!=(const LongFormEndOfDayTradeSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
