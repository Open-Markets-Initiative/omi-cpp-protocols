#include "TradeCondition.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

TradeCondition::TradeCondition(std::uint8_t trade_condition_length, const std::string& trade_condition_text)
  : trade_condition_length_(trade_condition_length), trade_condition_text_(trade_condition_text) {}

std::uint8_t TradeCondition::trade_condition_length() const { return trade_condition_length_; }
void TradeCondition::set_trade_condition_length(std::uint8_t value) { trade_condition_length_ = value; }

const std::string& TradeCondition::trade_condition_text() const { return trade_condition_text_; }
std::string& TradeCondition::trade_condition_text() { return trade_condition_text_; }
void TradeCondition::set_trade_condition_text(const std::string& value) { trade_condition_text_ = value; }

std::size_t TradeCondition::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("TradeCondition", offset + 1, length);
    trade_condition_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(trade_condition_length_);
        wire::require("TradeCondition", offset + count, length);
        trade_condition_text_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t TradeCondition::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeCondition", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto trade_condition_length = trade_condition_length_;
    trade_condition_length = static_cast<std::uint8_t>(trade_condition_text_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trade_condition_length));
    offset += 1;

    wire::require_capacity("encode", offset + trade_condition_text_.size(), capacity);
    wire::write_text(data + offset, trade_condition_text_.size(), ' ', trade_condition_text_);
    offset += trade_condition_text_.size();

    return offset;
}

std::size_t TradeCondition::encoded_size() const {
    return 1 + trade_condition_text_.size();
}

void TradeCondition::print(std::ostream& out) const {
    out << "TradeCondition{";
    out << "trade_condition_length=";
    out << static_cast<int>(trade_condition_length_);
    out << ", trade_condition_text=";
    print::text(out, trade_condition_text_);
    out << '}';
}

bool TradeCondition::operator==(const TradeCondition& other) const {
    return trade_condition_length_ == other.trade_condition_length_
        && trade_condition_text_ == other.trade_condition_text_;
}

bool TradeCondition::operator!=(const TradeCondition& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const TradeCondition& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
