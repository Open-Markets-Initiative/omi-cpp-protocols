#include "CombinationTradeExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

CombinationTradeExecutedMessage::CombinationTradeExecutedMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, TradeType trade_type, std::uint64_t trade_id, std::uint32_t executed_quantity, Decimal trade_price, std::uint32_t buyer_tradeable_instrument_id, BuyerSide buyer_side, std::uint64_t buyer_order_id, std::uint64_t buyer_combination_trade_id, const std::string& buyer_participant_id, std::uint32_t seller_tradeable_instrument_id, SellerSide seller_side, std::uint64_t seller_order_id, std::uint64_t seller_combination_trade_id, const std::string& seller_participant_id)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), trade_type_(trade_type), trade_id_(trade_id), executed_quantity_(executed_quantity), trade_price_(trade_price), buyer_tradeable_instrument_id_(buyer_tradeable_instrument_id), buyer_side_(buyer_side), buyer_order_id_(buyer_order_id), buyer_combination_trade_id_(buyer_combination_trade_id), buyer_participant_id_(buyer_participant_id), seller_tradeable_instrument_id_(seller_tradeable_instrument_id), seller_side_(seller_side), seller_order_id_(seller_order_id), seller_combination_trade_id_(seller_combination_trade_id), seller_participant_id_(seller_participant_id) {}

std::chrono::nanoseconds CombinationTradeExecutedMessage::nanoseconds() const { return nanoseconds_; }
void CombinationTradeExecutedMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t CombinationTradeExecutedMessage::trade_date() const { return trade_date_; }
void CombinationTradeExecutedMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t CombinationTradeExecutedMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void CombinationTradeExecutedMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

TradeType CombinationTradeExecutedMessage::trade_type() const { return trade_type_; }
void CombinationTradeExecutedMessage::set_trade_type(TradeType value) { trade_type_ = value; }

std::uint64_t CombinationTradeExecutedMessage::trade_id() const { return trade_id_; }
void CombinationTradeExecutedMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

std::uint32_t CombinationTradeExecutedMessage::executed_quantity() const { return executed_quantity_; }
void CombinationTradeExecutedMessage::set_executed_quantity(std::uint32_t value) { executed_quantity_ = value; }

Decimal CombinationTradeExecutedMessage::trade_price() const { return trade_price_; }
void CombinationTradeExecutedMessage::set_trade_price(Decimal value) { trade_price_ = value; }

std::uint32_t CombinationTradeExecutedMessage::buyer_tradeable_instrument_id() const { return buyer_tradeable_instrument_id_; }
void CombinationTradeExecutedMessage::set_buyer_tradeable_instrument_id(std::uint32_t value) { buyer_tradeable_instrument_id_ = value; }

BuyerSide CombinationTradeExecutedMessage::buyer_side() const { return buyer_side_; }
void CombinationTradeExecutedMessage::set_buyer_side(BuyerSide value) { buyer_side_ = value; }

std::uint64_t CombinationTradeExecutedMessage::buyer_order_id() const { return buyer_order_id_; }
void CombinationTradeExecutedMessage::set_buyer_order_id(std::uint64_t value) { buyer_order_id_ = value; }

std::uint64_t CombinationTradeExecutedMessage::buyer_combination_trade_id() const { return buyer_combination_trade_id_; }
void CombinationTradeExecutedMessage::set_buyer_combination_trade_id(std::uint64_t value) { buyer_combination_trade_id_ = value; }

const std::string& CombinationTradeExecutedMessage::buyer_participant_id() const { return buyer_participant_id_; }
std::string& CombinationTradeExecutedMessage::buyer_participant_id() { return buyer_participant_id_; }
void CombinationTradeExecutedMessage::set_buyer_participant_id(const std::string& value) { buyer_participant_id_ = value; }

std::uint32_t CombinationTradeExecutedMessage::seller_tradeable_instrument_id() const { return seller_tradeable_instrument_id_; }
void CombinationTradeExecutedMessage::set_seller_tradeable_instrument_id(std::uint32_t value) { seller_tradeable_instrument_id_ = value; }

SellerSide CombinationTradeExecutedMessage::seller_side() const { return seller_side_; }
void CombinationTradeExecutedMessage::set_seller_side(SellerSide value) { seller_side_ = value; }

std::uint64_t CombinationTradeExecutedMessage::seller_order_id() const { return seller_order_id_; }
void CombinationTradeExecutedMessage::set_seller_order_id(std::uint64_t value) { seller_order_id_ = value; }

