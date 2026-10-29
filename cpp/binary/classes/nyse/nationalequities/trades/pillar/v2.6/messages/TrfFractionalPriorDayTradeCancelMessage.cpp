#include "TrfFractionalPriorDayTradeCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

TrfFractionalPriorDayTradeCancelMessage::TrfFractionalPriorDayTradeCancelMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t trade_id, std::int32_t price, std::uint64_t fractional_volume, std::uint32_t prior_day_time, std::uint32_t prior_day_time_ns)
  : source_time_(source_time), source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), trade_id_(trade_id), price_(price), fractional_volume_(fractional_volume), prior_day_time_(prior_day_time), prior_day_time_ns_(prior_day_time_ns) {}

std::uint32_t TrfFractionalPriorDayTradeCancelMessage::source_time() const { return source_time_; }
void TrfFractionalPriorDayTradeCancelMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t TrfFractionalPriorDayTradeCancelMessage::source_time_ns() const { return source_time_ns_; }
void TrfFractionalPriorDayTradeCancelMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t TrfFractionalPriorDayTradeCancelMessage::symbol_index() const { return symbol_index_; }
void TrfFractionalPriorDayTradeCancelMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t TrfFractionalPriorDayTradeCancelMessage::symbol_seq_num() const { return symbol_seq_num_; }
void TrfFractionalPriorDayTradeCancelMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint32_t TrfFractionalPriorDayTradeCancelMessage::trade_id() const { return trade_id_; }
void TrfFractionalPriorDayTradeCancelMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::int32_t TrfFractionalPriorDayTradeCancelMessage::price() const { return price_; }
void TrfFractionalPriorDayTradeCancelMessage::set_price(std::int32_t value) { price_ = value; }

std::uint64_t TrfFractionalPriorDayTradeCancelMessage::fractional_volume() const { return fractional_volume_; }
void TrfFractionalPriorDayTradeCancelMessage::set_fractional_volume(std::uint64_t value) { fractional_volume_ = value; }

std::uint32_t TrfFractionalPriorDayTradeCancelMessage::prior_day_time() const { return prior_day_time_; }
void TrfFractionalPriorDayTradeCancelMessage::set_prior_day_time(std::uint32_t value) { prior_day_time_ = value; }

std::uint32_t TrfFractionalPriorDayTradeCancelMessage::prior_day_time_ns() const { return prior_day_time_ns_; }
void TrfFractionalPriorDayTradeCancelMessage::set_prior_day_time_ns(std::uint32_t value) { prior_day_time_ns_ = value; }

MessageCode TrfFractionalPriorDayTradeCancelMessage::type() const { return message_type; }

std::string_view TrfFractionalPriorDayTradeCancelMessage::name() const { return "Trf Fractional Prior Day Trade Cancel Message"; }

std::size_t TrfFractionalPriorDayTradeCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TrfFractionalPriorDayTradeCancelMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = wire::read_i32_le(data + offset);
    offset += 4;

    fractional_volume_ = wire::read_u64_le(data + offset);
    offset += 8;

    prior_day_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    prior_day_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t TrfFractionalPriorDayTradeCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TrfFractionalPriorDayTradeCancelMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(fractional_volume_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(prior_day_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(prior_day_time_ns_));
    offset += 4;

    return offset;
}

std::size_t TrfFractionalPriorDayTradeCancelMessage::encoded_size() const {
    return wire_size;
}

void TrfFractionalPriorDayTradeCancelMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TrfFractionalPriorDayTradeCancelMessage::clone() const {
    return std::make_unique<TrfFractionalPriorDayTradeCancelMessage>(*this);
}

void TrfFractionalPriorDayTradeCancelMessage::print(std::ostream& out) const {
    out << "TrfFractionalPriorDayTradeCancelMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", price=";
    out << price_;
    out << ", fractional_volume=";
    out << fractional_volume_;
    out << ", prior_day_time=";
    out << prior_day_time_;
    out << ", prior_day_time_ns=";
    out << prior_day_time_ns_;
    out << '}';
}

bool TrfFractionalPriorDayTradeCancelMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TrfFractionalPriorDayTradeCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TrfFractionalPriorDayTradeCancelMessage::operator==(const TrfFractionalPriorDayTradeCancelMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && trade_id_ == other.trade_id_
        && price_ == other.price_
        && fractional_volume_ == other.fractional_volume_
        && prior_day_time_ == other.prior_day_time_
        && prior_day_time_ns_ == other.prior_day_time_ns_;
}

bool TrfFractionalPriorDayTradeCancelMessage::operator!=(const TrfFractionalPriorDayTradeCancelMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
