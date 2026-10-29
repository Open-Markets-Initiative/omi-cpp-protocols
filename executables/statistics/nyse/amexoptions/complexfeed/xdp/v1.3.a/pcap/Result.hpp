#pragma once

namespace packet {

    enum class result {
        nyse_amexoptions_complexfeed_xdp_v1_3_a,
        error,
        end_of_file,
        unknown
    };

}