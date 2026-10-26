#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// securityDesc data struct
class SecurityDesc {
  public:
    static constexpr const char* name = "SecurityDesc";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityDesc(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityDesc has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return security_desc_data_end(); }

    std::uint8_t security_desc_length() const { return wire::read_u8(at(0)); }

    std::size_t security_desc_data_size() const { return wire::count(security_desc_length()); }
    std::string_view security_desc_data() const {
        wire::require("SecurityDesc", 1 + security_desc_data_size(), bytes_.size());
        return view::characters(at(1), security_desc_data_size());
    }

    void print(std::ostream& out) const {
        out << "SecurityDesc{";
        out << "security_desc_length=";
        out << static_cast<int>(security_desc_length());
        out << ", security_desc_data=";
        print::text(out, security_desc_data());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t security_desc_data_end() const { return 1 + security_desc_data_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityDesc& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
