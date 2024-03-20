#include <iostream>
#include <vector>

using namespace std;

//交换元素
template<typename T>
void mySwap(vector<T> &arr, int a, int b)
{
    T temp= arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

//调整堆
template<typename T>
void adjustHeap(vector<T> &arr, int size, int index)
{
    int left = 2*index + 1;
    int right = 2*index + 2; 
    int largest = index; 
    
    if(left < size && arr[left] > arr[largest])
    {
        largest = left;
    }

    if(right < size && arr[right] > arr[largest])
    {
        largest = right;
    }

    //有最大的值 优先放到
    if(largest != index)
    {
        //把最大的值 置换到 父节点 
        mySwap(arr, largest, index);
        adjustHeap(arr, size, largest);
    }
}

//堆排序
template<typename T>
void heapSort(vector<T> &arr)
{
    int n = arr.size();
    for(int i=n/2-1; i >= 0; i--)
    {
        adjustHeap(arr, n, i);
    }

    for(int i=n-1; i>=0; i--)
    {
        mySwap(arr, 0, i);
        adjustHeap(arr, i, 0);
    }

}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    cout << "Original array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    heapSort(arr);

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
