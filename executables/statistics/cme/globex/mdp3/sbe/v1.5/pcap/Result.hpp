#pragma once

namespace packet {

    enum class result {
        cme_globex_mdp3_sbe_v1_5,
        error,
        end_of_file,
        unknown
    };

}