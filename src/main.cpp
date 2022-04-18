#include "include/fileTools.h"
#include "include/user_info.h"

using namespace std;

const string fname = "data.csv";

int main()
{
    ifstream fin(fname);

    vector<userInfo> usersData;
    while(fin.peek() != EOF){
        userInfo tempUser;

        string tempStr;
        getline(fin, tempStr);
        parseUserData(tempUser, tempStr);
        usersData.push_back(tempUser);
    }

    sortBy("cityName", &usersData);

    int totalCallDuration = 0;
    int totalCallSum = 0;
    for(int i = 0; i < usersData.size(); i++){
        totalCallDuration += usersData.at(i).callDuration;
        totalCallSum += usersData.at(i).callDuration * usersData.at(i).rate;
        if(i != usersData.size() - 1 &&
           usersData.at(i).cityName != usersData.at(i + 1).cityName ||
           i == usersData.size() - 1){

            cout << usersData.at(i).cityName << ":\n"
                 << " Total call time is " << totalCallDuration << '\n'
                 << " Total call sum is " << totalCallSum << "\n\n";

            totalCallDuration = 0;
            totalCallSum = 0;

        }
    }

    fin.close();
    system("pause");
    return 0;
}