std::uint64_t CombinationTradeExecutedMessage::seller_combination_trade_id() const { return seller_combination_trade_id_; }
void CombinationTradeExecutedMessage::set_seller_combination_trade_id(std::uint64_t value) { seller_combination_trade_id_ = value; }

const std::string& CombinationTradeExecutedMessage::seller_participant_id() const { return seller_participant_id_; }
std::string& CombinationTradeExecutedMessage::seller_participant_id() { return seller_participant_id_; }
void CombinationTradeExecutedMessage::set_seller_participant_id(const std::string& value) { seller_participant_id_ = value; }

MessageCode CombinationTradeExecutedMessage::type() const { return message_type; }

std::string_view CombinationTradeExecutedMessage::name() const { return "Combination Trade Executed Message"; }

std::size_t CombinationTradeExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CombinationTradeExecutedMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_type_ = static_cast<TradeType>(wire::read_char(data + offset));
    offset += 1;

    trade_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    executed_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    buyer_tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    buyer_side_ = static_cast<BuyerSide>(wire::read_char(data + offset));
    offset += 1;

    buyer_order_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    buyer_combination_trade_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    buyer_participant_id_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    seller_tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    seller_side_ = static_cast<SellerSide>(wire::read_char(data + offset));
    offset += 1;

    seller_order_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    seller_combination_trade_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    seller_participant_id_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    return offset;
}

std::size_t CombinationTradeExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CombinationTradeExecutedMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(trade_type_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(executed_quantity_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(trade_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(buyer_tradeable_instrument_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(buyer_side_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(buyer_order_id_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(buyer_combination_trade_id_));
    offset += 8;

    wire::write_text(data + offset, 3, ' ', buyer_participant_id_);
    offset += 3;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(seller_tradeable_instrument_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(seller_side_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(seller_order_id_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(seller_combination_trade_id_));
    offset += 8;

    wire::write_text(data + offset, 3, ' ', seller_participant_id_);
    offset += 3;

    return offset;
}

std::size_t CombinationTradeExecutedMessage::encoded_size() const {
    return wire_size;
}

void CombinationTradeExecutedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> CombinationTradeExecutedMessage::clone() const {
    return std::make_unique<CombinationTradeExecutedMessage>(*this);
}

void CombinationTradeExecutedMessage::print(std::ostream& out) const {
    out << "CombinationTradeExecutedMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", tradeable_instrument_id=";
    out << tradeable_instrument_id_;
    out << ", trade_type=";
    out << trade_type_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", executed_quantity=";
    out << executed_quantity_;
    out << ", trade_price=";
    out << trade_price_;
    out << ", buyer_tradeable_instrument_id=";
    out << buyer_tradeable_instrument_id_;
    out << ", buyer_side=";
    out << buyer_side_;
    out << ", buyer_order_id=";
    out << buyer_order_id_;
    out << ", buyer_combination_trade_id=";
    out << buyer_combination_trade_id_;
    out << ", buyer_participant_id=";
    print::text(out, buyer_participant_id_);
    out << ", seller_tradeable_instrument_id=";
    out << seller_tradeable_instrument_id_;
    out << ", seller_side=";
    out << seller_side_;
    out << ", seller_order_id=";
    out << seller_order_id_;
    out << ", seller_combination_trade_id=";
    out << seller_combination_trade_id_;
    out << ", seller_participant_id=";
    print::text(out, seller_participant_id_);
    out << '}';
}

bool CombinationTradeExecutedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const CombinationTradeExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool CombinationTradeExecutedMessage::operator==(const CombinationTradeExecutedMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && trade_type_ == other.trade_type_
        && trade_id_ == other.trade_id_
        && executed_quantity_ == other.executed_quantity_
        && trade_price_ == other.trade_price_
        && buyer_tradeable_instrument_id_ == other.buyer_tradeable_instrument_id_
        && buyer_side_ == other.buyer_side_
        && buyer_order_id_ == other.buyer_order_id_
        && buyer_combination_trade_id_ == other.buyer_combination_trade_id_
        && buyer_participant_id_ == other.buyer_participant_id_
        && seller_tradeable_instrument_id_ == other.seller_tradeable_instrument_id_
        && seller_side_ == other.seller_side_
        && seller_order_id_ == other.seller_order_id_
        && seller_combination_trade_id_ == other.seller_combination_trade_id_
        && seller_participant_id_ == other.seller_participant_id_;
}

bool CombinationTradeExecutedMessage::operator!=(const CombinationTradeExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
