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
#include "../enums/Side.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

class QuoteRequest {
  public:
    static constexpr const char* name = "QuoteRequest";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteRequest(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteRequest has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<std::int32_t> last_qty() const { return wire::nullable(wire::read_i32_le(at(8)), static_cast<std::int32_t>(0x80000000LL)); }

    std::optional<Side> side() const { return wire::nullable_enum<Side>(wire::read_u8(at(12)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 3> pad3() const { return bytes_.subspan(13).template first<3>(); }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(16)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    void print(std::ostream& out) const {
        out << "QuoteRequest{";
        out << "security_id=";
        print::optional(out, security_id());
        out << ", last_qty=";
        print::optional(out, last_qty());
        out << ", side=";
        print::optional(out, side());
        out << ", pad3=";
        print::hex(out, pad3().data(), pad3().size());
        out << ", transact_time=";
        print::optional_duration(out, transact_time());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteRequest& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v3_0
