#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// SecurityDetail
class SecurityDetail {
  public:
    static constexpr const char* name = "SecurityDetail";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityDetail(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityDetail has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return security_detail_name_end(); }

    std::uint8_t security_detail_size() const { return wire::read_u8(at(0)); }

    std::size_t security_detail_name_size() const { return wire::count(security_detail_size()); }
    std::string_view security_detail_name() const {
        wire::require("SecurityDetail", 1 + security_detail_name_size(), bytes_.size());
        return view::characters(at(1), security_detail_name_size());
    }

    void print(std::ostream& out) const {
        out << "SecurityDetail{";
        out << "security_detail_size=";
        out << static_cast<int>(security_detail_size());
        out << ", security_detail_name=";
        print::text(out, security_detail_name());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t security_detail_name_end() const { return 1 + security_detail_name_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityDetail& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
