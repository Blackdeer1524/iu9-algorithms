# kmp - knuth-morris-pratt

def get_forward_kmp_table(pattern: str) -> list[int]:
    # a b a b c a b a b a b c
    # 0 0 1 2 0 1 2 3 4 3 4 5
    table = [0 for _ in range(len(pattern))]

    pattern_pivot_index = 0
    i = 1

    while i < len(pattern):
        if pattern[i] == pattern[pattern_pivot_index]:
            pattern_pivot_index += 1
            table[i] = pattern_pivot_index
            i += 1                             
        else:
            if pattern_pivot_index:
                pattern_pivot_index = table[pattern_pivot_index - 1]
            else:
                i += 1

    return table

def prepare_good_suffix_rule(pattern: str) -> list[int]: 
    jump_table: list[int] = [i for i in range(len(pattern))]
    backward_kmp_preprocess: list[int] = [0 for _ in range(len(pattern) + 1)]

    right_index = len(pattern) - 1
    pattern_pivot_index = right_index
    i = len(pattern) - 2

    cum_sum = 0
    while i > 0:
        if pattern[i] == pattern[pattern_pivot_index]:
            cum_sum += 1
            backward_kmp_preprocess[i] += cum_sum

            jump_table_index = right_index - (backward_kmp_preprocess[i] - 1)
            pattern_pivot_index -= 1
            i -= 1  

            if pattern[i] != pattern[jump_table_index - 1]:
                jump_table[jump_table_index] = min(pattern_pivot_index - i, jump_table[jump_table_index])
                if pattern_pivot_index < right_index:
                    pattern_pivot_index = right_index - backward_kmp_preprocess[pattern_pivot_index + 1]
                else:
                    i -= 1
                cum_sum = right_index - pattern_pivot_index                              
        else:
            if pattern_pivot_index < right_index:
                pattern_pivot_index = right_index - backward_kmp_preprocess[pattern_pivot_index + 1]
            else:
                i -= 1
            cum_sum = right_index - pattern_pivot_index
        
    while i == 0:
        if pattern[i] == pattern[pattern_pivot_index]:
            cum_sum += 1
            backward_kmp_preprocess[i] += cum_sum

            jump_table_index = right_index - (backward_kmp_preprocess[i] - 1)
            pattern_pivot_index -= 1
            i -= 1  

            jump_table[jump_table_index] = min(pattern_pivot_index - i, jump_table[jump_table_index])

        if pattern_pivot_index < right_index:
            pattern_pivot_index = right_index - backward_kmp_preprocess[pattern_pivot_index + 1]
        else:
            i -= 1
        cum_sum = right_index - pattern_pivot_index

    return jump_table


LOWEST_CHAR_CODE = 33
HIGHEST_CHAR_CODE = 126


def prepare_bad_character_rule(pattern: str) -> list[list[int]]:
    jump_table: list[list[int]] = [[len(pattern) for _ in range(len(pattern))] 
                                   for _ in range(LOWEST_CHAR_CODE, HIGHEST_CHAR_CODE + 1)]
    last_valid_item_lookup = [0 for _ in range(LOWEST_CHAR_CODE, HIGHEST_CHAR_CODE + 1)]

    for i in range(1, len(pattern)):
        prev_char_index = ord(pattern[i - 1]) - LOWEST_CHAR_CODE

        jump_table[prev_char_index][i] = 1
        if last_valid_item_lookup[prev_char_index]:
            for j in range(last_valid_item_lookup[prev_char_index], i):
                jump_table[prev_char_index][j] = jump_table[prev_char_index][j - 1] + 1

        last_valid_item_lookup[prev_char_index] = i + 1

    for i, row_last_valid_item in enumerate(last_valid_item_lookup):
        if not row_last_valid_item:
            continue

        for j in range(row_last_valid_item, len(pattern)):
            jump_table[i][j] = jump_table[i][j - 1] + 1

    return jump_table


def boyer_moore_str_search(src: str, pattern: str) -> None:
    good_suffix_jump_table = prepare_good_suffix_rule(pattern)
    bad_char_jump_table = prepare_bad_character_rule(pattern)
    forward_kmp_table = get_forward_kmp_table(pattern)

    offset = 0
    left_bound = 0
    while offset + len(pattern) <= len(src):
        i = len(pattern) - 1
        while i >= left_bound:
            if src[offset + i] != pattern[i]:
                break
            i -= 1
        else:  # cycle ended without `break`
            print(offset)
            offset += forward_kmp_table[len(pattern) - 1] if forward_kmp_table[len(pattern) - 1] else len(pattern)
            left_bound = 0
            continue
        
        good_suffix_shift = good_suffix_jump_table[i + 1] if i + 1 < len(good_suffix_jump_table) else len(pattern)
        bad_char_shift = bad_char_jump_table[ord(src[offset + i]) - LOWEST_CHAR_CODE][i]
        offset += min(good_suffix_shift, bad_char_shift)
        left_bound = forward_kmp_table[i]

def test_good_suffix_jump_table():
    pattern = "ababc"
    # print(prepare_good_suffix_rule(pattern))
    print(prepare_bad_character_rule(pattern))
    # print(get_forward_kmp_table("ababcabababc"))

if __name__ == "__main__":
    # test_good_suffix_jump_table()
    # boyer_moore_str_search("ababcabababc", "ababc")
    boyer_moore_str_search("aaaaaa", "aa")