#include <adoint.h>
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
    auto itComp = comparators.find(field_name);
    if (itComp == comparators.end()) {
        throw invalid_argument("Invalid value for 'field_name'.");
    }

    vector<userInfo> &_usersInfoRef = *_usersInfo;


    //several variants of sorting methods:
    //sort(_usersInfo->begin(), _usersInfo->end(), itComp->second);
    selectionSort(_usersInfoRef, make_pair(0, _usersInfoRef.size() -  1), itComp->second);
    //quickSort(_usersInfoRef, make_pair(0, _usersInfoRef.size() -  1), itComp->second);
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
void quickSort(vector<T>& _vec, pr_t _limits, usersComparator _comp)
{

    if (_limits.first >= _limits.second)
        return;

    int pivotIndex = partition(_vec, _limits, _comp);

    if(_limits.first < pivotIndex)
    quickSort(_vec, make_pair(_limits.first, pivotIndex - 1), _comp);

    if(_limits.second > pivotIndex)
    quickSort(_vec, make_pair(pivotIndex + 1, _limits.second), _comp);
}


template <typename T>
void selectionSort(vector<T>& _vec, pr_t _limits, usersComparator _comp)
{
    int min;
    for (int i = _limits.first; i <= _limits.second; i++)
    {
        min = i;
        for (int j = i + 1; j <= _limits.second; j++)
        {
            if (!_comp(_vec.at(j), _vec.at(min)))
                min = j;
        }
        swap(_vec.at(min), _vec.at(i));
    }
}


bool comparatorCityName(userInfo _userInfo, string _cityName){
    return _userInfo.cityName > _cityName;
}

bool equalTesterCityName(userInfo _userInfo, string _cityName){
    return _userInfo.cityName == _cityName;
}

int searchCity(string _searchValue, vector<userInfo>& _vec){
        int result =  binarySearch(_vec, _searchValue, make_pair(0, _vec.size() - 1));
        if(result == -1){
            throw "Not found value!";
        }
        return result;
}

int binarySearch(vector<userInfo>& _vec, string sValue, pr_t _limits){
    while(_limits.first <= _limits.second){
        int middleIndex = (_limits.first + _limits.second) / 2;
        if(equalTesterCityName(_vec.at(middleIndex), sValue)){
            return middleIndex;
        }
        if(!comparatorCityName(_vec.at(middleIndex), sValue)){
            _limits.first = middleIndex + 1;
        }
        else{
            _limits.second = middleIndex - 1;
        }
    }
    return -1;
}
