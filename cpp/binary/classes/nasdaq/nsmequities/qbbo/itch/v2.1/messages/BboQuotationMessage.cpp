#include "BboQuotationMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

BboQuotationMessage::BboQuotationMessage(std::uint16_t tracking_number, std::chrono::nanoseconds time_stamp, const std::string& stock, SecurityClass security_class, Decimal best_bid_price, std::uint32_t best_bid_size, Decimal best_offer_price, std::uint32_t best_offer_size)
  : tracking_number_(tracking_number), time_stamp_(time_stamp), stock_(stock), security_class_(security_class), best_bid_price_(best_bid_price), best_bid_size_(best_bid_size), best_offer_price_(best_offer_price), best_offer_size_(best_offer_size) {}

std::uint16_t BboQuotationMessage::tracking_number() const { return tracking_number_; }
void BboQuotationMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds BboQuotationMessage::time_stamp() const { return time_stamp_; }
void BboQuotationMessage::set_time_stamp(std::chrono::nanoseconds value) { time_stamp_ = value; }
std::int64_t BboQuotationMessage::time_stamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(time_stamp_.count())); }

const std::string& BboQuotationMessage::stock() const { return stock_; }
std::string& BboQuotationMessage::stock() { return stock_; }
void BboQuotationMessage::set_stock(const std::string& value) { stock_ = value; }

SecurityClass BboQuotationMessage::security_class() const { return security_class_; }
void BboQuotationMessage::set_security_class(SecurityClass value) { security_class_ = value; }

Decimal BboQuotationMessage::best_bid_price() const { return best_bid_price_; }
void BboQuotationMessage::set_best_bid_price(Decimal value) { best_bid_price_ = value; }

std::uint32_t BboQuotationMessage::best_bid_size() const { return best_bid_size_; }
void BboQuotationMessage::set_best_bid_size(std::uint32_t value) { best_bid_size_ = value; }

Decimal BboQuotationMessage::best_offer_price() const { return best_offer_price_; }
void BboQuotationMessage::set_best_offer_price(Decimal value) { best_offer_price_ = value; }

std::uint32_t BboQuotationMessage::best_offer_size() const { return best_offer_size_; }
void BboQuotationMessage::set_best_offer_size(std::uint32_t value) { best_offer_size_ = value; }

MessageCode BboQuotationMessage::type() const { return message_type; }

std::string_view BboQuotationMessage::name() const { return "Bbo Quotation Message"; }

std::size_t BboQuotationMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BboQuotationMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    time_stamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    security_class_ = static_cast<SecurityClass>(wire::read_char(data + offset));
    offset += 1;

    best_bid_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    best_bid_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    best_offer_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    best_offer_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t BboQuotationMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BboQuotationMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(time_stamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(security_class_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(best_bid_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(best_bid_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(best_offer_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(best_offer_size_));
    offset += 4;

    return offset;
}

std::size_t BboQuotationMessage::encoded_size() const {
    return wire_size;
}

void BboQuotationMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> BboQuotationMessage::clone() const {
    return std::make_unique<BboQuotationMessage>(*this);
}

void BboQuotationMessage::print(std::ostream& out) const {
    out << "BboQuotationMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", time_stamp=";
    calendar::print(out, time_stamp_.count(), 1, "America/New_York");
    out << ", stock=";
    print::text(out, stock_);
    out << ", security_class=";
    out << security_class_;
    out << ", best_bid_price=";
    out << best_bid_price_;
    out << ", best_bid_size=";
    out << best_bid_size_;
    out << ", best_offer_price=";
    out << best_offer_price_;
    out << ", best_offer_size=";
    out << best_offer_size_;
    out << '}';
}

bool BboQuotationMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const BboQuotationMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool BboQuotationMessage::operator==(const BboQuotationMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && time_stamp_ == other.time_stamp_
        && stock_ == other.stock_
        && security_class_ == other.security_class_
        && best_bid_price_ == other.best_bid_price_
        && best_bid_size_ == other.best_bid_size_
        && best_offer_price_ == other.best_offer_price_
        && best_offer_size_ == other.best_offer_size_;
}

bool BboQuotationMessage::operator!=(const BboQuotationMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
