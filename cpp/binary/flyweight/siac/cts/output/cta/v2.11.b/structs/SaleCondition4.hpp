#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Category1.hpp"
#include "../enums/Category2.hpp"
#include "../enums/Category3.hpp"
#include "../enums/Category4.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Sale Condition 4
class SaleCondition4 {
  public:
    static constexpr const char* name = "SaleCondition4";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SaleCondition4(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SaleCondition4 has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    Category1 category_1() const { return static_cast<Category1>(wire::read_char(at(0))); }

    Category2 category_2() const { return static_cast<Category2>(wire::read_char(at(1))); }

    Category3 category_3() const { return static_cast<Category3>(wire::read_char(at(2))); }

    Category4 category_4() const { return static_cast<Category4>(wire::read_char(at(3))); }

    void print(std::ostream& out) const {
        out << "SaleCondition4{";
        out << "category_1=";
        out << category_1();
        out << ", category_2=";
        out << category_2();
        out << ", category_3=";
        out << category_3();
        out << ", category_4=";
        out << category_4();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SaleCondition4& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
