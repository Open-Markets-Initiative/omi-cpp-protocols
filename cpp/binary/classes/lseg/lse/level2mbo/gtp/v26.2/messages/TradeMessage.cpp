#include "TradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

TradeMessage::TradeMessage(std::chrono::nanoseconds timestamp, std::chrono::nanoseconds transaction_time, SourceVenue source_venue, Decimal executed_size, std::uint64_t instrument, Decimal price, const std::array<std::byte, 8>& reserved_8, std::uint64_t trade_id, TradeType trade_type, AuctionType auction_type, const TradeFlags& trade_flags, HiddenExecutionIndicator hidden_execution_indicator, TradeQualifier trade_qualifier)
  : timestamp_(timestamp), transaction_time_(transaction_time), source_venue_(source_venue), executed_size_(executed_size), instrument_(instrument), price_(price), reserved_8_(reserved_8), trade_id_(trade_id), trade_type_(trade_type), auction_type_(auction_type), trade_flags_(trade_flags), hidden_execution_indicator_(hidden_execution_indicator), trade_qualifier_(trade_qualifier) {}

std::chrono::nanoseconds TradeMessage::timestamp() const { return timestamp_; }
void TradeMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::chrono::nanoseconds TradeMessage::transaction_time() const { return transaction_time_; }
void TradeMessage::set_transaction_time(std::chrono::nanoseconds value) { transaction_time_ = value; }

SourceVenue TradeMessage::source_venue() const { return source_venue_; }
void TradeMessage::set_source_venue(SourceVenue value) { source_venue_ = value; }

Decimal TradeMessage::executed_size() const { return executed_size_; }
void TradeMessage::set_executed_size(Decimal value) { executed_size_ = value; }

std::uint64_t TradeMessage::instrument() const { return instrument_; }
void TradeMessage::set_instrument(std::uint64_t value) { instrument_ = value; }

Decimal TradeMessage::price() const { return price_; }
void TradeMessage::set_price(Decimal value) { price_ = value; }

const std::array<std::byte, 8>& TradeMessage::reserved_8() const { return reserved_8_; }
std::array<std::byte, 8>& TradeMessage::reserved_8() { return reserved_8_; }
void TradeMessage::set_reserved_8(const std::array<std::byte, 8>& value) { reserved_8_ = value; }

std::uint64_t TradeMessage::trade_id() const { return trade_id_; }
void TradeMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

TradeType TradeMessage::trade_type() const { return trade_type_; }
void TradeMessage::set_trade_type(TradeType value) { trade_type_ = value; }

AuctionType TradeMessage::auction_type() const { return auction_type_; }
void TradeMessage::set_auction_type(AuctionType value) { auction_type_ = value; }

const TradeFlags& TradeMessage::trade_flags() const { return trade_flags_; }
TradeFlags& TradeMessage::trade_flags() { return trade_flags_; }
void TradeMessage::set_trade_flags(const TradeFlags& value) { trade_flags_ = value; }

HiddenExecutionIndicator TradeMessage::hidden_execution_indicator() const { return hidden_execution_indicator_; }
void TradeMessage::set_hidden_execution_indicator(HiddenExecutionIndicator value) { hidden_execution_indicator_ = value; }

TradeQualifier TradeMessage::trade_qualifier() const { return trade_qualifier_; }
void TradeMessage::set_trade_qualifier(TradeQualifier value) { trade_qualifier_ = value; }

MessageCode TradeMessage::type() const { return message_type; }

std::string_view TradeMessage::name() const { return "Trade Message"; }

std::size_t TradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    transaction_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    source_venue_ = static_cast<SourceVenue>(wire::read_u16_le(data + offset));
    offset += 2;

    executed_size_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -8);
    offset += 8;

    instrument_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -8);
    offset += 8;

    wire::read_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    trade_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    trade_type_ = static_cast<TradeType>(wire::read_u8(data + offset));
    offset += 1;

    auction_type_ = static_cast<AuctionType>(wire::read_char(data + offset));
    offset += 1;

    offset += trade_flags_.decode(data + offset, length - offset);

    hidden_execution_indicator_ = static_cast<HiddenExecutionIndicator>(wire::read_u8(data + offset));
    offset += 1;

    trade_qualifier_ = static_cast<TradeQualifier>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t TradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transaction_time_.count()));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(source_venue_));
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(executed_size_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(instrument_));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trade_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(auction_type_));
    offset += 1;

    offset += trade_flags_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(hidden_execution_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_qualifier_));
    offset += 1;

    return offset;
}

std::size_t TradeMessage::encoded_size() const {
    return wire_size;
}

void TradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeMessage::clone() const {
    return std::make_unique<TradeMessage>(*this);
}

void TradeMessage::print(std::ostream& out) const {
    out << "TradeMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", transaction_time=";
    out << transaction_time_.count();
    out << ", source_venue=";
    out << source_venue_;
    out << ", executed_size=";
    out << executed_size_;
    out << ", instrument=";
    out << instrument_;
    out << ", price=";
    out << price_;
    out << ", reserved_8=";
    print::hex(out, reserved_8_.data(), reserved_8_.size());
    out << ", trade_id=";
    out << trade_id_;
    out << ", trade_type=";
    out << trade_type_;
    out << ", auction_type=";
    out << auction_type_;
    out << ", trade_flags=";
    trade_flags_.print(out);
    out << ", hidden_execution_indicator=";
    out << hidden_execution_indicator_;
    out << ", trade_qualifier=";
    out << trade_qualifier_;
    out << '}';
}

bool TradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeMessage::operator==(const TradeMessage& other) const {
    return timestamp_ == other.timestamp_
        && transaction_time_ == other.transaction_time_
        && source_venue_ == other.source_venue_
        && executed_size_ == other.executed_size_
        && instrument_ == other.instrument_
        && price_ == other.price_
        && reserved_8_ == other.reserved_8_
        && trade_id_ == other.trade_id_
        && trade_type_ == other.trade_type_
        && auction_type_ == other.auction_type_
        && trade_flags_ == other.trade_flags_
        && hidden_execution_indicator_ == other.hidden_execution_indicator_
        && trade_qualifier_ == other.trade_qualifier_;
}

bool TradeMessage::operator!=(const TradeMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
