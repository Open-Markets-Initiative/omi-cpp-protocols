#include "ExecutionSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

ExecutionSummaryMessage::ExecutionSummaryMessage(std::chrono::microseconds time_microseconds, TriggeredSide triggered_side, std::uint64_t total_volume, std::uint64_t total_invalidation, Decimal last_price, std::uint32_t match_id, std::optional<Decimal> best_offer, std::optional<Decimal> best_bid)
  : time_microseconds_(time_microseconds), triggered_side_(triggered_side), total_volume_(total_volume), total_invalidation_(total_invalidation), last_price_(last_price), match_id_(match_id), best_offer_(best_offer), best_bid_(best_bid) {}

std::chrono::microseconds ExecutionSummaryMessage::time_microseconds() const { return time_microseconds_; }
void ExecutionSummaryMessage::set_time_microseconds(std::chrono::microseconds value) { time_microseconds_ = value; }

TriggeredSide ExecutionSummaryMessage::triggered_side() const { return triggered_side_; }
void ExecutionSummaryMessage::set_triggered_side(TriggeredSide value) { triggered_side_ = value; }

std::uint64_t ExecutionSummaryMessage::total_volume() const { return total_volume_; }
void ExecutionSummaryMessage::set_total_volume(std::uint64_t value) { total_volume_ = value; }

std::uint64_t ExecutionSummaryMessage::total_invalidation() const { return total_invalidation_; }
void ExecutionSummaryMessage::set_total_invalidation(std::uint64_t value) { total_invalidation_ = value; }

Decimal ExecutionSummaryMessage::last_price() const { return last_price_; }
void ExecutionSummaryMessage::set_last_price(Decimal value) { last_price_ = value; }

std::uint32_t ExecutionSummaryMessage::match_id() const { return match_id_; }
void ExecutionSummaryMessage::set_match_id(std::uint32_t value) { match_id_ = value; }

std::optional<Decimal> ExecutionSummaryMessage::best_offer() const { return best_offer_; }
void ExecutionSummaryMessage::set_best_offer(std::optional<Decimal> value) { best_offer_ = value; }

std::optional<Decimal> ExecutionSummaryMessage::best_bid() const { return best_bid_; }
void ExecutionSummaryMessage::set_best_bid(std::optional<Decimal> value) { best_bid_ = value; }

MessageCode ExecutionSummaryMessage::type() const { return message_type; }

std::string_view ExecutionSummaryMessage::name() const { return "Execution Summary Message"; }

std::size_t ExecutionSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ExecutionSummaryMessage", wire_size, length);

    time_microseconds_ = std::chrono::microseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    triggered_side_ = static_cast<TriggeredSide>(wire::read_char(data + offset));
    offset += 1;

    total_volume_ = wire::read_u48_be(data + offset);
    offset += 6;

    total_invalidation_ = wire::read_u48_be(data + offset);
    offset += 6;

    last_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -4);
    offset += 8;

    match_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    best_offer_ = wire::nullable_decimal(wire::read_u64_be(data + offset), static_cast<std::uint64_t>(0ULL), -4);
    offset += 8;

    best_bid_ = wire::nullable_decimal(wire::read_u64_be(data + offset), static_cast<std::uint64_t>(0ULL), -4);
    offset += 8;

    return offset;
}

std::size_t ExecutionSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExecutionSummaryMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(time_microseconds_.count()));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(triggered_side_));
    offset += 1;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(total_volume_));
    offset += 6;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(total_invalidation_));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(last_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(match_id_));
    offset += 4;

    wire::write_u64_be(data + offset, best_offer_ ? static_cast<std::uint64_t>(best_offer_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u64_be(data + offset, best_bid_ ? static_cast<std::uint64_t>(best_bid_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t ExecutionSummaryMessage::encoded_size() const {
    return wire_size;
}

void ExecutionSummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExecutionSummaryMessage::clone() const {
    return std::make_unique<ExecutionSummaryMessage>(*this);
}

void ExecutionSummaryMessage::print(std::ostream& out) const {
    out << "ExecutionSummaryMessage{";
    out << "time_microseconds=";
    out << time_microseconds_.count();
    out << ", triggered_side=";
    out << triggered_side_;
    out << ", total_volume=";
    out << total_volume_;
    out << ", total_invalidation=";
    out << total_invalidation_;
    out << ", last_price=";
    out << last_price_;
    out << ", match_id=";
    out << match_id_;
    out << ", best_offer=";
    print::optional(out, best_offer_);
    out << ", best_bid=";
    print::optional(out, best_bid_);
    out << '}';
}

bool ExecutionSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExecutionSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ExecutionSummaryMessage::operator==(const ExecutionSummaryMessage& other) const {
    return time_microseconds_ == other.time_microseconds_
        && triggered_side_ == other.triggered_side_
        && total_volume_ == other.total_volume_
        && total_invalidation_ == other.total_invalidation_
        && last_price_ == other.last_price_
        && match_id_ == other.match_id_
        && best_offer_ == other.best_offer_
        && best_bid_ == other.best_bid_;
}

bool ExecutionSummaryMessage::operator!=(const ExecutionSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
