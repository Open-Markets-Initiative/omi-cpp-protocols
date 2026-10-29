#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// deskID data struct
class DeskId {
  public:
    static constexpr const char* name = "DeskId";

    // the bytes it reads, which it does not own: they must outlive it
    explicit DeskId(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every DeskId has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return desk_id_data_end(); }

    std::uint8_t desk_id_length() const { return wire::read_u8(at(0)); }

    std::size_t desk_id_data_size() const { return wire::count(desk_id_length()); }
    std::string_view desk_id_data() const {
        wire::require("DeskId", 1 + desk_id_data_size(), bytes_.size());
        return view::characters(at(1), desk_id_data_size());
    }

    void print(std::ostream& out) const {
        out << "DeskId{";
        out << "desk_id_length=";
        out << static_cast<int>(desk_id_length());
        out << ", desk_id_data=";
        print::text(out, desk_id_data());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t desk_id_data_end() const { return 1 + desk_id_data_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const DeskId& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
