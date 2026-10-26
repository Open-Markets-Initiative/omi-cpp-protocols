#include "ServerPayloadMdIncrementalRefreshVolume.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

ServerPayloadMdIncrementalRefreshVolume::ServerPayloadMdIncrementalRefreshVolume(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 2>& padding_2, const IncrementalRefreshVolumeGroups& incremental_refresh_volume_groups)
  : transact_time_(transact_time), match_event_indicator_(match_event_indicator), padding_2_(padding_2), incremental_refresh_volume_groups_(incremental_refresh_volume_groups) {}

std::chrono::nanoseconds ServerPayloadMdIncrementalRefreshVolume::transact_time() const { return transact_time_; }
void ServerPayloadMdIncrementalRefreshVolume::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const MatchEventIndicator& ServerPayloadMdIncrementalRefreshVolume::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ServerPayloadMdIncrementalRefreshVolume::match_event_indicator() { return match_event_indicator_; }
void ServerPayloadMdIncrementalRefreshVolume::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 2>& ServerPayloadMdIncrementalRefreshVolume::padding_2() const { return padding_2_; }
std::array<std::byte, 2>& ServerPayloadMdIncrementalRefreshVolume::padding_2() { return padding_2_; }
void ServerPayloadMdIncrementalRefreshVolume::set_padding_2(const std::array<std::byte, 2>& value) { padding_2_ = value; }

const IncrementalRefreshVolumeGroups& ServerPayloadMdIncrementalRefreshVolume::incremental_refresh_volume_groups() const { return incremental_refresh_volume_groups_; }
IncrementalRefreshVolumeGroups& ServerPayloadMdIncrementalRefreshVolume::incremental_refresh_volume_groups() { return incremental_refresh_volume_groups_; }
void ServerPayloadMdIncrementalRefreshVolume::set_incremental_refresh_volume_groups(const IncrementalRefreshVolumeGroups& value) { incremental_refresh_volume_groups_ = value; }

ServerTcpMessageCode ServerPayloadMdIncrementalRefreshVolume::type() const { return message_type; }

std::string_view ServerPayloadMdIncrementalRefreshVolume::name() const { return "Md Incremental Refresh Volume"; }

std::size_t ServerPayloadMdIncrementalRefreshVolume::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ServerPayloadMdIncrementalRefreshVolume", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("ServerPayloadMdIncrementalRefreshVolume", offset + 2, length);
    wire::read_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += incremental_refresh_volume_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ServerPayloadMdIncrementalRefreshVolume::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadMdIncrementalRefreshVolume", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += incremental_refresh_volume_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ServerPayloadMdIncrementalRefreshVolume::encoded_size() const {
    return 8 + match_event_indicator_.encoded_size() + 2 + incremental_refresh_volume_groups_.encoded_size();
}

void ServerPayloadMdIncrementalRefreshVolume::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadMdIncrementalRefreshVolume::clone() const {
    return std::make_unique<ServerPayloadMdIncrementalRefreshVolume>(*this);
}

void ServerPayloadMdIncrementalRefreshVolume::print(std::ostream& out) const {
    out << "ServerPayloadMdIncrementalRefreshVolume{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", padding_2=";
    print::hex(out, padding_2_.data(), padding_2_.size());
    out << ", incremental_refresh_volume_groups=";
    incremental_refresh_volume_groups_.print(out);
    out << '}';
}

bool ServerPayloadMdIncrementalRefreshVolume::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadMdIncrementalRefreshVolume*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadMdIncrementalRefreshVolume::operator==(const ServerPayloadMdIncrementalRefreshVolume& other) const {
    return transact_time_ == other.transact_time_
        && match_event_indicator_ == other.match_event_indicator_
        && padding_2_ == other.padding_2_
        && incremental_refresh_volume_groups_ == other.incremental_refresh_volume_groups_;
}

bool ServerPayloadMdIncrementalRefreshVolume::operator!=(const ServerPayloadMdIncrementalRefreshVolume& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
