#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TradeAction.hpp"
#include "../bitfields/TradeStatus.hpp"
#include "../common/Decimal.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// A Trade Message is created for every trade that occurs on OTC Markets OTC Link ATS.
class TradeMessage {
  public:
    static constexpr const char* name = "TradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 43;
    static constexpr std::size_t fixed_size = 43;
    std::size_t encoded_size() const { return 43; }

    std::uint32_t channel_seq_num() const { return wire::read_u32_be(at(0)); }

    std::uint32_t trade_id() const { return wire::read_u32_be(at(4)); }

    TradeAction trade_action() const { return static_cast<TradeAction>(wire::read_u8(at(8))); }

    std::uint8_t trade_flags() const { return wire::read_u8(at(9)); }

    std::uint32_t security_id() const { return wire::read_u32_be(at(10)); }

    TradeStatus trade_status() const { return TradeStatus{ bytes_.subspan(14) }; }

    std::string_view deprecated() const { return view::text(at(15), 8, ' '); }

    Decimal trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(23))), -6); }

    std::uint32_t trade_size() const { return wire::read_u32_be(at(31)); }

    std::uint64_t trade_time_milli() const { return wire::read_u64_be(at(35)); }

    void print(std::ostream& out) const {
        out << "TradeMessage{";
        out << "channel_seq_num=";
        out << channel_seq_num();
        out << ", trade_id=";
        out << trade_id();
        out << ", trade_action=";
        out << trade_action();
        out << ", trade_flags=";
        out << static_cast<int>(trade_flags());
        out << ", security_id=";
        out << security_id();
        out << ", trade_status=";
        trade_status().print(out);
        out << ", deprecated=";
        print::text(out, deprecated());
        out << ", trade_price=";
        out << trade_price();
        out << ", trade_size=";
        out << trade_size();
        out << ", trade_time_milli=";
        out << trade_time_milli();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
