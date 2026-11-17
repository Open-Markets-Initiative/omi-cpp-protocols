// Databento.MarketData.Normalized.Dbn.v2: messages/MboMsg.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../bitfields/Flags.hpp"
#include "../enums/Action.hpp"
#include "../enums/Side.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// A market-by-order (MBO) tick message
class MboMsg {
  public:
    static constexpr const char* name = "MboMsg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MboMsg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MboMsg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::uint64_t order_id() const { return wire::read_u64_le(at(0)); }

    std::optional<Decimal> price() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::uint32_t size() const { return wire::read_u32_le(at(16)); }

    Flags flags() const { return Flags{ bytes_.subspan(20) }; }

    std::uint8_t channel_id() const { return wire::read_u8(at(21)); }

    Action action() const { return static_cast<Action>(wire::read_char(at(22))); }

    Side side() const { return static_cast<Side>(wire::read_char(at(23))); }

    std::optional<std::chrono::nanoseconds> ts_recv() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(24)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::int32_t ts_in_delta() const { return wire::read_i32_le(at(32)); }

    std::uint32_t sequence() const { return wire::read_u32_le(at(36)); }

    void print(std::ostream& out) const {
        out << "MboMsg{";
        out << "order_id=";
        out << order_id();
        out << ", price=";
        print::optional(out, price());
        out << ", size=";
        out << size();
        out << ", flags=";
        flags().print(out);
        out << ", channel_id=";
        out << static_cast<int>(channel_id());
        out << ", action=";
        out << action();
        out << ", side=";
        out << side();
        out << ", ts_recv=";
        print::optional_duration(out, ts_recv());
        out << ", ts_in_delta=";
        out << ts_in_delta();
        out << ", sequence=";
        out << sequence();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MboMsg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v2
