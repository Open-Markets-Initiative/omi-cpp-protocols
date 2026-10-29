#include "RetailInterestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

RetailInterestMessage::RetailInterestMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, InterestFlag interest_flag)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), stock_(stock), interest_flag_(interest_flag) {}

std::uint16_t RetailInterestMessage::stock_locate() const { return stock_locate_; }
void RetailInterestMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t RetailInterestMessage::tracking_number() const { return tracking_number_; }
void RetailInterestMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds RetailInterestMessage::timestamp() const { return timestamp_; }
void RetailInterestMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t RetailInterestMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

const std::string& RetailInterestMessage::stock() const { return stock_; }
std::string& RetailInterestMessage::stock() { return stock_; }
void RetailInterestMessage::set_stock(const std::string& value) { stock_ = value; }

InterestFlag RetailInterestMessage::interest_flag() const { return interest_flag_; }
void RetailInterestMessage::set_interest_flag(InterestFlag value) { interest_flag_ = value; }

MessageCode RetailInterestMessage::type() const { return message_type; }

std::string_view RetailInterestMessage::name() const { return "Retail Interest Message"; }

std::size_t RetailInterestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RetailInterestMessage", wire_size, length);

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

std::size_t RetailInterestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RetailInterestMessage", wire_size, capacity);

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

std::size_t RetailInterestMessage::encoded_size() const {
    return wire_size;
}

void RetailInterestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RetailInterestMessage::clone() const {
    return std::make_unique<RetailInterestMessage>(*this);
}

void RetailInterestMessage::print(std::ostream& out) const {
    out << "RetailInterestMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", stock=";
    print::text(out, stock_);
    out << ", interest_flag=";
    out << interest_flag_;
    out << '}';
}

bool RetailInterestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RetailInterestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RetailInterestMessage::operator==(const RetailInterestMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && stock_ == other.stock_
        && interest_flag_ == other.interest_flag_;
}

bool RetailInterestMessage::operator!=(const RetailInterestMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
