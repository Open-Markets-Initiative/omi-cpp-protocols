#include "SummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

SummaryMessage::SummaryMessage(std::uint32_t class_key, std::uint32_t security_id, std::uint8_t price_type, std::uint32_t trade_volume, std::uint32_t open_interest, const NetChgPrevDay& net_chg_prev_day, const UnderlyingPx& underlying_px, std::uint8_t no_entries, const std::vector<SummaryMdEntry>& summary_md_entry)
  : class_key_(class_key), security_id_(security_id), price_type_(price_type), trade_volume_(trade_volume), open_interest_(open_interest), net_chg_prev_day_(net_chg_prev_day), underlying_px_(underlying_px), no_entries_(no_entries), summary_md_entry_(summary_md_entry) {}

std::uint32_t SummaryMessage::class_key() const { return class_key_; }
void SummaryMessage::set_class_key(std::uint32_t value) { class_key_ = value; }

std::uint32_t SummaryMessage::security_id() const { return security_id_; }
void SummaryMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

std::uint8_t SummaryMessage::price_type() const { return price_type_; }
void SummaryMessage::set_price_type(std::uint8_t value) { price_type_ = value; }

std::uint32_t SummaryMessage::trade_volume() const { return trade_volume_; }
void SummaryMessage::set_trade_volume(std::uint32_t value) { trade_volume_ = value; }

std::uint32_t SummaryMessage::open_interest() const { return open_interest_; }
void SummaryMessage::set_open_interest(std::uint32_t value) { open_interest_ = value; }

const NetChgPrevDay& SummaryMessage::net_chg_prev_day() const { return net_chg_prev_day_; }
NetChgPrevDay& SummaryMessage::net_chg_prev_day() { return net_chg_prev_day_; }
void SummaryMessage::set_net_chg_prev_day(const NetChgPrevDay& value) { net_chg_prev_day_ = value; }

const UnderlyingPx& SummaryMessage::underlying_px() const { return underlying_px_; }
UnderlyingPx& SummaryMessage::underlying_px() { return underlying_px_; }
void SummaryMessage::set_underlying_px(const UnderlyingPx& value) { underlying_px_ = value; }

std::uint8_t SummaryMessage::no_entries() const { return no_entries_; }
void SummaryMessage::set_no_entries(std::uint8_t value) { no_entries_ = value; }

const std::vector<SummaryMdEntry>& SummaryMessage::summary_md_entry() const { return summary_md_entry_; }
std::vector<SummaryMdEntry>& SummaryMessage::summary_md_entry() { return summary_md_entry_; }
void SummaryMessage::set_summary_md_entry(const std::vector<SummaryMdEntry>& value) { summary_md_entry_ = value; }

MessageCode SummaryMessage::type() const { return message_type; }

std::string_view SummaryMessage::name() const { return "Summary Message"; }

std::size_t SummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SummaryMessage", offset + 4, length);
    class_key_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("SummaryMessage", offset + 4, length);
    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("SummaryMessage", offset + 1, length);
    price_type_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("SummaryMessage", offset + 4, length);
    trade_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("SummaryMessage", offset + 4, length);
    open_interest_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += net_chg_prev_day_.decode(data + offset, length - offset);

    offset += underlying_px_.decode(data + offset, length - offset);

    wire::require("SummaryMessage", offset + 1, length);
    no_entries_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(no_entries_);
        summary_md_entry_.clear();
        summary_md_entry_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SummaryMdEntry entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            summary_md_entry_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SummaryMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto no_entries = no_entries_;
    no_entries = static_cast<std::uint8_t>(summary_md_entry_.size());

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(class_key_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(security_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_type_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_volume_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(open_interest_));
    offset += 4;

    offset += net_chg_prev_day_.encode(data + offset, capacity - offset);

    offset += underlying_px_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(no_entries));
    offset += 1;

    for (const auto& entry : summary_md_entry_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SummaryMessage::encoded_size() const {
    return 4 + 4 + 1 + 4 + 4 + net_chg_prev_day_.encoded_size() + underlying_px_.encoded_size() + 1 + wire::encoded_size_of(summary_md_entry_);
}

void SummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SummaryMessage::clone() const {
    return std::make_unique<SummaryMessage>(*this);
}

void SummaryMessage::print(std::ostream& out) const {
    out << "SummaryMessage{";
    out << "class_key=";
    out << class_key_;
    out << ", security_id=";
    out << security_id_;
    out << ", price_type=";
    out << static_cast<int>(price_type_);
    out << ", trade_volume=";
    out << trade_volume_;
    out << ", open_interest=";
    out << open_interest_;
    out << ", net_chg_prev_day=";
    net_chg_prev_day_.print(out);
    out << ", underlying_px=";
    underlying_px_.print(out);
    out << ", no_entries=";
    out << static_cast<int>(no_entries_);
    out << ", summary_md_entry=";
    print::sequence(out, summary_md_entry_);
    out << '}';
}

bool SummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SummaryMessage::operator==(const SummaryMessage& other) const {
    return class_key_ == other.class_key_
        && security_id_ == other.security_id_
        && price_type_ == other.price_type_
        && trade_volume_ == other.trade_volume_
        && open_interest_ == other.open_interest_
        && net_chg_prev_day_ == other.net_chg_prev_day_
        && underlying_px_ == other.underlying_px_
        && no_entries_ == other.no_entries_
        && summary_md_entry_ == other.summary_md_entry_;
}

bool SummaryMessage::operator!=(const SummaryMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
