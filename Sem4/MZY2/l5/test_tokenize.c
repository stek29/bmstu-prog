#include <inttypes.h>
#include <stdio.h>

typedef struct {
    uint8_t start;
    uint8_t len;
} __attribute__((packed)) word_tok;

#ifdef __MINGW32__
__stdcall
#endif
    void
    test_tokenize(char *str, uint32_t len, word_tok *words, uint32_t smol_cnt_mask) {
    printf(
        "%s(str='%.*s...', len='%u', words='%p', smol_cnt_mask='%x')\n",
        __func__, len > 5 ? 5 : len, str, len, words, smol_cnt_mask);

    uint16_t s_count = (smol_cnt_mask >> 0) & 0xffff;
    uint16_t min_idx = (smol_cnt_mask >> 16) & 0xffff;

    printf("String: '%.*s'\n", len, str);

    for (uint16_t i = 0; i != s_count; ++i) {
        printf("%d. start=%d len=%d %.*s\n", i, words[i].start, words[i].len, words[i].len, str + words[i].start);
    }

    printf("Shortest word (%d chars): %.*s\n", words[min_idx].len, words[min_idx].len, str + words[min_idx].start);
}