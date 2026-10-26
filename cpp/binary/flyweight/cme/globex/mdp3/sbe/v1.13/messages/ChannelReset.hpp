#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../structs/ChannelResetGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// ChannelReset
class ChannelReset {
  public:
    static constexpr const char* name = "ChannelReset";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ChannelReset(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ChannelReset has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    std::size_t encoded_size() const { return channel_reset_groups_end(); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    ChannelResetGroups channel_reset_groups() const { return ChannelResetGroups{ bytes_.subspan(9) }; }

    void print(std::ostream& out) const {
        out << "ChannelReset{";
        out << "transact_time=";
        out << transact_time().count();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", channel_reset_groups=";
        channel_reset_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t channel_reset_groups_end() const { return 9 + channel_reset_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ChannelReset& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
