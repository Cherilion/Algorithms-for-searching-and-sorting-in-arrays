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


    //several variants of sorting methods:
    //sort(_usersInfo->begin(), _usersInfo->end(), it->second);
    selectionSort(_usersInfoRef, make_pair(0, _usersInfoRef.size() -  1), it->second);
    //quickSort(_usersInfoRef, make_pair(0, _usersInfoRef.size() -  1), it->second);
}


template <typename T>
int partition(vector<T>& _structVec, pr_t _limits, usersComparator comp)
{

    int pivot = _limits.first;

    int count = 0;
    for (int i = _limits.first + 1; i <= _limits.second; i++) {
        if (!comp(_structVec.at(i), _structVec.at(pivot)))
            count++;
    }


    int _pivotIndex = _limits.first + count;
    swap(_structVec.at(_pivotIndex), _structVec.at(_limits.first));


    int i = _limits.first, j = _limits.second;

    while (i < _pivotIndex && j > _pivotIndex) {

        while (!comp(_structVec.at(i), _structVec.at(_pivotIndex))) {
            i++;
        }

        while (comp(_structVec.at(j), _structVec.at(_pivotIndex))) {
            j--;
        }

        if (i < _pivotIndex && j > _pivotIndex) {
            swap(_structVec.at(i++), _structVec.at(j--));
        }
    }

    return _pivotIndex;
}

template <typename T>
void quickSort(vector<T>& vec, pr_t limits, usersComparator comp)
{

    if (limits.first >= limits.second)
        return;

    int pivotIndex = partition(vec, limits, comp);

    if(limits.first < pivotIndex)
    quickSort(vec, make_pair(limits.first, pivotIndex - 1), comp);

    if(limits.second > pivotIndex)
    quickSort(vec, make_pair(pivotIndex + 1, limits.second), comp);
}


template <typename T>
void selectionSort(vector<T>& _vec, pr_t limits, usersComparator comp)
{
    int min;
    for (int i = limits.first; i <= limits.second; i++)
    {
        min = i;
        for (int j = i + 1; j <= limits.second; j++)
        {
            if (!comp(_vec.at(j), _vec.at(min)))
                min = j;
        }
        swap(_vec.at(min), _vec.at(i));
    }
}