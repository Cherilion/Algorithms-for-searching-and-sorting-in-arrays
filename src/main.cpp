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
    cout << searchCity("Moscow", usersData) << endl;

    fin.close();
    system("pause");
    return 0;
}
