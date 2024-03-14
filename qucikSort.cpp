#include<iostream>
#include<vector>

template<typename T>
void quickSort(std::vector<T> &nums, int start, int end);

template<typename T>
int binarySearch(std::vector<T> nums, T target);

int main()
{
    std::vector<int> nums = {3,4,6,1,2,5,8,7,0};
    quickSort(nums, 0, nums.size()-1);
    for(int i:nums)
    {
        std::cout << i << " ,";
    }
    int pos = binarySearch(nums, 8);
    std::cout << std::endl <<"8,  pos = " << pos << std::endl;


    std::vector<double> nums_double = {3.14, 2.71, 1.618, 0.577, 1.732, 3.1, 2.7, 1.61, 0.57, 1.72};
    quickSort(nums_double, 0, nums_double.size()-1);
    for(double d : nums_double)
    {
        std::cout << d << " ,";
    }
    double pos_double = binarySearch(nums_double, 1.618);
    std::cout << std::endl <<"1.618,  pos = " << pos_double << std::endl;

    return 0;
}

template<typename T>
void quickSort(std::vector<T> &nums, int start, int end)
{
    if(start < end)
    {
        int i = start, j = end;
        T pivot = nums[i];
        while(i < j)
        {
            while(i < j && nums[j] >= pivot) j--;
            if(i<j) nums[i++] = nums[j];
            while(i < j && nums[i] <= pivot) i++;
            if(i < j) nums[j--] = nums[i];
        }
        nums[i] = pivot;
        quickSort(nums, start, i-1);
        quickSort(nums, i+1, end);
    }
}

template<typename T>
int binarySearch(std::vector<T> nums, T target)
{
    int begin = 0, end = nums.size()-1;
    while(begin <= end)
    {
        int mid = begin+(end-begin)/2;
        if(nums[mid] > target) end = mid - 1;
        else if(nums[mid] < target) begin = mid+1;
        else return mid;
    }
    return -1;
}
