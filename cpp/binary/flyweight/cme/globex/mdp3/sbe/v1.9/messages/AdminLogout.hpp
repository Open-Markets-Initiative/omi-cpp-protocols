#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// AdminLogout
class AdminLogout {
  public:
    static constexpr const char* name = "AdminLogout";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AdminLogout(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AdminLogout has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 100;
    static constexpr std::size_t fixed_size = 100;
    std::size_t encoded_size() const { return 100; }

    std::string_view text() const { return view::text(at(0), 100, '\0'); }

    void print(std::ostream& out) const {
        out << "AdminLogout{";
        out << "text=";
        print::text(out, text());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AdminLogout& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
