#pragma once

namespace packet {

    enum class result {
        eurex_t7_eobi_fbe_v3_0,
        error,
        end_of_file,
        unknown
    };

}