#pragma once

namespace packet {

    enum class result {
        iex_iexequities_deep_snap_v1_6,
        error,
        end_of_file,
        unknown
    };

}