#include "RecapUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

RecapUpdateMessage::RecapUpdateMessage(std::uint32_t class_key, std::uint32_t security_id, std::uint8_t price_type, const PrevClosePx& prev_close_px, std::uint32_t trade_volume, std::uint8_t no_entries, const std::vector<RecapUpdateMdEntry>& recap_update_md_entry)
  : class_key_(class_key), security_id_(security_id), price_type_(price_type), prev_close_px_(prev_close_px), trade_volume_(trade_volume), no_entries_(no_entries), recap_update_md_entry_(recap_update_md_entry) {}

std::uint32_t RecapUpdateMessage::class_key() const { return class_key_; }
void RecapUpdateMessage::set_class_key(std::uint32_t value) { class_key_ = value; }

std::uint32_t RecapUpdateMessage::security_id() const { return security_id_; }
void RecapUpdateMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

std::uint8_t RecapUpdateMessage::price_type() const { return price_type_; }
void RecapUpdateMessage::set_price_type(std::uint8_t value) { price_type_ = value; }

const PrevClosePx& RecapUpdateMessage::prev_close_px() const { return prev_close_px_; }
PrevClosePx& RecapUpdateMessage::prev_close_px() { return prev_close_px_; }
void RecapUpdateMessage::set_prev_close_px(const PrevClosePx& value) { prev_close_px_ = value; }

std::uint32_t RecapUpdateMessage::trade_volume() const { return trade_volume_; }
void RecapUpdateMessage::set_trade_volume(std::uint32_t value) { trade_volume_ = value; }

std::uint8_t RecapUpdateMessage::no_entries() const { return no_entries_; }
void RecapUpdateMessage::set_no_entries(std::uint8_t value) { no_entries_ = value; }

const std::vector<RecapUpdateMdEntry>& RecapUpdateMessage::recap_update_md_entry() const { return recap_update_md_entry_; }
std::vector<RecapUpdateMdEntry>& RecapUpdateMessage::recap_update_md_entry() { return recap_update_md_entry_; }
void RecapUpdateMessage::set_recap_update_md_entry(const std::vector<RecapUpdateMdEntry>& value) { recap_update_md_entry_ = value; }

MessageCode RecapUpdateMessage::type() const { return message_type; }

std::string_view RecapUpdateMessage::name() const { return "Recap Update Message"; }

std::size_t RecapUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("RecapUpdateMessage", offset + 4, length);
    class_key_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("RecapUpdateMessage", offset + 4, length);
    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("RecapUpdateMessage", offset + 1, length);
    price_type_ = wire::read_u8(data + offset);
    offset += 1;

    offset += prev_close_px_.decode(data + offset, length - offset);

    wire::require("RecapUpdateMessage", offset + 4, length);
    trade_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("RecapUpdateMessage", offset + 1, length);
    no_entries_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(no_entries_);
        recap_update_md_entry_.clear();
        recap_update_md_entry_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            RecapUpdateMdEntry entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            recap_update_md_entry_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t RecapUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RecapUpdateMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto no_entries = no_entries_;
    no_entries = static_cast<std::uint8_t>(recap_update_md_entry_.size());

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(class_key_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(security_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_type_));
    offset += 1;

    offset += prev_close_px_.encode(data + offset, capacity - offset);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(no_entries));
    offset += 1;

    for (const auto& entry : recap_update_md_entry_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t RecapUpdateMessage::encoded_size() const {
    return 4 + 4 + 1 + prev_close_px_.encoded_size() + 4 + 1 + wire::encoded_size_of(recap_update_md_entry_);
}

void RecapUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RecapUpdateMessage::clone() const {
    return std::make_unique<RecapUpdateMessage>(*this);
}

void RecapUpdateMessage::print(std::ostream& out) const {
    out << "RecapUpdateMessage{";
    out << "class_key=";
    out << class_key_;
    out << ", security_id=";
    out << security_id_;
    out << ", price_type=";
    out << static_cast<int>(price_type_);
    out << ", prev_close_px=";
    prev_close_px_.print(out);
    out << ", trade_volume=";
    out << trade_volume_;
    out << ", no_entries=";
    out << static_cast<int>(no_entries_);
    out << ", recap_update_md_entry=";
    print::sequence(out, recap_update_md_entry_);
    out << '}';
}

bool RecapUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RecapUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RecapUpdateMessage::operator==(const RecapUpdateMessage& other) const {
    return class_key_ == other.class_key_
        && security_id_ == other.security_id_
        && price_type_ == other.price_type_
        && prev_close_px_ == other.prev_close_px_
        && trade_volume_ == other.trade_volume_
        && no_entries_ == other.no_entries_
        && recap_update_md_entry_ == other.recap_update_md_entry_;
}

bool RecapUpdateMessage::operator!=(const RecapUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
