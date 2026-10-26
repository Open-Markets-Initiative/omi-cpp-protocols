#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

class RelatedInstrumentGrpComp {
  public:
    static constexpr const char* name = "RelatedInstrumentGrpComp";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RelatedInstrumentGrpComp(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RelatedInstrumentGrpComp has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::optional<std::int64_t> related_security_id() const { return wire::nullable(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    void print(std::ostream& out) const {
        out << "RelatedInstrumentGrpComp{";
        out << "related_security_id=";
        print::optional(out, related_security_id());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RelatedInstrumentGrpComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v13_0
