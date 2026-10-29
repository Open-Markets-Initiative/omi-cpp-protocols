#pragma once

#include <cstddef>
#include <ostream>

#include "../enums/Category2.hpp"
#include "../enums/Category3.hpp"
#include "../enums/Category4.hpp"

namespace siac::cts::output::cta::v1_91 {

// Sale Conditions
class SaleConditions {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 4;

    SaleConditions() = default;
    SaleConditions(char category_1, Category2 category_2, Category3 category_3, Category4 category_4);

    // Category 1: Denotes the Settlement Type sale condition
    char category_1() const;
    void set_category_1(char value);

    // Category 2: Denotes the Reason Type sale condition
    Category2 category_2() const;
    void set_category_2(Category2 value);

    // Category 3: Denotes the Sequence Type sale condition
    Category3 category_3() const;
    void set_category_3(Category3 value);

    // Category 4: Denotes the Trade Detail sale condition
    Category4 category_4() const;
    void set_category_4(Category4 value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SaleConditions& other) const;
    bool operator!=(const SaleConditions& other) const;

  private:
    char category_1_{};
    Category2 category_2_{};
    Category3 category_3_{};
    Category4 category_4_{};
};

std::ostream& operator<<(std::ostream& out, const SaleConditions& value);

} // namespace siac::cts::output::cta::v1_91
