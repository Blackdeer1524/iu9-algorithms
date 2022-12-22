def good_suffix_jump_table(pattern: str) -> list[int]: 
    jump_table: list[int] = [i for i in range(len(pattern))]
    kmp_preprocess: list[int] = [0 for _ in range(len(pattern) + 1)]

    right_index = len(pattern) - 1
    pattern_pivot_index = right_index
    i = len(pattern) - 2

    cum_sum = 0
    while i > 0:
        if pattern[i] == pattern[pattern_pivot_index]:
            cum_sum += 1
            kmp_preprocess[i] += cum_sum

            jump_table_index = right_index - (kmp_preprocess[i] - 1)
            pattern_pivot_index -= 1
            i -= 1  
            # if jump_table_index == right_index:
            #     continue

            if pattern[i] != pattern[jump_table_index - 1]:
                jump_table[jump_table_index] = min(pattern_pivot_index - i, jump_table[jump_table_index])
                if pattern_pivot_index < right_index:
                    pattern_pivot_index = right_index - kmp_preprocess[pattern_pivot_index + 1]
                else:
                    i -= 1
                cum_sum = right_index - pattern_pivot_index                              
        else:
            if pattern_pivot_index < right_index:
                pattern_pivot_index = right_index - kmp_preprocess[pattern_pivot_index + 1]
            else:
                i -= 1
            cum_sum = right_index - pattern_pivot_index
        
    while i == 0:
        if pattern[i] == pattern[pattern_pivot_index]:
            cum_sum += 1
            kmp_preprocess[i] += cum_sum

            jump_table_index = right_index - (kmp_preprocess[i] - 1)
            pattern_pivot_index -= 1
            i -= 1  
            # if jump_table_index == right_index:
            #     continue

            jump_table[jump_table_index] = min(pattern_pivot_index - i, jump_table[jump_table_index])

        if pattern_pivot_index < right_index:
            pattern_pivot_index = right_index - kmp_preprocess[pattern_pivot_index + 1]
        else:
            i -= 1
        cum_sum = right_index - pattern_pivot_index

    return jump_table

def test_good_suffix_jump_table():
    pattern = "abcbabcbabaabcba"
          #    a b c b a b c b a b a a b c b a 
          #    5 4 3 2 5 4 3 2 1 2 1 1 0 0 0 0
    print(good_suffix_jump_table(pattern))
    # res[target - 1]!!!!

if __name__ == "__main__":
    test_good_suffix_jump_table()
