#include<iostream>
#include<vector>

using namespace std;

void swap(vector<int> &nums, int i, int j)
{
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

void quickSort(vector<int> &nums, int left, int right)
{
    if(left >= right) return;
    int l = left, r = right;
    int pivot = nums[l];

    while(l < r)
    {
        while(l < r && nums[r] >= pivot) r--;
        if(l < r) nums[l++] = nums[r];
        while(l < r && nums[l] < pivot) l++;
        if(l < r) nums[r--] = nums[l]; 
    }
    nums[l] = pivot;
    quickSort(nums, left, l-1);
    quickSort(nums, l+1, right);

}

void selectSort(vector<int> &nums, int sz)
{
    int min;
    for(int i=0; i < sz; i++)
    {
        min = i;
        for(int j=i+1; j < sz; j++)
        {
            if(nums[j] < nums[min]) min = j;
        }
        swap(nums, i, min);
    }
}

void insertSort(vector<int> &nums, int sz)
{
    for(int i=1; i < sz; i++)
    {
        int cur = nums[i];
        int preIndex = i-1;
        while(preIndex >= 0 && nums[preIndex] > cur)
        {
            nums[preIndex+1] = nums[preIndex];  
            preIndex--;
        }
        nums[preIndex+1] = cur;
    }
}


void merge(vector<int> &nums, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);
    for(int i=0 ; i < n1; i++) L[i] = nums[left+i];
    for(int i=0 ; i < n2; i++) R[i] = nums[mid+1+i];

    int i=0, j = 0, k = left;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            nums[k] = L[i];
            i++; k++;
        }
        else
        {
            nums[k++] = R[j++];
        }
    }


    while(i < n1)
    {
        nums[k++] = L[i++];
    }

    while(j < n2)
    {
        nums[k++] = R[j++];
    }

}

void mergeSort(vector<int> &nums, int left, int right)
{
    if(left < right)
    {
        int mid = left + (right - left)/2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid+1, right);

        merge(nums, left, mid, right);
    }
}

int main()
{
    vector<int> nums = {3,1,2,6,4,5,6,9,10,8};
    // quickSort(nums, 0, nums.size());
    // selectSort(nums, nums.size());
    // insertSort(nums, nums.size());
    mergeSort(nums, 0, nums.size()-1);
    for(int i=0; i<nums.size(); i++)
    {
        cout << nums[i] << endl;
    }
    return 0;
}