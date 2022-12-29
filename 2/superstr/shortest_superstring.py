from pprint import pprint

# one string CANNOT contain the other as a substring

def get_max_overlap(left: str, right: str) -> int:
    for i in range(min(len(left), len(right)), 0, -1):
        if left.endswith(right[:i]):
            return i
    return 0


def reconstruct_solution(best_mask: int,
                         current_best_choise: int,
                         best_choise_matrix: list[list[int]]) -> None:
    if not (best_mask & (best_mask - 1)):
        return

    best_prev_choice = best_choise_matrix[best_mask][current_best_choise]

    reconstruct_solution(best_mask=best_mask ^ (1 << current_best_choise),
                         current_best_choise=best_prev_choice,
                         best_choise_matrix=best_choise_matrix)
    print(best_prev_choice)


def shortest_superstring(collection: list[str]) -> int:
    N = len(collection)
    overlap = [[0 for _ in range(N)] for _ in range(N)]
    for i in range(N):
        for j in range(N):
            if i == j:
                continue
            overlap[i][j] = get_max_overlap(collection[i], collection[j])
    print("Overlap=====")
    pprint(overlap)
    dp = [[0 for _ in range(N)] for _ in range(1 << N)]
    best_index_dp = [[0 for _ in range(N)] for _ in range(1 << N)]

    for mask in range(1, 1 << N):
        if not (mask & (mask - 1)):
            continue

        for chosen_index in range(N):
            if not ((mask >> chosen_index) & 1):
                continue
            
            prev_mask = mask ^ (1 << chosen_index)
            for potential_prev_choice in range(N):
                if not ((prev_mask >> potential_prev_choice) & 1):
                    continue
                
                total_overlap = overlap[potential_prev_choice][chosen_index] + dp[prev_mask][potential_prev_choice]
                if total_overlap > dp[mask][chosen_index]:
                    dp[mask][chosen_index] = total_overlap
                    best_index_dp[mask][chosen_index] = potential_prev_choice

    # reconstructing solution
    all_chosen_mask = (1 << N) - 1
    best_last_choise = -1
    result_max_overlap = -1
    for i in range(N):
        if dp[all_chosen_mask][i] > result_max_overlap:
            result_max_overlap = dp[all_chosen_mask][i] 
            best_last_choise = i

    print("Solution=====")
    reconstruct_solution(all_chosen_mask, best_last_choise, best_index_dp)
    print(best_last_choise)

    print("DP=====")
    pprint(dp)

    return sum((len(i) for i in collection)) - max(dp[all_chosen_mask])


if __name__ == "__main__":
    string_collection = [
        # "asfaffsfa",
        # "asfatyurikjnd", 
        "1231241312tyurikjnd",
        "123123123",
        "123123123vefvfwedew123123",
    ]

    # 123123123
    # 123123123vefvfwedew123123
    #                       1231241312tyurikjnd

    # 123123123vefvfwedew1231231241312tyurikjnd

    print(shortest_superstring(string_collection))
