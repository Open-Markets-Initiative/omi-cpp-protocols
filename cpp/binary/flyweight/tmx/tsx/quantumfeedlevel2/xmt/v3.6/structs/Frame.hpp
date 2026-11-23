// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/Frame.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/BodyHeader.hpp"
#include "../structs/BusinessHeader.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// Xmt Body
class Frame {
  public:
    static constexpr const char* name = "Frame";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Frame(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Frame has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    BodyHeader body_header() const { return BodyHeader{ bytes_.subspan(0) }; }

    BusinessHeader business_header() const { return BusinessHeader{ bytes_.subspan(3) }; }

    void print(std::ostream& out) const {
        out << "Frame{";
        out << "body_header=";
        body_header().print(out);
        out << ", business_header=";
        business_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Frame& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
