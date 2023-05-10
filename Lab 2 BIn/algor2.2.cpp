#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

std::vector<std::vector<int>> optimal_bst(const std::vector<int>& keys, const std::vector<int>& frequencies) {
    int n = keys.size();
    std::vector<std::vector<int>> cost(n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> sum_freq(n + 1, std::vector<int>(n + 1, 0));

    for (int i = 0; i < n; i++) {
        cost[i][i] = frequencies[i];
        sum_freq[i][i] = frequencies[i];
    }

    for (int l = 2; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1;
            sum_freq[i][j] = sum_freq[i][j - 1] + frequencies[j];
            cost[i][j] = std::numeric_limits<int>::max();

            for (int r = i; r <= j; r++) {
                int c = ((r > i) ? cost[i][r - 1] : 0) + ((r < j) ? cost[r + 1][j] : 0) + sum_freq[i][j];
                cost[i][j] = std::min(cost[i][j], c);
            }
        }
    }

    return cost;
}

int main() {
    std::vector<int> keys = { 10, 20, 30, 40, 50 };
    std::vector<int> frequencies = { 5, 4, 3, 2, 1 };

    std::vector<std::vector<int>> cost = optimal_bst(keys, frequencies);
    std::cout << "Minimum cost of Optimal Binary Search Tree: " << cost[0][keys.size() - 1] << std::endl;

    return 0;
}