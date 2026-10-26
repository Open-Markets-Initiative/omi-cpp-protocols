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
#include "../structs/IncrementalRefreshOrderBookGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// MDIncrementalRefreshOrderBook
class ServerPayloadMdIncrementalRefreshOrderBook {
  public:
    static constexpr const char* name = "ServerPayloadMdIncrementalRefreshOrderBook";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ServerPayloadMdIncrementalRefreshOrderBook(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ServerPayloadMdIncrementalRefreshOrderBook has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 11;
    std::size_t encoded_size() const { return incremental_refresh_order_book_groups_end(); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    std::span<const std::byte, 2> padding_2() const { return bytes_.subspan(9).template first<2>(); }

    IncrementalRefreshOrderBookGroups incremental_refresh_order_book_groups() const { return IncrementalRefreshOrderBookGroups{ bytes_.subspan(11) }; }

    void print(std::ostream& out) const {
        out << "ServerPayloadMdIncrementalRefreshOrderBook{";
        out << "transact_time=";
        out << transact_time().count();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", padding_2=";
        print::hex(out, padding_2().data(), padding_2().size());
        out << ", incremental_refresh_order_book_groups=";
        incremental_refresh_order_book_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t incremental_refresh_order_book_groups_end() const { return 11 + incremental_refresh_order_book_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ServerPayloadMdIncrementalRefreshOrderBook& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
