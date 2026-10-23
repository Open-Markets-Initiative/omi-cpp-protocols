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
#include "../enums/Side.hpp"
#include "../enums/CrossRequestType.hpp"
#include "../enums/InputSource.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class CrossRequest {
  public:
    static constexpr const char* name = "CrossRequest";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CrossRequest(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CrossRequest has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<Decimal> last_px() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<Decimal> last_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<Side> side() const { return wire::nullable_enum<Side>(wire::read_u8(at(24)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<CrossRequestType> cross_request_type() const { return wire::nullable_enum<CrossRequestType>(wire::read_u8(at(25)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<InputSource> input_source() const { return wire::nullable_enum<InputSource>(wire::read_u8(at(26)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 5> pad5() const { return bytes_.subspan(27).template first<5>(); }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(32)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    void print(std::ostream& out) const {
        out << "CrossRequest{";
        out << "security_id=";
        print::optional(out, security_id());
        out << ", last_px=";
        print::optional(out, last_px());
        out << ", last_qty=";
        print::optional(out, last_qty());
        out << ", side=";
        print::optional(out, side());
        out << ", cross_request_type=";
        print::optional(out, cross_request_type());
        out << ", input_source=";
        print::optional(out, input_source());
        out << ", pad5=";
        print::hex(out, pad5().data(), pad5().size());
        out << ", transact_time=";
        print::optional_duration(out, transact_time());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CrossRequest& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v15_0
