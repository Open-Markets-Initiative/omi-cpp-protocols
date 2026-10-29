#include "NextSharesEndOfDayTradeSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

NextSharesEndOfDayTradeSummaryMessage::NextSharesEndOfDayTradeSummaryMessage(const std::string& issue_symbol, MarketCategory market_category, Decimal consolidated_high_price, Decimal nav_offset_amount_high, Decimal consolidated_low_price, Decimal nav_offset_amount_low, Decimal consolidated_closing_price, Decimal nav_offset_amount_closing, std::uint64_t consolidated_volume, Decimal consolidated_open_price, Decimal nav_offset_amount_open)
  : issue_symbol_(issue_symbol), market_category_(market_category), consolidated_high_price_(consolidated_high_price), nav_offset_amount_high_(nav_offset_amount_high), consolidated_low_price_(consolidated_low_price), nav_offset_amount_low_(nav_offset_amount_low), consolidated_closing_price_(consolidated_closing_price), nav_offset_amount_closing_(nav_offset_amount_closing), consolidated_volume_(consolidated_volume), consolidated_open_price_(consolidated_open_price), nav_offset_amount_open_(nav_offset_amount_open) {}

const std::string& NextSharesEndOfDayTradeSummaryMessage::issue_symbol() const { return issue_symbol_; }
std::string& NextSharesEndOfDayTradeSummaryMessage::issue_symbol() { return issue_symbol_; }
void NextSharesEndOfDayTradeSummaryMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

MarketCategory NextSharesEndOfDayTradeSummaryMessage::market_category() const { return market_category_; }
void NextSharesEndOfDayTradeSummaryMessage::set_market_category(MarketCategory value) { market_category_ = value; }

Decimal NextSharesEndOfDayTradeSummaryMessage::consolidated_high_price() const { return consolidated_high_price_; }
void NextSharesEndOfDayTradeSummaryMessage::set_consolidated_high_price(Decimal value) { consolidated_high_price_ = value; }

Decimal NextSharesEndOfDayTradeSummaryMessage::nav_offset_amount_high() const { return nav_offset_amount_high_; }
void NextSharesEndOfDayTradeSummaryMessage::set_nav_offset_amount_high(Decimal value) { nav_offset_amount_high_ = value; }

Decimal NextSharesEndOfDayTradeSummaryMessage::consolidated_low_price() const { return consolidated_low_price_; }
void NextSharesEndOfDayTradeSummaryMessage::set_consolidated_low_price(Decimal value) { consolidated_low_price_ = value; }

Decimal NextSharesEndOfDayTradeSummaryMessage::nav_offset_amount_low() const { return nav_offset_amount_low_; }
void NextSharesEndOfDayTradeSummaryMessage::set_nav_offset_amount_low(Decimal value) { nav_offset_amount_low_ = value; }

Decimal NextSharesEndOfDayTradeSummaryMessage::consolidated_closing_price() const { return consolidated_closing_price_; }
void NextSharesEndOfDayTradeSummaryMessage::set_consolidated_closing_price(Decimal value) { consolidated_closing_price_ = value; }

Decimal NextSharesEndOfDayTradeSummaryMessage::nav_offset_amount_closing() const { return nav_offset_amount_closing_; }
void NextSharesEndOfDayTradeSummaryMessage::set_nav_offset_amount_closing(Decimal value) { nav_offset_amount_closing_ = value; }

std::uint64_t NextSharesEndOfDayTradeSummaryMessage::consolidated_volume() const { return consolidated_volume_; }
void NextSharesEndOfDayTradeSummaryMessage::set_consolidated_volume(std::uint64_t value) { consolidated_volume_ = value; }

Decimal NextSharesEndOfDayTradeSummaryMessage::consolidated_open_price() const { return consolidated_open_price_; }
void NextSharesEndOfDayTradeSummaryMessage::set_consolidated_open_price(Decimal value) { consolidated_open_price_ = value; }

