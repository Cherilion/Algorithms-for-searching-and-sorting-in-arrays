#include "include/user_info.h"
#include "include/fileTools.h"

void parseTime(_time& _date, string _initialDate){
    _date.day = stoi(_initialDate.substr(0,2));
    _date.month = stoi(_initialDate.substr(3,2));
    _date.year = stoi(_initialDate.substr(6,2));
}


void parseUserData(userInfo& _userInfo, string _row){
    vector<string> _initialData;
    split(_row, _initialData, ',');

    parseTime(_userInfo.date, _initialData.at(0));

    _userInfo.code = stoi(_initialData.at(1));
    _userInfo.cityName = _initialData.at(2);

    _userInfo.callDuration = stoi(_initialData.at(3));
    _userInfo.rate = stoi(_initialData.at(4));

    _userInfo.phoneNumber1 = stoi(_initialData.at(5));
    _userInfo.phoneNumber2 = stoi(_initialData.at(6));
}

template <typename T, typename Field>
function<bool(const T&, const T&)> comparator(Field T::* field) {
    return [field](const T& b1, const T& b2) {
        return b1.*field > b2.*field;
    };
}


void sortBy(const string& field_name, vector<userInfo>* _usersInfo) {
    static const std::map<std::string, usersComparator> comparators{
            {"code", comparator(&userInfo::code)},
            {"cityName", comparator(&userInfo::cityName)},
            {"callDuration", comparator(&userInfo::callDuration)},
            {"rate", comparator(&userInfo::rate)},
            {"phoneNumber1", comparator(&userInfo::phoneNumber1)},
            {"phoneNumber2", comparator(&userInfo::phoneNumber2)}
    };
    auto it = comparators.find(field_name);
    if (it == comparators.end()) {
        throw invalid_argument("Invalid value for 'field_name'.");
    }

    vector<userInfo> &_usersInfoRef = *_usersInfo;

    //sort(_usersInfo->begin(), _usersInfo->end(), it->second);
    quickSort(_usersInfoRef, make_pair(0, _usersInfoRef.size() -  1), it->second);
}


template <typename T>
int partition(vector<T>& _structVec, pr_t startStop, usersComparator comp)
{

    int pivot = startStop.first;

    int count = 0;
    for (int i = startStop.first + 1; i <= startStop.second; i++) {
        if (!comp(_structVec.at(i), _structVec.at(pivot)))
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = startStop.first + count;
    swap(_structVec.at(pivotIndex), _structVec.at(startStop.first));

    // Sorting left and right parts of the pivot element
    int i = startStop.first, j = startStop.second;

    while (i < pivotIndex && j > pivotIndex) {

        while (comp(_structVec.at(i), _structVec.at(pivot))) {
            i++;
        }

        while (!comp(_structVec.at(i), _structVec.at(pivot))) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(_structVec.at(i++), _structVec.at(j--));
        }
    }

    return pivotIndex;
}

template <typename T>
void quickSort(vector<T>& vec, pr_t startStop, usersComparator comp)
{

    if (startStop.first >= startStop.second)
        return;

    int p = partition(vec, startStop, comp);

    quickSort(vec, make_pair(startStop.first, p - 1), comp);

    quickSort(vec, make_pair(p + 1, startStop.second), comp);
}
