#include <iostream>

void heapify(float arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(float arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void acceptMarks(float arr[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << "Enter Student " << i + 1 << "'s Marks: ";
        std::cin >> arr[i];
    }
}

void displayMarks(float arr[], int n) {
    std::cout << "Marks: ";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int choice;
    int n;
    std::cout << "Enter the number of Students: ";
    std::cin >> n;
    float* marks = new float[n];
    bool sorted = false;

    while (true) {
        std::cout << "\n\n1. Enter Marks" << std::endl;
        std::cout << "2. Display Marks" << std::endl;
        std::cout << "3. Heap Sort" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                acceptMarks(marks, n);
                sorted = false;
                break;
            case 2:
                if (!sorted) {
                    std::cout << "Marks have not been sorted yet." << std::endl;
                } else {
                    displayMarks(marks, n);
               std::cout <<"Minimum Marks: " << marks[0] <<std::endl;
               std::cout <<"Minimum Marks: " << marks[n - 1] <<std::endl;
                }
                
                break;
            case 3:
                heapSort(marks, n);
                sorted = true;
                std::cout << "Marks have been sorted using Heap Sort." << std::endl;
                break;
            case 4:
                delete[] marks;
                return 0;
            default:
                std::cout << "Invalid choice" << std::endl;
                break;
        }
    }

    return 0;
}
