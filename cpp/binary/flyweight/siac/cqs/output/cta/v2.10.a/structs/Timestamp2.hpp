#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// Timestamp 2
class Timestamp2 {
  public:
    static constexpr const char* name = "Timestamp2";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Timestamp2(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Timestamp2 has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::chrono::seconds seconds() const { return std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(4)))); }

    void print(std::ostream& out) const {
        out << "Timestamp2{";
        out << "seconds=";
        out << seconds().count();
        out << ", nanoseconds=";
        out << nanoseconds().count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Timestamp2& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v2_10_a
