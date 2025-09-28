#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <numeric>

using namespace std;

// Function to get input from the user
void getInput(int& num_columns, int& num_rows, vector<vector<string>>& data, vector<int>& classes) {
    cout << "Enter Count Of Column :- ";
    cin >> num_columns;
    cout << "Enter Count Of Rows :- ";
    cin >> num_rows;

    data.resize(num_columns, vector<string>(num_rows));
    classes.resize(num_rows);

    for (int i = 0; i < num_columns; ++i) {
        for (int j = 0; j < num_rows; ++j) {
            cout << "Enter " << i + 1 << " Text Column " << j + 1 << " Row Value :- ";
            cin >> data[i][j];
        }
    }

    for (int i = 0; i < num_rows; ++i) {
        cout << "Enter " << i + 1 << " Class Value :- ";
        cin >> classes[i];
    }
}

// Function to calculate entropy
double calculateEntropy(double positive, double negative) {
    if (positive == 0 || negative == 0) {
        return 0;
    }
    double total = positive + negative;
    double p_pos = positive / total;
    double p_neg = negative / total;
    return -p_pos * log2(p_pos) - p_neg * log2(p_neg);
}

// Function to print the decision tree
void printTree(const vector<string>& root_nodes, const vector<double>& root_node_outcomes, const vector<string>& child_nodes, const vector<string>& child_node_outcomes) {
    cout << "--------------------------";
    cout << "Root Node" << endl;
    cout << "--------------------------";
    cout << endl;
    for (size_t i = 0; i < root_nodes.size(); ++i) {
        if (root_node_outcomes[i] == -1) {
            cout << root_nodes[i] << " For Yes" << endl;
        } else if (root_node_outcomes[i] == -2) {
            cout << root_nodes[i] << " For No" << endl;
        }
        else {
            cout << root_nodes[i] << " For " << (root_node_outcomes[i]) << " Column" << endl;
        }
    }

    if (!child_nodes.empty()) {
        cout << endl << endl;
        cout << "--------------------------";
        cout << "Child Node" << endl;
        cout << "--------------------------";
        cout << endl;

        vector<pair<string, string>> child_pairs;
        for(size_t i = 0; i < child_nodes.size(); ++i) {
            child_pairs.push_back({child_nodes[i], child_node_outcomes[i]});
        }
        sort(child_pairs.begin(), child_pairs.end());
        child_pairs.erase(unique(child_pairs.begin(), child_pairs.end()), child_pairs.end());

        for (const auto& p : child_pairs) {
            cout << p.first << " For " << p.second << endl;
        }
    }
}

