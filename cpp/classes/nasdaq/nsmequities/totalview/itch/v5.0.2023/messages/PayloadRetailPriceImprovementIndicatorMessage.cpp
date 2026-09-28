#include "PayloadRetailPriceImprovementIndicatorMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

PayloadRetailPriceImprovementIndicatorMessage::PayloadRetailPriceImprovementIndicatorMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, InterestFlag interest_flag)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), stock_(stock), interest_flag_(interest_flag) {}

std::uint16_t PayloadRetailPriceImprovementIndicatorMessage::stock_locate() const { return stock_locate_; }
void PayloadRetailPriceImprovementIndicatorMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t PayloadRetailPriceImprovementIndicatorMessage::tracking_number() const { return tracking_number_; }
void PayloadRetailPriceImprovementIndicatorMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds PayloadRetailPriceImprovementIndicatorMessage::timestamp() const { return timestamp_; }
void PayloadRetailPriceImprovementIndicatorMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& PayloadRetailPriceImprovementIndicatorMessage::stock() const { return stock_; }
std::string& PayloadRetailPriceImprovementIndicatorMessage::stock() { return stock_; }
void PayloadRetailPriceImprovementIndicatorMessage::set_stock(const std::string& value) { stock_ = value; }

InterestFlag PayloadRetailPriceImprovementIndicatorMessage::interest_flag() const { return interest_flag_; }
void PayloadRetailPriceImprovementIndicatorMessage::set_interest_flag(InterestFlag value) { interest_flag_ = value; }

PacketMessageCode PayloadRetailPriceImprovementIndicatorMessage::type() const { return message_type; }

std::string_view PayloadRetailPriceImprovementIndicatorMessage::name() const { return "Retail Price Improvement Indicator Message"; }

std::size_t PayloadRetailPriceImprovementIndicatorMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadRetailPriceImprovementIndicatorMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    interest_flag_ = static_cast<InterestFlag>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t PayloadRetailPriceImprovementIndicatorMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadRetailPriceImprovementIndicatorMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(interest_flag_));
    offset += 1;

    return offset;
}

std::size_t PayloadRetailPriceImprovementIndicatorMessage::encoded_size() const {
    return wire_size;
}

void PayloadRetailPriceImprovementIndicatorMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadRetailPriceImprovementIndicatorMessage::clone() const {
    return std::make_unique<PayloadRetailPriceImprovementIndicatorMessage>(*this);
}

void PayloadRetailPriceImprovementIndicatorMessage::print(std::ostream& out) const {
    out << "PayloadRetailPriceImprovementIndicatorMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", stock=";
    print::text(out, stock_);
    out << ", interest_flag=";
    out << interest_flag_;
    out << '}';
}

bool PayloadRetailPriceImprovementIndicatorMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadRetailPriceImprovementIndicatorMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadRetailPriceImprovementIndicatorMessage::operator==(const PayloadRetailPriceImprovementIndicatorMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && stock_ == other.stock_
        && interest_flag_ == other.interest_flag_;
}

bool PayloadRetailPriceImprovementIndicatorMessage::operator!=(const PayloadRetailPriceImprovementIndicatorMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
