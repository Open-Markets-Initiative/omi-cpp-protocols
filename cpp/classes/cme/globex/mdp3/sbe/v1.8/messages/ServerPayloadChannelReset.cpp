#include "ServerPayloadChannelReset.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

ServerPayloadChannelReset::ServerPayloadChannelReset(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, const ChannelResetGroups& channel_reset_groups)
  : transact_time_(transact_time), match_event_indicator_(match_event_indicator), channel_reset_groups_(channel_reset_groups) {}

std::chrono::nanoseconds ServerPayloadChannelReset::transact_time() const { return transact_time_; }
void ServerPayloadChannelReset::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const MatchEventIndicator& ServerPayloadChannelReset::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ServerPayloadChannelReset::match_event_indicator() { return match_event_indicator_; }
void ServerPayloadChannelReset::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const ChannelResetGroups& ServerPayloadChannelReset::channel_reset_groups() const { return channel_reset_groups_; }
ChannelResetGroups& ServerPayloadChannelReset::channel_reset_groups() { return channel_reset_groups_; }
void ServerPayloadChannelReset::set_channel_reset_groups(const ChannelResetGroups& value) { channel_reset_groups_ = value; }

ServerTcpMessageCode ServerPayloadChannelReset::type() const { return message_type; }

std::string_view ServerPayloadChannelReset::name() const { return "Channel Reset"; }

std::size_t ServerPayloadChannelReset::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ServerPayloadChannelReset", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    offset += channel_reset_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ServerPayloadChannelReset::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadChannelReset", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    offset += channel_reset_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ServerPayloadChannelReset::encoded_size() const {
    return 8 + match_event_indicator_.encoded_size() + channel_reset_groups_.encoded_size();
}

void ServerPayloadChannelReset::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadChannelReset::clone() const {
    return std::make_unique<ServerPayloadChannelReset>(*this);
}

void ServerPayloadChannelReset::print(std::ostream& out) const {
    out << "ServerPayloadChannelReset{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", channel_reset_groups=";
    channel_reset_groups_.print(out);
    out << '}';
}

bool ServerPayloadChannelReset::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadChannelReset*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadChannelReset::operator==(const ServerPayloadChannelReset& other) const {
    return transact_time_ == other.transact_time_
        && match_event_indicator_ == other.match_event_indicator_
        && channel_reset_groups_ == other.channel_reset_groups_;
}

bool ServerPayloadChannelReset::operator!=(const ServerPayloadChannelReset& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_8
