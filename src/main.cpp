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

    sortBy("callDuration", &usersData);

    fin.close();
    system("pause");
    return 0;
}
