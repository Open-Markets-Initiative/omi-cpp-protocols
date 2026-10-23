#include "ChannelReset.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

ChannelReset::ChannelReset(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, const ChannelResetGroups& channel_reset_groups)
  : transact_time_(transact_time), match_event_indicator_(match_event_indicator), channel_reset_groups_(channel_reset_groups) {}

std::chrono::nanoseconds ChannelReset::transact_time() const { return transact_time_; }
void ChannelReset::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const MatchEventIndicator& ChannelReset::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ChannelReset::match_event_indicator() { return match_event_indicator_; }
void ChannelReset::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const ChannelResetGroups& ChannelReset::channel_reset_groups() const { return channel_reset_groups_; }
ChannelResetGroups& ChannelReset::channel_reset_groups() { return channel_reset_groups_; }
void ChannelReset::set_channel_reset_groups(const ChannelResetGroups& value) { channel_reset_groups_ = value; }

MktdataPayloadCode ChannelReset::type() const { return message_type; }

std::string_view ChannelReset::name() const { return "Channel Reset"; }

std::size_t ChannelReset::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ChannelReset", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    offset += channel_reset_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ChannelReset::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ChannelReset", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    offset += channel_reset_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ChannelReset::encoded_size() const {
    return 8 + match_event_indicator_.encoded_size() + channel_reset_groups_.encoded_size();
}

void ChannelReset::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> ChannelReset::clone() const {
    return std::make_unique<ChannelReset>(*this);
}

void ChannelReset::print(std::ostream& out) const {
    out << "ChannelReset{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", channel_reset_groups=";
    channel_reset_groups_.print(out);
    out << '}';
}

bool ChannelReset::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const ChannelReset*>(&other);
    return that != nullptr && *this == *that;
}

bool ChannelReset::operator==(const ChannelReset& other) const {
    return transact_time_ == other.transact_time_
        && match_event_indicator_ == other.match_event_indicator_
        && channel_reset_groups_ == other.channel_reset_groups_;
}

bool ChannelReset::operator!=(const ChannelReset& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
