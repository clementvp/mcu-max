// Test du moteur d'échecs MCU-Max
// Joue quelques coups et affiche le plateau

#include <stdio.h>
#include "mcu-max.h"

void print_board() {
    const char *symbols = ".PPNKBRQ.ppnkbrq";
    printf("\n  +-----------------+\n");
    for (int y = 0; y < 8; y++) {
        printf("%d | ", 8 - y);
        for (int x = 0; x < 8; x++) {
            printf("%c ", symbols[mcumax_get_piece(0x10 * y + x)]);
        }
        printf("|\n");
    }
    printf("  +-----------------+\n");
    printf("    a b c d e f g h\n\n");
}

void print_board_raw() {
    printf("\nRaw board values:\n");
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            mcumax_square sq = y * 16 + x;
            printf("%02x ", mcumax.board[sq]);
        }
        printf("\n");
    }
    printf("\n");
}


int main() {
    // Liste de FEN où les blancs sont en échec
    const char *fens[] = {
        // Tour blanche en e7, roi noir en e8
        "4k3/4R3/8/8/8/8/8/4K3 b - - 0 1",
        // Dame blanche en e7, roi noir en e8
        "4k3/4Q3/8/8/8/8/8/4K3 b - - 0 1",
        // Fou blanc en d5, roi noir en g8
        "6k1/8/8/3B4/8/8/8/4K3 b - - 0 1",
        // Cavalier blanc en f6, roi noir en e8
        "4k3/8/5N2/8/8/8/8/4K3 b - - 0 1",
        // Pion blanc en d7, roi noir en c8
        "2k5/3P4/8/8/8/8/8/4K3 b - - 0 1",
        // Roi blanc en d7, roi noir en e8
        "4k3/3K4/8/8/8/8/8/8 b - - 0 1"
    };
    int nb = sizeof(fens)/sizeof(fens[0]);
    for (int i = 0; i < nb; i++) {
        printf("\nTest FEN %d : %s\n", i+1, fens[i]);
        mcumax_set_fen_position(fens[i]);
        print_board();
        print_board_raw();
    printf("Noir en échec ? %s\n", is_in_check(MCUMAX_BOARD_BLACK) ? "oui" : "non");
    }
    return 0;
}
