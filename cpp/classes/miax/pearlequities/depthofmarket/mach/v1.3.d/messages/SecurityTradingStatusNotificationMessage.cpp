#include "SecurityTradingStatusNotificationMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

SecurityTradingStatusNotificationMessage::SecurityTradingStatusNotificationMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, TradingStatus trading_status, MarketState market_state, ShortSaleRestriction short_sale_restriction)
  : nanoseconds_(nanoseconds), symbol_id_(symbol_id), trading_status_(trading_status), market_state_(market_state), short_sale_restriction_(short_sale_restriction) {}

std::chrono::nanoseconds SecurityTradingStatusNotificationMessage::nanoseconds() const { return nanoseconds_; }
void SecurityTradingStatusNotificationMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t SecurityTradingStatusNotificationMessage::symbol_id() const { return symbol_id_; }
void SecurityTradingStatusNotificationMessage::set_symbol_id(std::uint32_t value) { symbol_id_ = value; }

TradingStatus SecurityTradingStatusNotificationMessage::trading_status() const { return trading_status_; }
void SecurityTradingStatusNotificationMessage::set_trading_status(TradingStatus value) { trading_status_ = value; }

MarketState SecurityTradingStatusNotificationMessage::market_state() const { return market_state_; }
void SecurityTradingStatusNotificationMessage::set_market_state(MarketState value) { market_state_ = value; }

ShortSaleRestriction SecurityTradingStatusNotificationMessage::short_sale_restriction() const { return short_sale_restriction_; }
void SecurityTradingStatusNotificationMessage::set_short_sale_restriction(ShortSaleRestriction value) { short_sale_restriction_ = value; }

DataCode SecurityTradingStatusNotificationMessage::type() const { return message_type; }

std::string_view SecurityTradingStatusNotificationMessage::name() const { return "Security Trading Status Notification Message"; }

std::size_t SecurityTradingStatusNotificationMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityTradingStatusNotificationMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    trading_status_ = static_cast<TradingStatus>(wire::read_u8(data + offset));
    offset += 1;

    market_state_ = static_cast<MarketState>(wire::read_u8(data + offset));
    offset += 1;

    short_sale_restriction_ = static_cast<ShortSaleRestriction>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SecurityTradingStatusNotificationMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityTradingStatusNotificationMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(market_state_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(short_sale_restriction_));
    offset += 1;

    return offset;
}

std::size_t SecurityTradingStatusNotificationMessage::encoded_size() const {
    return wire_size;
}

void SecurityTradingStatusNotificationMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> SecurityTradingStatusNotificationMessage::clone() const {
    return std::make_unique<SecurityTradingStatusNotificationMessage>(*this);
}

void SecurityTradingStatusNotificationMessage::print(std::ostream& out) const {
    out << "SecurityTradingStatusNotificationMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", symbol_id=";
    out << symbol_id_;
    out << ", trading_status=";
    out << trading_status_;
    out << ", market_state=";
    out << market_state_;
    out << ", short_sale_restriction=";
    out << short_sale_restriction_;
    out << '}';
}

bool SecurityTradingStatusNotificationMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const SecurityTradingStatusNotificationMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityTradingStatusNotificationMessage::operator==(const SecurityTradingStatusNotificationMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && symbol_id_ == other.symbol_id_
        && trading_status_ == other.trading_status_
        && market_state_ == other.market_state_
        && short_sale_restriction_ == other.short_sale_restriction_;
}

bool SecurityTradingStatusNotificationMessage::operator!=(const SecurityTradingStatusNotificationMessage& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
