#ifndef LAB2_USER_INFO_H
#define LAB2_USER_INFO_H

#include<bits/stdc++.h>
using namespace std;

typedef pair<size_t, size_t> pr_t;

struct _time{
    int day;
    int month;
    int year;
};

struct userInfo{
    _time date;

    int code;
    string cityName;

    int callDuration;
    int rate;

    int phoneNumber1;
    int phoneNumber2;
};

void parseTime(_time&, string);
void parseUserData(userInfo&, string);

typedef function<bool(const userInfo&, const userInfo&)> usersComparator;

template <typename T, typename Field>
function<bool(const T&, const T&)> comparator(Field T::* field);

void sortBy(const std::string& field_name, std::vector<userInfo>* );

template <typename T>
int partition(vector<T>&, pr_t, usersComparator);

template <typename T>
void quickSort(vector<T>&, pr_t, usersComparator);

template <typename T>
void selectionSort(vector<T>&, pr_t, usersComparator);


bool comparatorCityName(userInfo, string);
bool equalTesterCityName(userInfo, string);
int searchCity(string _searchValue, vector<userInfo>& _vec);
int binarySearch(vector<userInfo>&, string, pr_t);

#endif //LAB2_USER_INFO_H
