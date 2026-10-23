#include "EndOfDaySummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

EndOfDaySummaryMessage::EndOfDaySummaryMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, std::uint32_t trade_date, std::uint32_t open_interest, Decimal high_price, Decimal low_price, Decimal open_price, Decimal close_price, std::uint32_t total_volume, std::uint32_t block_volume, std::uint32_t ecrp_volume, const SummaryFlags& summary_flags)
  : time_offset_(time_offset), symbol_(symbol), trade_date_(trade_date), open_interest_(open_interest), high_price_(high_price), low_price_(low_price), open_price_(open_price), close_price_(close_price), total_volume_(total_volume), block_volume_(block_volume), ecrp_volume_(ecrp_volume), summary_flags_(summary_flags) {}

std::chrono::nanoseconds EndOfDaySummaryMessage::time_offset() const { return time_offset_; }
void EndOfDaySummaryMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& EndOfDaySummaryMessage::symbol() const { return symbol_; }
std::string& EndOfDaySummaryMessage::symbol() { return symbol_; }
void EndOfDaySummaryMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint32_t EndOfDaySummaryMessage::trade_date() const { return trade_date_; }
void EndOfDaySummaryMessage::set_trade_date(std::uint32_t value) { trade_date_ = value; }

std::uint32_t EndOfDaySummaryMessage::open_interest() const { return open_interest_; }
void EndOfDaySummaryMessage::set_open_interest(std::uint32_t value) { open_interest_ = value; }

Decimal EndOfDaySummaryMessage::high_price() const { return high_price_; }
void EndOfDaySummaryMessage::set_high_price(Decimal value) { high_price_ = value; }

Decimal EndOfDaySummaryMessage::low_price() const { return low_price_; }
void EndOfDaySummaryMessage::set_low_price(Decimal value) { low_price_ = value; }

Decimal EndOfDaySummaryMessage::open_price() const { return open_price_; }
void EndOfDaySummaryMessage::set_open_price(Decimal value) { open_price_ = value; }

Decimal EndOfDaySummaryMessage::close_price() const { return close_price_; }
void EndOfDaySummaryMessage::set_close_price(Decimal value) { close_price_ = value; }

std::uint32_t EndOfDaySummaryMessage::total_volume() const { return total_volume_; }
void EndOfDaySummaryMessage::set_total_volume(std::uint32_t value) { total_volume_ = value; }

std::uint32_t EndOfDaySummaryMessage::block_volume() const { return block_volume_; }
void EndOfDaySummaryMessage::set_block_volume(std::uint32_t value) { block_volume_ = value; }

std::uint32_t EndOfDaySummaryMessage::ecrp_volume() const { return ecrp_volume_; }
void EndOfDaySummaryMessage::set_ecrp_volume(std::uint32_t value) { ecrp_volume_ = value; }

const SummaryFlags& EndOfDaySummaryMessage::summary_flags() const { return summary_flags_; }
SummaryFlags& EndOfDaySummaryMessage::summary_flags() { return summary_flags_; }
void EndOfDaySummaryMessage::set_summary_flags(const SummaryFlags& value) { summary_flags_ = value; }

MessageCode EndOfDaySummaryMessage::type() const { return message_type; }

std::string_view EndOfDaySummaryMessage::name() const { return "End Of Day Summary Message"; }

std::size_t EndOfDaySummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EndOfDaySummaryMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    trade_date_ = wire::read_u32_le(data + offset);
    offset += 4;

    open_interest_ = wire::read_u32_le(data + offset);
    offset += 4;

    high_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    low_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    open_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    close_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    total_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    block_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    ecrp_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += summary_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t EndOfDaySummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EndOfDaySummaryMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', symbol_);
    offset += 6;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_date_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(open_interest_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(high_price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(low_price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(open_price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(close_price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(total_volume_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(block_volume_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(ecrp_volume_));
    offset += 4;

    offset += summary_flags_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t EndOfDaySummaryMessage::encoded_size() const {
    return wire_size;
}

void EndOfDaySummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EndOfDaySummaryMessage::clone() const {
    return std::make_unique<EndOfDaySummaryMessage>(*this);
}

void EndOfDaySummaryMessage::print(std::ostream& out) const {
    out << "EndOfDaySummaryMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", trade_date=";
    out << trade_date_;
    out << ", open_interest=";
    out << open_interest_;
    out << ", high_price=";
    out << high_price_;
    out << ", low_price=";
    out << low_price_;
    out << ", open_price=";
    out << open_price_;
    out << ", close_price=";
    out << close_price_;
    out << ", total_volume=";
    out << total_volume_;
    out << ", block_volume=";
    out << block_volume_;
    out << ", ecrp_volume=";
    out << ecrp_volume_;
    out << ", summary_flags=";
    summary_flags_.print(out);
    out << '}';
}

bool EndOfDaySummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EndOfDaySummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EndOfDaySummaryMessage::operator==(const EndOfDaySummaryMessage& other) const {
    return time_offset_ == other.time_offset_
        && symbol_ == other.symbol_
        && trade_date_ == other.trade_date_
        && open_interest_ == other.open_interest_
        && high_price_ == other.high_price_
        && low_price_ == other.low_price_
        && open_price_ == other.open_price_
        && close_price_ == other.close_price_
        && total_volume_ == other.total_volume_
        && block_volume_ == other.block_volume_
        && ecrp_volume_ == other.ecrp_volume_
        && summary_flags_ == other.summary_flags_;
}

bool EndOfDaySummaryMessage::operator!=(const EndOfDaySummaryMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
