#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/AuctionType.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// 9 Used to disseminate the indicative auction price and the tradable quantity and imbalance
// at this price.
class AuctionInfoMessage {
  public:
    static constexpr const char* name = "AuctionInfoMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionInfoMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionInfoMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    static constexpr std::size_t fixed_size = 28;
    std::size_t encoded_size() const { return 28; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint32_t paired_quantity() const { return wire::read_u32_le(at(4)); }

    std::span<const std::byte, 4> reserved_4() const { return bytes_.subspan(8).template first<4>(); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(12).template first<1>(); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(13)); }

    std::span<const std::byte, 1> reserved_a() const { return bytes_.subspan(17).template first<1>(); }

    std::span<const std::byte, 1> reserved_b() const { return bytes_.subspan(18).template first<1>(); }

    std::int64_t price() const { return wire::read_i64_le(at(19)); }

    AuctionType auction_type() const { return static_cast<AuctionType>(wire::read_char(at(27))); }

    void print(std::ostream& out) const {
        out << "AuctionInfoMessage{";
        out << "nanosecond=";
        out << nanosecond();
        out << ", paired_quantity=";
        out << paired_quantity();
        out << ", reserved_4=";
        print::hex(out, reserved_4().data(), reserved_4().size());
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", instrument_id=";
        out << instrument_id();
        out << ", reserved_a=";
        print::hex(out, reserved_a().data(), reserved_a().size());
        out << ", reserved_b=";
        print::hex(out, reserved_b().data(), reserved_b().size());
        out << ", price=";
        out << price();
        out << ", auction_type=";
        out << auction_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionInfoMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
