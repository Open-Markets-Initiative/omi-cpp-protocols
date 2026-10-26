#pragma once

#include <cstddef>
#include <ostream>

#include "../enums/Category1.hpp"
#include "../enums/Category2.hpp"
#include "../enums/Category3.hpp"
#include "../enums/Category4.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Sale Condition 4
class SaleCondition4 {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 4;

    SaleCondition4() = default;
    SaleCondition4(Category1 category_1, Category2 category_2, Category3 category_3, Category4 category_4);

    // Category 1: Settlement Type
    Category1 category_1() const;
    void set_category_1(Category1 value);

    // Category 2: Reason for Trade-Through Exemption / Other Reason
    Category2 category_2() const;
    void set_category_2(Category2 value);

    // Category 3: Extended Hours / Sequence Type
    Category3 category_3() const;
    void set_category_3(Category3 value);

    // Category 4: SRO Trade Detail
    Category4 category_4() const;
    void set_category_4(Category4 value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SaleCondition4& other) const;
    bool operator!=(const SaleCondition4& other) const;

  private:
    Category1 category_1_{};
    Category2 category_2_{};
    Category3 category_3_{};
    Category4 category_4_{};
};

std::ostream& operator<<(std::ostream& out, const SaleCondition4& value);

} // namespace siac::cts::output::cta::v2_11_b
