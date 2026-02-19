#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;


vector<int> frequency_count;
vector<int> max_or_element;

void process_test_case() {
    int array_size;
    if (!(cin >> array_size)) return;

    vector<int> input_array(array_size);
    int current_max_value = 0;
    int max_bit_count = 0;

    for(int i = 0; i < array_size; i++) {
        cin >> input_array[i];
        current_max_value = max(current_max_value, input_array[i]);
        while(input_array[i] >= (1 << max_bit_count)) max_bit_count++;
    }

    if (current_max_value == 0) {
        cout << 0 << " " << (long long)array_size * array_size << "\n";
        return;
    }


    int state_size = (1 << max_bit_count);
    frequency_count.assign(state_size, 0);
    max_or_element.assign(state_size, -1);


    for(int val : input_array) {
        frequency_count[val]++;
        max_or_element[val] = val;
    }


    for(int bit_pos = 0; bit_pos < max_bit_count; bit_pos++) {
        for(int i = 0; i < state_size; i++) {

            if (i & (1 << bit_pos)) {
                int i_without_bit = i ^ (1 << bit_pos);


                if (max_or_element[i_without_bit] > max_or_element[i]) {
                    max_or_element[i] = max_or_element[i_without_bit];
                }

            }
        }
    }

    long long final_max_result = current_max_value;
    long long total_pair_count = 0;


    for(int val : input_array) {

        int complement = ((1 << max_bit_count) - 1) ^ val;

        if(max_or_element[complement] != -1) {
            long long current_or_result = (long long)max_or_element[complement] | val;

            if(final_max_result < current_or_result) {
                final_max_result = current_or_result;
                total_pair_count = 0;
            }
        }
    }


    for(int val : input_array) {
        int complement = ((1 << max_bit_count) - 1) ^ val;

        if (max_or_element[complement] != -1) {
            if (final_max_result == ((long long)max_or_element[complement] | val)) {

                int element_to_add = max_or_element[complement];

                if (val == element_to_add) {

                    if (val == final_max_result) {

                    }
                } else {

                    total_pair_count += frequency_count[element_to_add];
                }
            }
        }
    }


    total_pair_count = 0;
    map<int, long long> counts;
    for(int x : input_array) counts[x]++;

    for(auto const& pair : counts) {
        if (pair.first == final_max_result) {
            total_pair_count += pair.second * pair.second;
        }
    }


    for(int val : input_array) {
        int complement = ((1 << max_bit_count) - 1) ^ val;
        if (max_or_element[complement] != -1) {
            int element_to_add = max_or_element[complement];
            if (final_max_result == ((long long)element_to_add | val)) {
                if (val != element_to_add) {

                    if (val < element_to_add) {
                        total_pair_count += counts[val] * counts[element_to_add];
                    }
                }
            }
        }
    }


    total_pair_count = 0;

    for(auto const& pair : counts) {
        int x = pair.first;
        if (x == final_max_result) {
            total_pair_count += pair.second * pair.second;
        }
    }

    for(int x : input_array) {
        int C = ((1 << max_bit_count) - 1) ^ x;
        if(max_or_element[C] != -1) {
            int y = max_or_element[C];
            if(final_max_result == ((long long)x | y)) {
                if(x < y) {

                   total_pair_count += 2 * counts[x] * counts[y];
                }
            }
        }
    }


    cout << final_max_result << " " << total_pair_count << "\n";
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int total_test_cases;
    if (!(cin >> total_test_cases)) return 0;

    while (total_test_cases--) {
        process_test_case();
    }

    return 0;
}
