#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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

void data_validation(vector <vector <string> > input_data) {
    int data_size = input_data[0].size();
    bool valid = true;
    for (int i = 0; i < input_data.size(); i++){
        if (input_data[i].size() != data_size) valid = false;
    }
    if (valid) {
        cout << "Data valid" << '\n';
    } else cout << "Data invalid!!" << '\n';
}

vector <int> label_allocation ()


int main()
{
    auto main_data = read_csv();
    data_validation(main_data);

    return 0;
}