Decimal NextSharesEndOfDayTradeSummaryMessage::nav_offset_amount_open() const { return nav_offset_amount_open_; }
void NextSharesEndOfDayTradeSummaryMessage::set_nav_offset_amount_open(Decimal value) { nav_offset_amount_open_ = value; }

MessageCode NextSharesEndOfDayTradeSummaryMessage::type() const { return message_type; }

std::string_view NextSharesEndOfDayTradeSummaryMessage::name() const { return "Next Shares End Of Day Trade Summary Message"; }

std::size_t NextSharesEndOfDayTradeSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NextSharesEndOfDayTradeSummaryMessage", wire_size, length);

    issue_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    market_category_ = static_cast<MarketCategory>(wire::read_char(data + offset));
    offset += 1;

    consolidated_high_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    nav_offset_amount_high_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    consolidated_low_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    nav_offset_amount_low_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    consolidated_closing_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    nav_offset_amount_closing_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    consolidated_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    consolidated_open_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    nav_offset_amount_open_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    return offset;
}

std::size_t NextSharesEndOfDayTradeSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NextSharesEndOfDayTradeSummaryMessage", wire_size, capacity);

    wire::write_text(data + offset, 8, ' ', issue_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(market_category_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(consolidated_high_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nav_offset_amount_high_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(consolidated_low_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nav_offset_amount_low_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(consolidated_closing_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nav_offset_amount_closing_.mantissa()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_volume_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(consolidated_open_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nav_offset_amount_open_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t NextSharesEndOfDayTradeSummaryMessage::encoded_size() const {
    return wire_size;
}

void NextSharesEndOfDayTradeSummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> NextSharesEndOfDayTradeSummaryMessage::clone() const {
    return std::make_unique<NextSharesEndOfDayTradeSummaryMessage>(*this);
}

void NextSharesEndOfDayTradeSummaryMessage::print(std::ostream& out) const {
    out << "NextSharesEndOfDayTradeSummaryMessage{";
    out << "issue_symbol=";
    print::text(out, issue_symbol_);
    out << ", market_category=";
    out << market_category_;
    out << ", consolidated_high_price=";
    out << consolidated_high_price_;
    out << ", nav_offset_amount_high=";
    out << nav_offset_amount_high_;
    out << ", consolidated_low_price=";
    out << consolidated_low_price_;
    out << ", nav_offset_amount_low=";
    out << nav_offset_amount_low_;
    out << ", consolidated_closing_price=";
    out << consolidated_closing_price_;
    out << ", nav_offset_amount_closing=";
    out << nav_offset_amount_closing_;
    out << ", consolidated_volume=";
    out << consolidated_volume_;
    out << ", consolidated_open_price=";
    out << consolidated_open_price_;
    out << ", nav_offset_amount_open=";
    out << nav_offset_amount_open_;
    out << '}';
}

bool NextSharesEndOfDayTradeSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const NextSharesEndOfDayTradeSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool NextSharesEndOfDayTradeSummaryMessage::operator==(const NextSharesEndOfDayTradeSummaryMessage& other) const {
    return issue_symbol_ == other.issue_symbol_
        && market_category_ == other.market_category_
        && consolidated_high_price_ == other.consolidated_high_price_
        && nav_offset_amount_high_ == other.nav_offset_amount_high_
        && consolidated_low_price_ == other.consolidated_low_price_
        && nav_offset_amount_low_ == other.nav_offset_amount_low_
        && consolidated_closing_price_ == other.consolidated_closing_price_
        && nav_offset_amount_closing_ == other.nav_offset_amount_closing_
        && consolidated_volume_ == other.consolidated_volume_
        && consolidated_open_price_ == other.consolidated_open_price_
        && nav_offset_amount_open_ == other.nav_offset_amount_open_;
}

bool NextSharesEndOfDayTradeSummaryMessage::operator!=(const NextSharesEndOfDayTradeSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
