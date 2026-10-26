#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/AuctionType.hpp"
#include "../bitfields/PtModFlags.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Sent to report details of an auction
class AuctionTradeMessage {
  public:
    static constexpr const char* name = "AuctionTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint32_t quantity() const { return wire::read_u32_le(at(4)); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(8)); }

    std::span<const std::byte, 1> reserved_a() const { return bytes_.subspan(12).template first<1>(); }

    std::span<const std::byte, 1> reserved_b() const { return bytes_.subspan(13).template first<1>(); }

    std::int64_t price() const { return wire::read_i64_le(at(14)); }

    std::uint64_t trade_match_id() const { return wire::read_u64_le(at(22)); }

    AuctionType auction_type() const { return static_cast<AuctionType>(wire::read_char(at(30))); }

    PtModFlags pt_mod_flags() const { return PtModFlags{ bytes_.subspan(31) }; }

    void print(std::ostream& out) const {
        out << "AuctionTradeMessage{";
        out << "nanosecond=";
        out << nanosecond();
        out << ", quantity=";
        out << quantity();
        out << ", instrument_id=";
        out << instrument_id();
        out << ", reserved_a=";
        print::hex(out, reserved_a().data(), reserved_a().size());
        out << ", reserved_b=";
        print::hex(out, reserved_b().data(), reserved_b().size());
        out << ", price=";
        out << price();
        out << ", trade_match_id=";
        out << trade_match_id();
        out << ", auction_type=";
        out << auction_type();
        out << ", pt_mod_flags=";
        pt_mod_flags().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
