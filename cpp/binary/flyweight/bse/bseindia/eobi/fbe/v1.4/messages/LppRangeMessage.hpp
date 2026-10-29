#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Published whenever there is a change in the limit price protection range of the instrument.
class LppRangeMessage {
  public:
    static constexpr const char* name = "LppRangeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LppRangeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LppRangeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::int64_t security_id() const { return wire::read_i64_le(at(0)); }

    Decimal upper_exec_limit() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(8))), -6); }

    Decimal lower_exec_limit() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(16))), -6); }

    void print(std::ostream& out) const {
        out << "LppRangeMessage{";
        out << "security_id=";
        out << security_id();
        out << ", upper_exec_limit=";
        out << upper_exec_limit();
        out << ", lower_exec_limit=";
        out << lower_exec_limit();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LppRangeMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