int main() {
    int num_columns, num_rows;
    vector<vector<string>> data;
    vector<int> classes;

    getInput(num_columns, num_rows, data, classes);

    double total_positive = 0, total_negative = 0;
    for (int cls : classes) {
        if (cls == 1) total_positive++;
        else total_negative++;
    }

    vector<double> gains;
    double entire_entropy = calculateEntropy(total_positive, total_negative);

    for (int i = 0; i < num_columns; ++i) {
        double entropy = 0;
        vector<int> p(num_rows);
        iota(p.begin(), p.end(), 0);
        sort(p.begin(), p.end(), [&](int a, int b) {
            return data[i][a] < data[i][b];
        });

        if (num_rows > 0) {
            string current_val = data[i][p[0]];
            double pos = 0, neg = 0;
            for (int j = 0; j < num_rows; ++j) {
                int original_index = p[j];
                if (data[i][original_index] == current_val) {
                    if (classes[original_index] == 1) pos++;
                    else neg++;
                } else {
                    entropy += ((pos + neg) / num_rows) * calculateEntropy(pos, neg);
                    current_val = data[i][original_index];
                    pos = (classes[original_index] == 1);
                    neg = (classes[original_index] == 0);
                }
            }
            entropy += ((pos + neg) / num_rows) * calculateEntropy(pos, neg);
        }
        gains.push_back(entire_entropy - entropy);
    }

    int root_node_index = distance(gains.begin(), max_element(gains.begin(), gains.end()));

    vector<string> root_nodes;
    if(num_rows > 0) {
        vector<string> sorted_root_col = data[root_node_index];
        sort(sorted_root_col.begin(), sorted_root_col.end());
        sorted_root_col.erase(unique(sorted_root_col.begin(), sorted_root_col.end()), sorted_root_col.end());
        root_nodes = sorted_root_col;
    }

    vector<double> root_node_outcomes;
    vector<string> child_nodes;
    vector<string> child_node_outcomes;

    for (const string& root_node_val : root_nodes) {
        vector<vector<string>> sub_data;
        vector<int> sub_classes;
        double sub_total_p = 0, sub_total_n = 0;
        vector<int> original_indices;

        for (int i = 0; i < num_rows; ++i) {
            if (data[root_node_index][i] == root_node_val) {
                if (classes[i] == 1) sub_total_p++;
                else sub_total_n++;
                sub_classes.push_back(classes[i]);
                original_indices.push_back(i);
            }
        }

        if (sub_total_n == 0) {
            root_node_outcomes.push_back(-1); // Pure Yes
            continue;
        }
        if (sub_total_p == 0) {
            root_node_outcomes.push_back(-2); // Pure No
            continue;
        }

        sub_data.resize(num_columns, vector<string>(sub_classes.size()));
        for(int i = 0; i < num_columns; i++){
            int k = 0;
            for(int j : original_indices){
                sub_data[i][k++] = data[i][j];
            }
        }

        double sub_entire_entropy = calculateEntropy(sub_total_p, sub_total_n);
        vector<double> sub_gains;

        for (int i = 0; i < num_columns; ++i) {
            if (i == root_node_index) {
                sub_gains.push_back(-1.0);
                continue;
            }
            double entropy = 0;
            if(!sub_classes.empty()){
                vector<int> p_sub(sub_classes.size());
                iota(p_sub.begin(), p_sub.end(), 0);
                sort(p_sub.begin(), p_sub.end(), [&](int a, int b) {
                    return sub_data[i][a] < sub_data[i][b];
                });

                string current_val = sub_data[i][p_sub[0]];
                double p = 0, n = 0;
                for (size_t j = 0; j < sub_classes.size(); ++j) {
                    int original_sub_index = p_sub[j];
                    if (sub_data[i][original_sub_index] == current_val) {
                        if (sub_classes[original_sub_index] == 1) p++;
                        else n++;
                    } else {
                        entropy += ((p + n) / sub_classes.size()) * calculateEntropy(p, n);
                        current_val = sub_data[i][original_sub_index];
                        p = (sub_classes[original_sub_index] == 1);
                        n = (sub_classes[original_sub_index] == 0);
                    }
                }
                entropy += ((p + n) / sub_classes.size()) * calculateEntropy(p, n);
            }
            sub_gains.push_back(sub_entire_entropy - entropy);
        }

        int max_gain_col_idx = distance(sub_gains.begin(), max_element(sub_gains.begin(), sub_gains.end()));
        root_node_outcomes.push_back(max_gain_col_idx + 1);

        if(!sub_data.empty()){
            vector<string> unique_child_vals;
            vector<string> sorted_child_data = sub_data[max_gain_col_idx];
            sort(sorted_child_data.begin(), sorted_child_data.end());
            if(!sorted_child_data.empty()){
                unique_child_vals.push_back(sorted_child_data[0]);
                for(size_t i = 1; i < sorted_child_data.size(); i++){
                    if(sorted_child_data[i] != sorted_child_data[i-1]){
                        unique_child_vals.push_back(sorted_child_data[i]);
                    }
                }
            }

            for(const string& val : unique_child_vals){
                child_nodes.push_back(val);
                double p = 0, n = 0;
                for(size_t i = 0; i < sub_data[max_gain_col_idx].size(); i++){
                    if(sub_data[max_gain_col_idx][i] == val){
                        if(sub_classes[i] == 1) p++;
                        else n++;
                    }
                }
                if(p >= n) child_node_outcomes.push_back("Yes");
                else child_node_outcomes.push_back("No");
            }
        }
    }

    printTree(root_nodes, root_node_outcomes, child_nodes, child_node_outcomes);

    return 0;
}