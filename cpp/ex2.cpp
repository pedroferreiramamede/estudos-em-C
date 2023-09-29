#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

std::vector<int> test(std::vector<int> nums)
{
    //create a temp vector to return de result
    std::vector<int> temp;
    for(int i = 1; i < nums.size()-1; i++)
    {
        //cout << "looking at:" << nums[i] << endl;

        if(nums[i] < nums[i-1] && nums[i] < nums[i+1])
        {
            temp.push_back(nums[i]);
            //cout << "found:" << nums[i] << endl;
        }
    }

    return temp;
}

int main()
{
    vector<int> nums = {1, 2 ,5, 0, 3, 1, 7};
    vector<int> result;

    //lets first print the original vector, just to pratice
    for (int x : nums)
    {
        cout << x;
        if(x != nums.back()) cout<< ",";
    }
    cout << endl;
    
    //get the result
    result = test(nums);

    for (int x : result)
    {
        cout << x;
        if(x != result.back()) cout<< ",";
    }
    cout << endl;

    
}