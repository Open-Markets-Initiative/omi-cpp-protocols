#include "RequestForQuoteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

RequestForQuoteMessage::RequestForQuoteMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, RfqSide rfq_side, std::uint32_t quantity)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), rfq_side_(rfq_side), quantity_(quantity) {}

std::chrono::nanoseconds RequestForQuoteMessage::nanoseconds() const { return nanoseconds_; }
void RequestForQuoteMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t RequestForQuoteMessage::trade_date() const { return trade_date_; }
void RequestForQuoteMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t RequestForQuoteMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void RequestForQuoteMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

RfqSide RequestForQuoteMessage::rfq_side() const { return rfq_side_; }
void RequestForQuoteMessage::set_rfq_side(RfqSide value) { rfq_side_ = value; }

std::uint32_t RequestForQuoteMessage::quantity() const { return quantity_; }
void RequestForQuoteMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

MessageCode RequestForQuoteMessage::type() const { return message_type; }

std::string_view RequestForQuoteMessage::name() const { return "Request For Quote Message"; }

std::size_t RequestForQuoteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RequestForQuoteMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    rfq_side_ = static_cast<RfqSide>(wire::read_char(data + offset));
    offset += 1;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t RequestForQuoteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RequestForQuoteMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(rfq_side_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    return offset;
}

std::size_t RequestForQuoteMessage::encoded_size() const {
    return wire_size;
}

void RequestForQuoteMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RequestForQuoteMessage::clone() const {
    return std::make_unique<RequestForQuoteMessage>(*this);
}

void RequestForQuoteMessage::print(std::ostream& out) const {
    out << "RequestForQuoteMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", tradeable_instrument_id=";
    out << tradeable_instrument_id_;
    out << ", rfq_side=";
    out << rfq_side_;
    out << ", quantity=";
    out << quantity_;
    out << '}';
}

bool RequestForQuoteMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RequestForQuoteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RequestForQuoteMessage::operator==(const RequestForQuoteMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && rfq_side_ == other.rfq_side_
        && quantity_ == other.quantity_;
}

bool RequestForQuoteMessage::operator!=(const RequestForQuoteMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
