#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/FullRefreshHeader.hpp"

namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g {

// The first message in each packet of refresh messages published over the Refresh multicast
// channels is of this type.
class RefreshHeaderMessage {
  public:
    static constexpr const char* name = "RefreshHeaderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RefreshHeaderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RefreshHeaderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    std::size_t encoded_size() const { return full_refresh_header_end(); }

    std::uint16_t current_refresh_pkt() const { return wire::read_u16_le(at(0)); }

    std::uint16_t total_refresh_pkts() const { return wire::read_u16_le(at(2)); }

    std::optional<FullRefreshHeader> full_refresh_header() const {
        if (!(current_refresh_pkt() == 1)) { return std::nullopt; }
        wire::require("RefreshHeaderMessage", 4 + FullRefreshHeader::minimum_size, bytes_.size());
        return FullRefreshHeader{ bytes_.subspan(4) };
    }

    void print(std::ostream& out) const {
        out << "RefreshHeaderMessage{";
        out << "current_refresh_pkt=";
        out << current_refresh_pkt();
        out << ", total_refresh_pkts=";
        out << total_refresh_pkts();
        out << ", full_refresh_header=";
        print::optional(out, full_refresh_header());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t full_refresh_header_end() const { return 4 + (full_refresh_header() ? full_refresh_header()->encoded_size() : 0); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RefreshHeaderMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g
