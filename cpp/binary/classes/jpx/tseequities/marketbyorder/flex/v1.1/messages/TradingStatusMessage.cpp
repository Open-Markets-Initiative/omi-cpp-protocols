#include "TradingStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

TradingStatusMessage::TradingStatusMessage(std::chrono::microseconds time_microseconds, MarketStatus market_status, const std::string& status_flag, ShortSellingStatus short_selling_status, PricingMethod pricing_method, Decimal book_center_price)
  : time_microseconds_(time_microseconds), market_status_(market_status), status_flag_(status_flag), short_selling_status_(short_selling_status), pricing_method_(pricing_method), book_center_price_(book_center_price) {}

std::chrono::microseconds TradingStatusMessage::time_microseconds() const { return time_microseconds_; }
void TradingStatusMessage::set_time_microseconds(std::chrono::microseconds value) { time_microseconds_ = value; }

MarketStatus TradingStatusMessage::market_status() const { return market_status_; }
void TradingStatusMessage::set_market_status(MarketStatus value) { market_status_ = value; }

const std::string& TradingStatusMessage::status_flag() const { return status_flag_; }
std::string& TradingStatusMessage::status_flag() { return status_flag_; }
void TradingStatusMessage::set_status_flag(const std::string& value) { status_flag_ = value; }

ShortSellingStatus TradingStatusMessage::short_selling_status() const { return short_selling_status_; }
void TradingStatusMessage::set_short_selling_status(ShortSellingStatus value) { short_selling_status_ = value; }

PricingMethod TradingStatusMessage::pricing_method() const { return pricing_method_; }
void TradingStatusMessage::set_pricing_method(PricingMethod value) { pricing_method_ = value; }

Decimal TradingStatusMessage::book_center_price() const { return book_center_price_; }
void TradingStatusMessage::set_book_center_price(Decimal value) { book_center_price_ = value; }

MessageCode TradingStatusMessage::type() const { return message_type; }

std::string_view TradingStatusMessage::name() const { return "Trading Status Message"; }

std::size_t TradingStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradingStatusMessage", wire_size, length);

    time_microseconds_ = std::chrono::microseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    market_status_ = static_cast<MarketStatus>(wire::read_u8(data + offset));
    offset += 1;

    status_flag_ = wire::read_text(data + offset, 2, ' ');
    offset += 2;

    short_selling_status_ = static_cast<ShortSellingStatus>(wire::read_u8(data + offset));
    offset += 1;

    pricing_method_ = static_cast<PricingMethod>(wire::read_u8(data + offset));
    offset += 1;

    book_center_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t TradingStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingStatusMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(time_microseconds_.count()));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(market_status_));
    offset += 1;

    wire::write_text(data + offset, 2, ' ', status_flag_);
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(short_selling_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(pricing_method_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(book_center_price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t TradingStatusMessage::encoded_size() const {
    return wire_size;
}

void TradingStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradingStatusMessage::clone() const {
    return std::make_unique<TradingStatusMessage>(*this);
}

void TradingStatusMessage::print(std::ostream& out) const {
    out << "TradingStatusMessage{";
    out << "time_microseconds=";
    out << time_microseconds_.count();
    out << ", market_status=";
    out << market_status_;
    out << ", status_flag=";
    print::text(out, status_flag_);
    out << ", short_selling_status=";
    out << short_selling_status_;
    out << ", pricing_method=";
    out << pricing_method_;
    out << ", book_center_price=";
    out << book_center_price_;
    out << '}';
}

bool TradingStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradingStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradingStatusMessage::operator==(const TradingStatusMessage& other) const {
    return time_microseconds_ == other.time_microseconds_
        && market_status_ == other.market_status_
        && status_flag_ == other.status_flag_
        && short_selling_status_ == other.short_selling_status_
        && pricing_method_ == other.pricing_method_
        && book_center_price_ == other.book_center_price_;
}

bool TradingStatusMessage::operator!=(const TradingStatusMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
