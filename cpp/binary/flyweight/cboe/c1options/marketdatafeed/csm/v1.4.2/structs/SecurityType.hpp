#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class SecurityType {
  public:
    static constexpr const char* name = "SecurityType";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityType(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityType has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return security_type_text_end(); }

    std::uint8_t security_type_length() const { return wire::read_u8(at(0)); }

    std::size_t security_type_text_size() const { return wire::count(security_type_length()); }
    std::string_view security_type_text() const {
        wire::require("SecurityType", 1 + security_type_text_size(), bytes_.size());
        return view::characters(at(1), security_type_text_size());
    }

    void print(std::ostream& out) const {
        out << "SecurityType{";
        out << "security_type_length=";
        out << static_cast<int>(security_type_length());
        out << ", security_type_text=";
        print::text(out, security_type_text());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t security_type_text_end() const { return 1 + security_type_text_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityType& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
