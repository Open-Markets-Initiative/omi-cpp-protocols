#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// credentials data struct
class Credentials {
  public:
    static constexpr const char* name = "Credentials";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Credentials(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Credentials has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return credentials_data_end(); }

    std::uint8_t credentials_length() const { return wire::read_u8(at(0)); }

    std::size_t credentials_data_size() const { return wire::count(credentials_length()); }
    std::string_view credentials_data() const {
        wire::require("Credentials", 1 + credentials_data_size(), bytes_.size());
        return view::characters(at(1), credentials_data_size());
    }

    void print(std::ostream& out) const {
        out << "Credentials{";
        out << "credentials_length=";
        out << static_cast<int>(credentials_length());
        out << ", credentials_data=";
        print::text(out, credentials_data());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t credentials_data_end() const { return 1 + credentials_data_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Credentials& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
