#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <math.h>

using namespace std;

vector <vector <string> >read_csv(){
    ifstream file;
    vector <vector <string> > ret_vec;
    file.open ("dataset.txt"); // make this an input variable
    string line;
    if (file.is_open()) {
        while (getline (file, line) ) {
            string temp;
            stringstream s(line);
            vector <string> temp_vec;
            while (getline (s, temp, ',')){
                temp_vec.push_back(temp);
            }
        ret_vec.push_back(temp_vec);
        }
        cout << ret_vec.size() << '\n';
        cout << ret_vec[0].size() << '\n';
        return ret_vec;
        file.close();
    } else cout << "Unable to open file";
}

bool data_validation(vector <vector <string> > input_data) {
    int data_size = input_data[0].size();
    bool valid = true;
    for (int i = 0; i < input_data.size(); i++){
        if (input_data[i].size() != data_size) valid = false;
    }
    if (valid) {
        cout << "Data valid" << '\n';
        return (valid);
    } else {
        cout << "Data invalid!!" << '\n';
        return (valid);
    }
}
map <int, string> label_allocation (vector <vector <string> > input_data) {
    vector <string> labels;
    int size = input_data[0].size();
    labels.push_back(input_data[0][size-1]);
    cout << "Size: " << size << '\n';
    for (int i = 0; i < input_data.size(); i++) {
        bool found = false;
        for (int it = 0; it < labels.size(); it++) {
            if (input_data[i][size-1] == labels[it]){
                //cout << "found" << '\n';
                found = true;
                }
            }
        if (found==false) {
            cout << "Adding to labels" << '\n';
            labels.push_back(input_data[i][size-1]);
        }
    }
    int count = 0;
    map <int, string> allocations;
    for (int itt = 0; itt < labels.size(); itt++) {
            allocations.insert({count, labels[itt]});
            count++;
        }
    return(allocations);
    }

vector <double> hidden_node_alpha(vector <vector <string> >input_data, double input_value, int data_col, map <int, string> labels) {
    vector <double> return_vals;
    int size = input_data[0].size()-1;
    int index = 0;
    string label;
    double smallest_distance = 1;
    double current_distance;
    for (int it = 0; it < input_data.size(); it++) {
        const char *current_string = input_data[it][data_col].c_str();
        double current_val = atof(current_string);
        current_distance = current_val - input_value;
        if (current_distance < 0) current_distance = -current_distance;
        if (smallest_distance > current_distance) {
           index = it;
           smallest_distance = current_distance;
           label = input_data[it][size];
        }
    }
    const char *return_string = input_data[index][data_col].c_str();
    double return_val = atof(return_string);
    return_vals.push_back(return_val);
    for (double itn = 0; itn < labels.size(); itn++) {
        if (labels[itn] == label) return_vals.push_back(itn);
    }
    return return_vals;
}

vector <double> hidden_node_alpha(vector <vector <string> >input_data, double input_value, int data_col, map <int, string> labels, double weight) {
    vector <double> return_vals;
    int size = input_data[0].size()-1;
    int index = 0;
    string label;
    double smallest_distance = 1;
    double current_distance;
    for (int it = 0; it < input_data.size(); it++) {
        const char *current_string = input_data[it][data_col].c_str();
        double current_val = atof(current_string);
        current_distance = current_val - input_value;
        if (current_distance < 0) current_distance = -current_distance;
        if (smallest_distance > current_distance) {
           index = it;
           smallest_distance = current_distance;
           label = input_data[it][size];
        }
    }
    const char *return_string = input_data[index][data_col].c_str();
    double return_val = atof(return_string);
    return_vals.push_back(return_val);
    for (double itn = 0; itn < labels.size(); itn++) {
        if (labels[itn] == label) {
            double new_weight = (weight*itn/2;
            //cout << "New weight: " << new_weight << '\n';
            return_vals.push_back (itn);
            return_vals.push_back (new_weight);
        }
    }
    return return_vals;
}

vector <vector <vector <string> > > splitter (vector < vector <string> > input_data) {
    vector <vector <vector <string> > > return_vectors;
    int size = input_data.size();
    vector <vector <string> > training, testing;
    cout << "You have " << size << " data entries. Please enter a training size." << '\n';
    int split_size;
    cin >> split_size;
    std::random_shuffle(input_data.begin(), input_data.end());
    int count = 0;
    for (int it = 0; it < input_data.size(); it++) {
        if (count < split_size) {
            training.push_back(input_data[it]);
        } else testing.push_back(input_data[it]);
        count++;
    }
    return_vectors.push_back(training);
    return_vectors.push_back(testing);
    return(return_vectors);
}


double distance_difference_binary(vector <vector <string> >input_data, double input_value, int data_col, map <int, string> labels) {
    double return_vals;
    int size = input_data[0].size()-1;
    int index = 0;
    string label;
    double smallest_distance_0 = 1;
    double smallest_distance_1 = 1;
    double current_distance;
    for (int it = 0; it < input_data.size(); it++) {
        const char *current_string = input_data[it][data_col].c_str();
        double current_val = atof(current_string);
        current_distance = current_val - input_value;
        if (current_distance < 0) = current_distance = -current_distance;
        if (smallest_distance_0 > current_distance && input_data[it][size] == labels[0]) {
            smallest_distance_0 = current_distance;
        }
        if (smallest_distance_1 > current_distance && input_data[it][size] == labels[1]) {
            smallest_distance_1 = current_distance;
        }
    }
    return_vals = smallest_distance_0-smallest_distance_1;
    if (return_vals < 0) return_vals = -return_vals;
    return(return_vals)
}

int main()
{
    vector <vector <string> > main_data = read_csv();
    if (data_validation(main_data)) {
        map <int, string> label_alloc = label_allocation(main_data);
        for (int i = 0; i < label_alloc.size(); i++) {
            cout << label_alloc[i] << '\n';
        }

    vector <vector <vector <string> > > split_data = splitter(main_data);
    cout << "Data has been split" << '\n';
    cout << "Training size is: " << split_data[0].size() << '\n';
    cout << "Testing data is: " << split_data[1].size() << '\n';
    int map_index = main_data[0].size()-1;
    double counter = 1;
    double correct = 0;
    vector <double> guesses;
    for (int it = 0; it < split_data[1].size(); it++) {
        double weight = 1;
        for (int itt = 0; itt < main_data[0].size()-1; itt++) {
            const char *current_string = split_data[1][it][itt].c_str();
            double current_val = atof(current_string);
            double a_b_distance = distance_difference_binary(split_data[0], current_val, itt, label_alloc)

            vector <double> current_runthrough = hidden_node_alpha(split_data[0], current_val, itt, label_alloc, weight);
            //cout << current_runthrough.size() << '\n';
            guesses.push_back(current_runthrough[2]);
            //cout << "Parsing.." << '\n';
        }
        string guess = label_alloc[round(weight)];
        if (guess == split_data[1][it][map_index]) {
                //cout << "correct!" << '\n';
                correct ++;
        }
        cout << "Guess = " << guess << " . Actual answer = " << split_data[1][it][map_index] << '\n';
        counter++;
    }
    //cout << correct << counter;
    double confidence = (correct/counter);
    cout << "Confidence = " << confidence << '\n';
    }
    return 0;
}
