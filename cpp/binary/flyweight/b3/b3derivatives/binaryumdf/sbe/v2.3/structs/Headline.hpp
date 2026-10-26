#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// headline data struct
class Headline {
  public:
    static constexpr const char* name = "Headline";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Headline(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Headline has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 2;
    std::size_t encoded_size() const { return headline_data_end(); }

    std::uint16_t headline_length() const { return wire::read_u16_le(at(0)); }

    std::size_t headline_data_size() const { return wire::count(headline_length()); }
    std::string_view headline_data() const {
        wire::require("Headline", 2 + headline_data_size(), bytes_.size());
        return view::characters(at(2), headline_data_size());
    }

    void print(std::ostream& out) const {
        out << "Headline{";
        out << "headline_length=";
        out << headline_length();
        out << ", headline_data=";
        print::text(out, headline_data());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t headline_data_end() const { return 2 + headline_data_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Headline& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
